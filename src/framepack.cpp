#include "framepack.hpp"
#include <msgpack.hpp>

/*------------------------------------------------------------ FRAMEPACK CLASS METHODS ------------------------------------------------------------------*/

FramePack::FramePack(){}

void FramePack::setPackingStructureMeta(std::string source)
{
    ps.source = source;
}

// Method to pack the frame
std::string FramePack::packFrame(const cv::Mat &frame, int &error)
{   
    ps.height  = frame.rows;
    ps.width   = frame.cols;
    ps.channels = frame.channels();
    ps.dims = frame.dims;
    ps.type    = frame.type();
    ps.imgData = std::vector<uchar>(frame.data,frame.data + (frame.rows*frame.cols*frame.channels()));

    std::stringstream ss;
    msgpack::pack(&ss, ps);
    return ss.str();
}

// Method to unpack the frame
packingStructure FramePack::unpackFrame(std::string &packStr)
{
    auto objectHandle = msgpack::unpack(packStr.data(), packStr.size());
    auto obj = objectHandle.get();
    packingStructure ps = obj.as<packingStructure>();
    return ps;
}
