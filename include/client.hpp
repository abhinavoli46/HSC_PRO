#pragma once

#include <string>
#include <zmq.hpp>
#include "framepack.hpp"

/*------------------------------------------------------------ CLIENT CLASS DEFINITION ------------------------------------------------------------------*/

class Client{
    private:
        zmq::context_t m_context;
        zmq::socket_t m_socket;
        std::string m_topic;
    public:
        Client();
        void connect(const int& port);
        void sendMessageToServer(std::string& frameStr);
        ~Client();
};

