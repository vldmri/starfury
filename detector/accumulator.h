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
    static const int _defaultCapacity = 20;
    explicit Accumulator(const int capacity = _defaultCapacity) :
        _capacity(capacity), _num(0) {}
    ~Accumulator() {}
    const FrameBox& frame() const {return _frame;}
    const FrameBox& add(FrameBox&);
    void setCapacity(const int capacity) {_capacity = capacity;}
    int capacity() const {return _capacity;}
    int num()      const {return _num;}
private:
    static const double _alpha = 1.0;
    static const double _beta  = 1.0;
    FrameBox _frame;
    int      _capacity; //������� (���-�� ������������� ������)
    int      _num;      //������� ���-�� ����������� ������
    void checkSize(const Frame::Header&);
    void checkNum();
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // ACCUMULATOR_H
