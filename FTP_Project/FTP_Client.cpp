// FTP_Client.cpp

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
    boost::asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8080");
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    while (true) {
        string command;
        cout << "Enter command (UPLOAD/DOWNLOAD): ";
        cin >> command;

        boost::system::error_code error;
        socket.write_some(boost::asio::buffer(command), error);

        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        socket.write_some(boost::asio::buffer(filename), error);

        if (command == "UPLOAD") {
            ifstream ifs(filename, ios::binary);
            char data[1024];
            while (ifs.read(data, 1024)) {
                socket.write_some(boost::asio::buffer(data, 1024), error);
            }
            ifs.close();
        } else if (command == "DOWNLOAD") {
            ofstream ofs(filename, ios::binary);
            char data[1024];
            while (socket.read_some(boost::asio::buffer(data), error)) {
                ofs.write(data, 1024);
            }
            ofs.close();
        }
    }

    return 0;
}
