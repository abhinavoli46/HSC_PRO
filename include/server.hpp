#ifndef SERVER_H
#define SERVER_H

#include<string>
#include<zmq.hpp>
#include "framepack.hpp"

/*------------------------------------------------------------ SERVER CLASS DEFINITION ------------------------------------------------------------------*/
class Server
{

    private:
        zmq::context_t m_context;
        zmq::context_t n_context;
        zmq::socket_t m_socket;
        std::string n_topic;
        zmq::socket_t n_socket;
    public:
        Server();
        void startServer(int portL,int portR,std::string topicName);
        void receiveMessageFromClient();
        void sendMessageToClient(std::string& frameStr);
        ~Server();

};

#endif