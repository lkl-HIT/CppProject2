#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>

template <typename T> class MyDeque {
public:
    //初始成员函数 
    //默认构造
    explicit MyDeque(size_t cap = 16):_cap(cap),_front(0),_back(0),_size(0){
        _data = new T[_cap];
    }

    ~MyDeque(){
        delete [] _data;
    }

    //拷贝构造
    MyDeque(const MyDeque& other){
        _data = new T[other._cap];
        for(size_t i=0;i<other._cap;i++)
            _data[i] = other._data[i];
        _front = other._front;
        _back = other._back;
        _size = other._size;
        _cap = other._cap;
    }

    //拷贝赋值
    MyDeque& operator=(const MyDeque& other){
        if(this!=&other){
            delete [] _data;
            _data = new T[other._cap];
            for(size_t i=0;i<other._cap;i++)
                _data[i] = other._data[i];
            _front = other._front;
            _back = other._back;
            _size = other._size;
            _cap = other._cap;
        }

        return *this;
    }


    //核心功能
    void push_front(const T& value){
        if(_size >= _cap)
            reserve(2*_cap);
        
        _front = (_front + _cap - 1) % _cap;
        _data[_front] = value;

        _size++;
    }

    void push_back(const T& value){
        if(_size >= _cap)
            reserve(2*_cap);
        _back = (_back + 1) % _cap;
        _data[_back] = value;

        _size++;
    }

    void pop_front(){
        if(empty())
            return;
        
        _front = (_front + 1) % _cap;
        _size --;
    }

    void pop_back(){
        if(empty())
            return;
        
        _back = (_back + _cap - 1) % _cap;
        _size --;
    }

    T& operator[](size_t n){
        if(n>=_size)
            throw std::out_of_range("[] out of range");
        return _data[(_front + n)%_cap];
    }

    void printDeque(){
        for(size_t i =0;i<_size;i++)
            std::cout << (*this)[i] << " ";
        std::cout << std::endl;
    }

    void clear(){
        _size=0;
        _front=0;
        _back=0;
    }

    bool empty(){
        return _size==0;
    }

    bool full(){
        return _front==_back;
    }

    size_t size(){
        return _size;
    }
    

private:
    size_t _cap;
    size_t _front;
    size_t _back;
    size_t _size;
    T* _data;

    void reserve(size_t newcap){
        T* newdata = new T[newcap];
        size_t cpy_st = (newcap - _cap)/2;
        //这个地方不仅要将数据放在新空间的中间，还要利用重载运算符的方法重新顺序排列
        for(size_t i = cpy_st;i<_cap+cpy_st;i++){
            newdata[i] = (*this)[i-cpy_st];
        }
            
        _front =  cpy_st;
        _back = _size + cpy_st;
        _cap = newcap;
    };
};