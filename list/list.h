
#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <stdexcept>

/**
 * 类似std::vector
 */
class List {
public:
    List()
        : _data(new int[1])
        , _size(0)
        , _capcity(1) {}

    ~List() {
        delete[] _data;
        _data    = nullptr;
        _size    = 0;
        _capcity = 0;
    }

    void Append(int val) {
        if (_size >= _capcity) {
            Resize(_capcity * 2);
        }
        _data[_size++] = val;
    }

    void Insert(int index, int val) {
        if (index < 0 || index >= _size) throw std::out_of_range("out of boundary");

        if (_size >= _capcity) {
            Resize(_capcity * 2);
        }
        for (int i = _size; i > index; --i) _data[i] = _data[i - 1];
        _data[index] = val;
        ++_size;
    }

    void Remove(int index) {
        if (index < 0 || index >= _size) throw std::out_of_range("out of boundary");

        for (int i = index; i < _size - 1; ++i) _data[i] = _data[i + 1];
        _size--;

        if (_size < _capcity / 4) {
            Resize(_capcity / 2);
        }
    }

    void Resize(int new_cap) {
        int *new_data = new int[new_cap];
        assert(new_data != nullptr);

        for (int i = 0; i < _size; ++i) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data    = new_data;
        _capcity = _capcity * 2;
    }

    unsigned int Size() const { return _size; }

private:
    int         *_data;
    unsigned int _size;
    unsigned int _capcity;
};

#endif