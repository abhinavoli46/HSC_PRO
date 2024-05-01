#include <iostream>
#include <zmq.hpp>
#include <server.hpp>
#include <thread>

const int PUB_SUB_PORT = 5001;
const int PUSH_PULL_PORT = 5000;

std::atomic<bool> appExit(false);

void ctrCHandler(int signal)
{
    //"Got signal to exit"
    appExit = true;
}

/*------------------------------------------------------------------------ SERVER CLASS METHODS----------------------------------------------------------------------------*/
// Server object creation with 2 different sockets 
// One in PULL mode for pulling the data
// Another in PUBLISH mode for publishing the data
Server::Server()
{
    m_context = zmq::context_t(1);
    m_socket = zmq::socket_t(m_context,ZMQ_PULL);

    n_context = zmq::context_t(1);
    n_socket = zmq::socket_t(n_context,ZMQ_PUB);
}

// Method to start the server by binding the sockets
void Server::startServer(int portL,int portR,std::string topicName)
{
    try
    {
        m_socket.bind("tcp://localhost:"+std::to_string(portL));
        n_socket.bind("tcp://localhost:"+std::to_string(portR));
        std::cout << "\nServer Listening on port : " << portL << " " << portR << std::endl; 
        n_topic = topicName;
    }
    catch(zmq::error_t& error)
    {
        std::cout << "Exception Raised In Server : " << error.what() << std::endl;
    }   
   
}

// Method to receive message from OpenCV client
void Server::receiveMessageFromClient()
{
    zmq::message_t payload;
    // cv::namedWindow("Received Frame At Server",cv::WINDOW_AUTOSIZE);
    FramePack packer;
    while(!appExit)
    {
        
        auto rc = m_socket.recv(payload,zmq::recv_flags::none);
        std::string frameStr = payload.to_string();
        if(frameStr.length() == 5)
            std::cout << "Client Connected" << std::endl;
        else if(frameStr.length() == 3)
            std::cout << "Client Disconnected" << std::endl;
        else
        {
            std::cout << "Alert Reached the Server" << std::endl;
            // packingStructure ps = packer.unpackFrame(frameStr);
            // cv::imshow("Received Frame At Server",cv::Mat(ps.height,ps.width,ps.type,ps.imgData.data()));
            sendMessageToClient(frameStr);
        }
        if(cv::waitKey(1) == 'q')
        {
            appExit = true;
        }    
        
    }
    
    cv::destroyAllWindows();    
    
}

// Method to send message to all the subscribers
void Server::sendMessageToClient(std::string &frameStr)
{
    zmq::message_t topicName(n_topic.size());
    zmq::message_t payload(frameStr.size());

    memcpy(topicName.data(),n_topic.data(),n_topic.size());
    memcpy(payload.data(),frameStr.data(),frameStr.size());

    auto rc = n_socket.send(topicName,zmq::send_flags::sndmore);
    rc = n_socket.send(payload, zmq::send_flags::none);
}

// Destructor to release the resources
Server::~Server()
{
    try
    {
        if(m_socket.handle() != nullptr)
        {
            m_socket.close();
        }
        m_context.shutdown();
    }
    catch(zmq::error_t e)
    {
        std::cout << e.what();
    }
}

void publish(Server* server)
{
    server->receiveMessageFromClient();
}

/*----------------------------------------------------------------------------- MAIN ---------------------------------------------------------------------------*/
int main()
{
    signal(SIGINT,ctrCHandler);
    Server server;
    server.startServer(PUSH_PULL_PORT,PUB_SUB_PORT,"Frames");
    
    std::thread t1(publish,&server);
    while(!appExit)
    {
        sleep(1);
    }
    return 0;
}