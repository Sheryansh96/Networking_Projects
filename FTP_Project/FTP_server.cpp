// FTP_Server.cpp

#include <iostream>
#include <fstream>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

void handle_client(tcp::socket socket) {
    try {
        while (true) {
            char command[1024];
            boost::system::error_code error;
            socket.read_some(boost::asio::buffer(command), error);
            string str_command(command);

            if (str_command == "UPLOAD") {
                char filename[1024];
                socket.read_some(boost::asio::buffer(filename), error);
                ofstream ofs(filename, ios::binary);

                char data[1024];
                while (socket.read_some(boost::asio::buffer(data), error)) {
                    ofs.write(data, 1024);
                }
                ofs.close();
            } else if (str_command == "DOWNLOAD") {
                char filename[1024];
                socket.read_some(boost::asio::buffer(filename), error);
                ifstream ifs(filename, ios::binary);

                char data[1024];
                while (ifs.read(data, 1024)) {
                    socket.write_some(boost::asio::buffer(data, 1024), error);
                }
                ifs.close();
            }
        }
    } catch (exception &e) {
        cerr << "Exception in thread: " << e.what() << endl;
    }
}

int main() {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        thread(handle_client, move(socket)).detach();
    }
}
