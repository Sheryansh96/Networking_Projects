#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int current_server = 0;

string backend_addresses[] = {"127.0.0.1:9001", "127.0.0.1:9002"};

void handle_client(tcp::socket client_socket) {
  try {
    string backend_address = backend_addresses[current_server];
    current_server = (current_server + 1) % 2;

    string backend_ip = backend_address.substr(0, backend_address.find(":"));
    string backend_port = backend_address.substr(backend_address.find(":") + 1);

    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::socket backend_socket(io_context);
    auto endpoints = resolver.resolve(backend_ip, backend_port);
    boost::asio::connect(backend_socket, endpoints);

    char data[1024];
    while (true) {
      auto bytes_read_from_client = client_socket.read_some(boost::asio::buffer(data));
      backend_socket.write_some(boost::asio::buffer(data, bytes_read_from_client));

      auto bytes_read_from_backend = backend_socket.read_some(boost::asio::buffer(data));
      client_socket.write_some(boost::asio::buffer(data, bytes_read_from_backend));
    }
  } catch (exception &e) {
    cerr << "Exception in thread: " << e.what() << endl;
  }
}

int main() {
  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    while (true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      thread(handle_client, move(socket)).detach();
    }
  } catch (exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
