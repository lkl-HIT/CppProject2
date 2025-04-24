#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include <iostream>
#include <stdexcept>



template<typename T>
class myTinyDeque {
public:
    explicit myTinyDeque(size_t cap = 16)
        : _cap(cap), _size(0), _front(0), _back(0)
    {
        _data = new T[_cap];
    }

    ~myTinyDeque() {
        delete[] _data;
    }

    myTinyDeque(const myTinyDeque& other)
        : _cap(other._cap), _size(other._size), _front(other._front), _back(other._back)
    {
        _data = new T[_cap];
        for (size_t i = 0; i < _cap; ++i)
            _data[i] = other._data[i];
    }

    myTinyDeque& operator=(const myTinyDeque& other)
    {
        if (this != &other) {
            delete[] _data;
            _cap = other._cap;
            _size = other._size;
            _front = other._front;
            _back = other._back;
            _data = new T[_cap];
            for (size_t i = 0; i < _cap; ++i)
                _data[i] = other._data[i];
        }
        return *this;
    }

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

    void push_back(const T& value) {
        ensure_capacity();
        _data[_back] = value;
        _back = (_back + 1) % _cap;
        ++_size;
    }

    void push_front(const T& value) {
        ensure_capacity();
        _front = (_front + _cap - 1) % _cap;
        _data[_front] = value;
        ++_size;
    }

    void pop_back() {
        if (empty())
            throw std::out_of_range("pop_back() deque is empty!");
        _back = (_back + _cap - 1) % _cap;
        --_size;
    }

    void pop_front() {
        if (empty())
            throw std::out_of_range("pop_front() deque is empty!");
        _front = (_front + 1) % _cap;
        --_size;
    }

    T& front() {
        if (empty())
            throw std::out_of_range("front() deque is empty!");
        return _data[_front];
    }

    T& back() {
        if (empty())
            throw std::out_of_range("back() deque is empty!");
        return _data[(_back + _cap - 1) % _cap];
    }

    T& operator[](size_t idx) {
        if (idx >= _size)
            throw std::out_of_range("operator[] index out of range");
        // 注意环形缓冲区索引转换
        return _data[(_front + idx) % _cap];
    }

    const T& operator[](size_t idx) const {
        if (idx >= _size)
            throw std::out_of_range("operator[] index out of range");
        return _data[(_front + idx) % _cap];
    }

private:
    T* _data;
    size_t _cap, _size, _front, _back;

    void ensure_capacity() {
        if (_size == _cap) {
            size_t newcap = _cap * 2;
            T* newdata = new T[newcap];
            // 重新顺序存储
            for (size_t i = 0; i < _size; ++i) {
                newdata[i] = (*this)[i];
            }
            delete[] _data;
            _data = newdata;
            _cap = newcap;
            _front = 0;
            _back = _size;
        }
    }
};

#endif //MY_TINY_DEQUE_H