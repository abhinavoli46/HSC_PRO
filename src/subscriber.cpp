#include <iostream>
#include <subscriber.hpp>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include "framepack.hpp"
#include <thread>

const int SUBSCRIBER_PORT = 5001;
const std::string topic = "Frames";
std::atomic<bool> appExit(false);
void ctrCHandler(int signal)
{
    if(signal == SIGINT)
    {
        //"Got signal to exit"
        appExit = true;
    }
        
}

/*------------------------------------------------------------------------ SUBSCRIBER CLASS METHODS----------------------------------------------------------------------------*/
// Subscriber object constructor to create socket in SUBSCRIBER mode
Subscriber::Subscriber()
{
    m_context = zmq::context_t(1);
    m_socket = zmq::socket_t(m_context,ZMQ_SUB);
    
}

// Method to connect the socket with the server
void Subscriber::connect(int port, std::string topicName)
{
    m_socket.set(zmq::sockopt::subscribe, topicName.c_str());
    try{
        m_socket.connect("tcp://localhost:" + std::to_string(port));
    }
    catch(zmq::error_t e)
    {
        std::cout << e.what();
    }
    m_topic = topicName;
}

// Method to receive the message from the server
void Subscriber::receiveMessageFromServer()
{
    zmq::message_t topicName;
    zmq::message_t payload;
    cv::namedWindow("Subscriber Window",cv::WINDOW_AUTOSIZE);
    FramePack packer;
    
    while(!appExit)
    {
        if(m_socket.recv(topicName,zmq::recv_flags::none))
        {
            auto rc = m_socket.recv(payload,zmq::recv_flags::none);

            auto frameStr = payload.to_string();
            packingStructure ps = packer.unpackFrame(frameStr);
            cv::imshow("Subscriber Window", cv::Mat(ps.height,ps.width,ps.type,ps.imgData.data()));
            if(cv::waitKey(1) == 'q')
            {
                appExit = true;
            }
            std::cout << "Alert Received In Subscriber" << std::endl;
        }
        else
        {
            continue;
        }
        
    }
    cv::destroyAllWindows();
}

// Method to close socket and shut the context
void Subscriber::close()
{
    try
    {
        if(m_socket.handle() != nullptr)
        {
            m_socket.close();
            std::cout << "Socket Closed" << std::endl;
        }
        m_context.shutdown();
        std::cout << "Context Shutdown" << std::endl;
    }
    catch(zmq::error_t e)
    {
        std::cout << "Error at subscriber : " << e.what() << std::endl;
    }
}
// Destructor to release the resources
Subscriber::~Subscriber()
{
    close();
}

void receive(Subscriber* subscriber)
{
    subscriber->receiveMessageFromServer();
}

/*----------------------------------------------------------------------------- MAIN ---------------------------------------------------------------------------*/
int main()
{
    signal(SIGINT,ctrCHandler);
    Subscriber subscriber;
    subscriber.connect(SUBSCRIBER_PORT,topic);
    std::thread t(receive,&subscriber);
    while(!appExit)
    {
        sleep(1);
    }
    return 0;
}