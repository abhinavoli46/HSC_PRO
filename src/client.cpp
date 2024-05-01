#include <iostream>
#include "framepack.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <signal.h>
#include <thread>
#include <client.hpp>
#include <string>
#include <sstream>

using namespace cv;
using namespace dnn;

const int CLIENT_PORT = 5000;

bool appExit = false;
void ctrCHandler(int signal)
{
    appExit = true;
}

/*------------------------------------------------------------------------ OPENCV CLIENT CLASS METHODS----------------------------------------------------------------------------*/

// Client constructor for socket creation using PUSH PULL mode of communication
Client::Client()
{
    m_context = zmq::context_t(1);
    m_socket = zmq::socket_t(m_context,ZMQ_PUSH);   
}

// Method to connect client object to the server
void Client::connect(const int& port)
{
    try
    {
        m_socket.connect("tcp://localhost:" + std::to_string(port));
        std::cout << "Connecting to port " << port << "..." << std::endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

// Method to send frame data to the server
void Client::sendMessageToServer(std::string& frameStr)
{   
    try
    {
        zmq::message_t payload(frameStr.size());
        memcpy(payload.data(),frameStr.data(),frameStr.size());
        m_socket.send(payload,zmq::send_flags::none);
    }
    catch(std::exception& e)
    {
        std::cout << "Exception while sending : " << e.what();
        return;
    }
}
    
// Destructor
Client::~Client()
{
    try
    {
        if(m_socket.handle() != nullptr)
        {
            std::string test = "bye";
            sendMessageToServer(test);
            m_socket.close();
            std::cout << "Socket Closed" << std::endl;
            m_context.shutdown();
            std::cout << "Context Shutdown" << std::endl;
        }  
    }
    catch(zmq::error_t e)
    {
        std::cout << e.what();
    }
}

/*------------------------------------------------------------------------ OPENCV OBJECT DETECTION ----------------------------------------------------------------------------*/

// Vector of colors for object boundary
const std::vector<cv::Scalar> colors = {cv::Scalar(255, 255, 0), cv::Scalar(234, 255, 0), cv::Scalar(0, 255, 212), cv::Scalar(255, 0, 123) };
// Width and Height for the blob size
const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;

// Threshold to filter low probability class scores
const float SCORE_THRESHOLD = 0.2;
//  This threshold used for non-maximum suppression to remove overlapping bounding boxes
const float NMS_THRESHOLD = 0.4;
// Threshold level an object should have for detecting an object in the frame and displaying it   
const float CONFIDENCE_THRESHOLD = 0.4;   
// Particular Structure for a detected object
struct Detection
{
    int class_id;
    float confidence;
    Rect box;
};

// Function to extract class names from COCO dataset used in YoloV5 object detection model
std::vector<std::string> load_classes()
{
    //Reading a list of class names from the file which in "Models/classes.txt" and keeping them in a vector
    std::vector<std::string> class_list;
    std::ifstream ifs("/home/linos/Client-Server-Model/Resources/classes.txt");
    std::string line;
    while (getline(ifs, line))
    {
        class_list.push_back(line);
    }
    return class_list;
}

/*
Function to perform padding on input images as images need to be of fixed dimensions for YoloV5. 
Padding ensures that images of different aspect ratios are resized without distortion.
*/
Mat format_yolov5(const Mat& source)
{
    int col = source.cols;
    int row = source.rows;
    int _max = MAX(col, row);
    Mat result = Mat::zeros(_max, _max, CV_8UC3);
    source.copyTo(result(Rect(0, 0, col, row)));
    return result;
}

//Function of obejct detection in an image frame
/*
    Performs object detection on a video media using the YOLOv5 model
    
    Processes the model outputs to extract class IDs, confidences, and bounding box coordinates
    Applies confidence and threshold filtering and performs non-maximum suppression to eliminate redundant detections
*/
void detect(Mat& image, Net& net, std::vector<Detection>& output, const std::vector<std::string>& className) 
{
    Mat blob;
    auto input_image = format_yolov5(image);
    // Converts  the  input  images  to  a 4D-blob  suitable  for model input
    blobFromImage(input_image, blob, 1. / 255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);
    net.setInput(blob);
    // Vector for storing the output from model
    std::vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());

    float x_factor = input_image.cols / INPUT_WIDTH;
    float y_factor = input_image.rows / INPUT_HEIGHT;

    //Get pointer to the data of first tensor from output vector
    float* data = (float*)outputs[0].data;

    // 80 class scores 4 box locations(x,y,width,height) objectness score. 
    const int dimensions = 85;
    // No of candidate bounding boxes
    const int rows = 25200;

    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<Rect> boxes;

    for (int i = 0; i < rows; ++i) {

        float confidence = data[4];
        if (confidence >= CONFIDENCE_THRESHOLD) {

            float* classes_scores = data + 5;
            Mat scores(1, className.size(), CV_32FC1, classes_scores);
            Point class_id;
            double max_class_score;
            minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            if (max_class_score > SCORE_THRESHOLD) {

                confidences.push_back(confidence);

                class_ids.push_back(class_id.x);

                float x = data[0];
                float y = data[1];
                float w = data[2];
                float h = data[3];

                // Width, height and x,y coordinates of bounding box

                int left = int((x - 0.5 * w) * x_factor);
                int top = int((y - 0.5 * h) * y_factor);
                int width = int(w * x_factor);
                int height = int(h * y_factor);

                boxes.push_back(Rect(left, top, width, height));
            }

        }
        data += 85;

    }
    // NMS algorithm helps in reducing multiple 
    // detections of the same object by suppressing overlapping 
    // bounding boxes, thus giving more accurate and concise results.
    std::vector<int> nms_result;
    NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);
    for (int i = 0; i < nms_result.size(); i++) {
        int idx = nms_result[i];
        Detection result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }
}



/*------------------------------------------------------------------------ MAIN FUNCTION ----------------------------------------------------------------------------*/

int main()
{
    
    signal(SIGINT,ctrCHandler);
    Client client;
    client.connect(CLIENT_PORT);
    /*----------------------------------------------------  Attempt to send a test message to verify the connection -------------------------------------*/
    try
    {
        std::string test = "hello";
        client.sendMessageToServer(test);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    /*--------------------------------------------------------------------- OPENCV CODE----------------------------------------------------------------------*/

    FramePack packer;
    packer.setPackingStructureMeta("Frames");
    int errCode = 0;

    std::vector<std::string> class_list = load_classes();
    Mat frame;
    VideoCapture capture("/home/linos/Client-Server-Model/Resources/fall.mp4");
    if (!capture.isOpened())
    {
        std::cerr << "Error while opening video media\n";
        return -1;
    }

    Net net;
    auto result = readNetFromONNX("/home/linos/Client-Server-Model/Resources/yolov5m.onnx");
    net = result;
    result.setPreferableBackend(DNN_BACKEND_CUDA);
    result.setPreferableTarget(DNN_TARGET_CUDA_FP16);
    auto start = std::chrono::high_resolution_clock::now();
    int frame_count = 0;
    float fps = -1;
    int total_frames = 0;

    int targetWidth = 800; // Adjust the desired width
    int time = 0;          // Variable to keep a threshold of time when to send alert


    while(!appExit)
    {
        capture.read(frame);
        if (frame.empty())
        {
            std::cout << "Media finished\n";
            break;
        }
        std::vector<Detection> output;

        detect(frame, net, output, class_list);

        frame_count++;
        total_frames++;

        //Total number of objects detected in the current frame
        int detections = output.size();

         for (int i = 0; i < detections; ++i)
        {
            auto detection = output[i];
            auto box = detection.box;
            auto classId = detection.class_id;
            float confidence = detection.confidence;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << confidence;
            std::string text = ss.str();
            
            const auto color = colors[classId % colors.size()];
            rectangle(frame, box, color, 1);

            cv::rectangle(frame, cv::Point(box.x, box.y - 20), cv::Point(box.x + box.width, box.y), color, cv::FILLED);
            putText(frame, class_list[classId].c_str(), Point(box.x, box.y - 5), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
            putText(frame, text, Point(box.x , box.y - 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
            
            //Logic for fall detection and sending alert
            float ratio = (box.width /(1.0 * box.height));
            
            if (detection.class_id == 0)
            {
                if (ratio > 0 && ratio <= 0.6)
                {
                    putText(frame, "Stable", Point(box.x-55, box.y + 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(20, 255, 57));
                    time = 0;
                }
                else if (ratio >= 1.101)
                {
                    putText(frame, "Fall", Point(box.x-55, box.y + 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(130, 0, 75));
                    putText(frame, "Detected", Point(box.x-55, box.y + 35), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(130, 0, 75));
                    time++;
                }

                if (time > 20)
                {
                    
                    
                    std::string frameStr = packer.packFrame(frame,errCode);
                    assert(!frameStr.empty());
                    
                    client.sendMessageToServer(frameStr);
                    time = 0;
                    
                    std::cout << "Sending Alert" << std::endl;
                    break;
                }

            }    
        }
        //Update the fps text after each 30 frame count.
        if (frame_count >= 30)
        {
            auto end = std::chrono::high_resolution_clock::now();
            fps = frame_count * 1000.0 / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            frame_count = 0;
            start = std::chrono::high_resolution_clock::now();
        }

        if (fps > 0)
        {
            std::ostringstream fps_label;
            fps_label << std::fixed << std::setprecision(2);
            fps_label << "FPS: " << fps;
            std::string fps_label_str = fps_label.str();

            putText(frame, fps_label_str.c_str(), Point(10, 25), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
        }

        // Resize the frame with it's new shape as it's original ratio
        int targetHeight = static_cast<int>(frame.rows * static_cast<float>(targetWidth) / frame.cols);
        Size newSize(targetWidth, targetHeight);
        Mat resized_frame;
        resize(frame, resized_frame, newSize);   
        imshow("output", resized_frame);
        int key = cv::waitKey(1);
        if (key == 'q') // q to exit
        {
            appExit = true;
        }
    }

    std :: cout << "Control Returned to main" << std:: endl;
    return 0;
}
