#include "accumulator.h"
/////////////////////////////////////////////////////////////////////////////////////
void Accumulator::add(const Frame &f)
{

}
/////////////////////////////////////////////////////////////////////////////////////
void Accumulator::checkSize(const Frame::Header &newHeader)
{
    if(_frame.header() != newHeader)
    {
        _frame.setHeader(newHeader);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
