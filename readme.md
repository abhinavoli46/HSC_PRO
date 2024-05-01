Fall Detection System Using OpenCV and Alert Messaging Using ZeroMQ.
+ About the project:
  -> A simple fall detector that detects fall incidence using YoloV5 object detection model, generates alert signals and publishes the alerts using PUB-SUB model of ZeroMQ networking library.
  -> It has 3 components : An OpenCV client component, a server component and a subscriber component.
  -> Frames are captured at client side when the fall is detected, then every frame is serialized using msgpack library before sending 
    to the server. 
  -> After reaching to the server, the serialized string is published to all the subscribers where again it is deserialized and is 
    developed back into frames.

+ Language Used: C++

+ Operating System: Ubuntu 22.04.4 LTS (Jammy Jellyfish)

+ Libraries Used:
  -> OpenCV (Compiled with CUDA 12.2.2 support, Version 4.8.1)
  -> CppZMQ
  -> MsgPack
  -> Boost Utility (Version 1.84)
  -> cuDNN (Version 8.9.4)

+ Tools Used:
  -> Visual Studio Code
  -> CMake
