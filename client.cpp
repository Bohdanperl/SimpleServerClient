#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <chrono>

using boost::asio::ip::tcp;

const std::string SERVER_IP = "127.0.0.1";
const int PORT = 12345;

std::ofstream create_file() {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch();
    std::string filename = "received_response" + std::to_string(value.count()) + ".txt";
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        throw std::runtime_error("Error creating file: " + filename);
    }
    std::cout << "Receiving file and saving as " << filename << std::endl;
    return outfile;
}

void receive_file(tcp::socket& socket) {
    std::ofstream outfile = create_file();

    boost::system::error_code error;
    boost::asio::streambuf buffer;
    while (boost::asio::read(socket, buffer, boost::asio::transfer_at_least(1), error)) {
        outfile << &buffer;
    }
    if (error != boost::asio::error::eof) {
        throw boost::system::system_error(error);
    }

    std::cout << "File received successfully." << std::endl;
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(SERVER_IP, std::to_string(PORT)));
        std::cout << "Connecting to server..." << std::endl;
        receive_file(socket);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}