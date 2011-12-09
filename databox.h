#ifndef DATABOX_H
#define DATABOX_H
/////////////////////////////////////////////////////////////////////////////////////
#include <QReadWriteLock>
#include <QDateTime>
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
template<typename T> class DataBox
{
public:
    explicit DataBox();
    explicit DataBox(const DataBox<T>&);
    DataBox<T>& operator =(const DataBox<T>&);
    T&              data()             {return _data;}
    QReadWriteLock& lock()             {return _lock;}
    QDateTime&      timeMarker()       {return _marker;}
private:
    T              _data;
    QReadWriteLock _lock;
    QDateTime      _marker;
};
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
template<typename T>
DataBox<T>::DataBox()
{
    _marker = QDateTime::currentDateTime();
}
/////////////////////////////////////////////////////////////////////////////////////
template<typename T>
DataBox<T>::DataBox(const DataBox<T> &other)
{
    this->_data = other._data;
    this->_marker = other._marker;
}
/////////////////////////////////////////////////////////////////////////////////////
template<typename T>
DataBox<T>& DataBox<T>::operator =(const DataBox<T> &other)
{
    if(this != &other)
    {
        this->_data = other._data;
        this->_marker = other._marker;
    }
    return *this;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#endif // DATABOX_H
