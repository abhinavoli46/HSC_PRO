# Fall Detection System Using OpenCV and Alert Messaging Using ZeroMQ.
## About the project:
* A simple fall detector that detects fall incidence using the YoloV5 object detection model, generates alert signals and publishes the alerts using the PUB-SUB model of the ZeroMQ networking library.
* It has 3 components: An OpenCV client component, a server component, and a subscriber component.
* Frames are captured at the client side when the fall is detected, then every frame is serialized using the msgpack library before sending it to the server.
* After the serialized string reaches to the server, it is published to all the subscribers.
* The subscriber component deserializes the received string and converts it back into a frame.

## Language Used
* C++

## Operating System
* Ubuntu 22.04.4 LTS (Jammy Jellyfish)

## Libraries Used:
* OpenCV (Compiled with CUDA 12.2.2 support, Version 4.8.1)
* CppZMQ
* MsgPack
* Boost Utility (Version 1.84)
* cuDNN (Version 8.9.4)
  
## Tools Used:
* Visual Studio Code
* CMake
  
