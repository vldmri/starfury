#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#include "opencv.hpp"
#include "boxes/frame.h"
/////////////////////////////////////////////////////////////////////////////////////
class Accumulator
{
public:
    explicit Accumulator() {}
    ~Accumulator() {}
    const Frame& frame() const {return _frame;}
    void add(const Frame&);
private:
    Frame _frame;
    void checkSize(const Frame::Header&);
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // ACCUMULATOR_H
