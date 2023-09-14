# Networking_Projects


Description:
This C++ program is a simple implementation of an FTP client-server model. It is designed for educational purposes and demonstrates the core functionalities of file upload and download using the TCP/IP protocol. The server supports handling multiple clients through multithreading. The Boost.Asio library is used to handle asynchronous networking tasks.

Key Concepts:
TCP/IP Networking: The program uses TCP sockets for networking, ensuring reliable data transmission.

Asynchronous I/O: The Boost.Asio library manages asynchronous I/O operations, enhancing responsiveness and efficiency.

Multithreading: The server uses multithreading to handle multiple client connections simultaneously.

File Operations: The server and client perform basic file operations like reading and writing to upload and download files.

How It Works:
Server:
Initialization: The server listens on port 8080 and waits for incoming client connections.

Client Connection: Upon accepting a new client connection, a new thread is spawned to handle the client's requests.

Command Handling: The server reads a command sent by the client. Currently supported commands are "UPLOAD" and "DOWNLOAD".

File Transfer: Based on the received command, the server either reads from the client socket and writes to a file (UPLOAD) or reads from a file and writes to the client socket (DOWNLOAD).

Client:
Connection: The client connects to the server on IP 127.0.0.1 and port 8080.

User Input: The client waits for the user to input a command ("UPLOAD" or "DOWNLOAD") and the filename to act upon.

File Transfer: Depending on the command, the client either sends a file to the server or receives a file from it.

Compilation:
Server: g++ FTP_Server.cpp -o FTP_Server -lboost_system -pthread
Client: g++ FTP_Client.cpp -o FTP_Client -lboost_system
Execution:
Run the server using ./FTP_Server
Run the client using ./FTP_Client
Limitations:
The example is highly simplified and lacks features like user authentication, error handling, and secure data transmission through SSL/TLS.
Dependencies:
Boost.Asio library for handling asynchronous network operations.
By running the server and client, you can upload and download files by entering the respective commands ("UPLOAD" or "DOWNLOAD") and specifying the filename.
