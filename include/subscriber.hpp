#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>
#include <zmq.hpp>

/*------------------------------------------------------------ SUBSCRIBER CLASS DEFINITION ------------------------------------------------------------------*/
class Subscriber
{

    private:
        zmq::socket_t m_socket;
        zmq::context_t m_context;
        std::string m_topic;

    public:
        Subscriber();
        void connect(int port,std::string topicName);
        void receiveMessageFromServer();
        void close();
        ~Subscriber();
        
};

#endif