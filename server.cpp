#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <memory>

using boost::asio::ip::tcp;
const std::string FILENAME = "response.txt";
const int PORT = 12345;

void handle_client(std::shared_ptr<tcp::socket> socket) {
    try {
        std::ifstream file(FILENAME, std::ios::binary);
        if (!file) {
            std::cerr << "Error: file " << FILENAME << " not found." << std::endl;
            return;
        }

        std::cout << "Sending file..." << std::endl;
        boost::asio::write(*socket, boost::asio::buffer(std::string(std::istreambuf_iterator<char>(file), {})));
        std::cout << "File sent." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error sending file: " << e.what() << std::endl;
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
        std::cout << "Server started on port " << PORT << "..." << std::endl;
        std::vector<std::thread> thread_pool;

        while (true) {
            auto socket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*socket);
            std::cout << "Сlient connected." << std::endl;

            thread_pool.emplace_back(handle_client, socket);
        }

        for (auto& th : thread_pool) {
            if (th.joinable()) {
                th.join();
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}