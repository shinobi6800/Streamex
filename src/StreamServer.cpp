#include "StreamCommon.hpp"
#include <vector>

class StreamServerCore {
public:
    StreamServerCore(int port)
        : io_context_(), acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
        logInfo("Server listening on port " + std::to_string(port));
    }

    void start() {
        std::thread([this]() {
            acceptLoop();
        }).detach();
    }

    void broadcast(const std::string& message) {
        for (auto& s : sessions_) {
            s->send(message);
        }
    }

private:
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<StreamSession>> sessions_;

    void acceptLoop() {
        for (;;) {
            tcp::socket socket(io_context_);
            acceptor_.accept(socket);
            auto session = std::make_shared<StreamSession>(io_context_, std::move(socket));
            sessions_.push_back(session);
            session->start();
        }
    }
};
