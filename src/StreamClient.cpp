#include "StreamCommon.hpp"

class StreamClientCore {
public:
    StreamClientCore(const std::string& host, int port)
        : io_context_(), socket_(io_context_) {
        tcp::resolver resolver(io_context_);
        boost::asio::connect(socket_, resolver.resolve(host, std::to_string(port)));
        logInfo("Connected to server " + host + ":" + std::to_string(port));
    }

    void send(const std::string& message) {
        boost::asio::write(socket_, boost::asio::buffer(message));
    }

    void startReceiving() {
        std::thread([this]() { receiveLoop(); }).detach();
    }

private:
    boost::asio::io_context io_context_;
    tcp::socket socket_;

    void receiveLoop() {
        try {
            char buf[4096];
            for (;;) {
                boost::system::error_code ec;
                size_t len = socket_.read_some(boost::asio::buffer(buf), ec);
                if (ec) break;
                std::string data(buf, len);
                std::cout << "[Client] Received: " << data << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "[Client] Exception: " << e.what() << std::endl;
        }
    }
};
