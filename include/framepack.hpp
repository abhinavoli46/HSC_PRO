#ifndef FRAMEPACK_H
#define FRAMEPACK_H

#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <string>
#include <msgpack.hpp>
#include <vector>
#include <iostream>

/*------------------------------------------------------------ FRAMEPACK CLASS DEFINITION ------------------------------------------------------------------*/

struct packingStructure
{
    uint16_t height;
    uint16_t width;
    uint16_t type;
    uint16_t channels;
    uint16_t dims;
    std::vector<uchar> imgData;
    std::string source;
    // Macro provided for MessagePack Library, instruct how a struct or class should be 
    // serialized into MessagePack format.
    MSGPACK_DEFINE(height, width, type, channels, dims, imgData, source);
};

class FramePack
{
    private:
        packingStructure ps;
    public:
        FramePack();
        void setPackingStructureMeta(std::string source);
        std::string packFrame(const cv::Mat& frame, int& error);
        packingStructure unpackFrame(std::string& packStr);
};
#endif
