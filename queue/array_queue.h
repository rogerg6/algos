
#ifndef _ARRAY_QUEUE_H_
#define _ARRAY_QUEUE_H_

#include <stdexcept>

/**
 * \brief: 数组实现的固定长度的环形队列
 */
template<typename T>
class ArrayQueue {
public:
    ArrayQueue(int cap) {
        _data = new T[cap];
        if (!_data) throw std::runtime_error("New ArrayQueue failed");

        _head = _tail = _size = 0;
        _capcity              = cap;
    }
    ~ArrayQueue() {
        if (_data) delete[] _data;
    }

    void Push(T val) {
        if (_size >= _capcity) throw std::runtime_error("Queue is full");
        _data[_tail] = val;
        _tail        = (_tail + 1) % _capcity;
        _size++;
    }

    T Pop() {
        T val = Peek();
        _head = (_head + 1) % _capcity;
        _size--;
        return val;
    }

    T Peek() const {
        if (_size <= 0) throw std::runtime_error("Queue is empty");
        return _data[_head];
    }

    bool Empty() const { return _size <= 0; }
    int  Size() const { return _size; }

private:
    T  *_data;
    int _size;
    int _capcity;
    int _head, _tail;
};

#endif