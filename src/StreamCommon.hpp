#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <memory>
#include <vector>

using boost::asio::ip::tcp;

class StreamSession : public std::enable_shared_from_this<StreamSession> {
public:
    StreamSession(boost::asio::io_context& io, tcp::socket socket)
        : socket_(std::move(socket)), io_context_(io) {}

    void start() {
        readLoop();
    }

    void send(const std::string& data) {
        std::lock_guard<std::mutex> lock(write_mutex_);
        boost::asio::async_write(socket_, boost::asio::buffer(data),
            [this](boost::system::error_code ec, std::size_t) {
                if (ec) std::cerr << "[StreamSession] Write error: " << ec.message() << std::endl;
            });
    }

private:
    tcp::socket socket_;
    boost::asio::io_context& io_context_;
    std::mutex write_mutex_;

    void readLoop() {
        auto self(shared_from_this());
        std::thread([this, self]() {
            try {
                char buf[4096];
                for (;;) {
                    boost::system::error_code ec;
                    size_t len = socket_.read_some(boost::asio::buffer(buf), ec);
                    if (ec) break;
                    std::string data(buf, len);
                    handleIncomingData(data);
                }
            } catch (const std::exception& e) {
                std::cerr << "[StreamSession] Exception: " << e.what() << std::endl;
            }
        }).detach();
    }

    void handleIncomingData(const std::string& data) {
        std::cout << "[StreamSession] Received: " << data << std::endl;
    }
};

inline void logInfo(const std::string& msg) {
    std::cout << "[StreamX] " << msg << std::endl;
}
