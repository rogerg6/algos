
#ifndef _ARRAY_DEQUE_H
#define _ARRAY_DEQUE_H

#include <stdexcept>

class ArrayDeque {

public:
    ArrayDeque(int cap) {
        _data = new int[cap];
        if (!_data) throw std::runtime_error("New ArrayQueue failed");

        _head = _tail = _size = 0;
        _capcity              = cap;
    }
    ~ArrayDeque() {
        if (_data) delete[] _data;
    }

    void PushHead(int val) {
        if (_size >= _capcity) throw std::runtime_error("Queue is full");
        _head        = (_head - 1 + _capcity) % _capcity;
        _data[_head] = val;
        _size++;
    }
    void PushTail(int val) {
        if (_size >= _capcity) throw std::runtime_error("Queue is full");
        _data[_tail] = val;
        _tail        = (_tail + 1) % _capcity;
        _size++;
    }

    int PopHead() {
        int val = PeekHead();
        _head   = (_head + 1) % _capcity;
        _size--;
        return val;
    }
    int PopTail() {
        int val = PeekTail();
        _tail   = (_tail - 1 + _capcity) % _capcity;
        _size--;
        return val;
    }

    int PeekHead() const {
        if (_size <= 0) throw std::runtime_error("Queue is empty");
        return _data[_head];
    }
    int PeekTail() const {
        if (_size <= 0) throw std::runtime_error("Queue is empty");
        int tail = (_tail - 1 + _capcity) % _capcity;
        return _data[tail];
    }

    bool Empty() const { return _size <= 0; }
    int  Size() const { return _size; }

private:
    int *_data;
    int  _size;
    int  _capcity;
    int  _head, _tail;
};



#endif