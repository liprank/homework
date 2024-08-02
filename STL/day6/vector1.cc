#include <iostream>
#include <stdexcept>
#include <memory>

template<typename T>
class Vector {
public:
    Vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
        _start = _alloc.allocate(8);
        _finish = _start;
        _end_of_storage = _start + 8;
    }

    ~Vector() {
        _alloc.deallocate(_start, _end_of_storage - _start);
    }

    void push_back(const T& value) {
        if (_finish != _end_of_storage) {
            *_finish++ = value;
        } else {
            reallocate();
            *_finish++ = value;
        }
    }

    void pop_back() {
        if (size() > 0) {
            --_finish;
        }
    }

    int size() const {
        return _finish - _start;
    }

    int capacity() const {
        return _end_of_storage - _start;
    }

    T& operator[](int idx) {
        if (idx >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return _start[idx];
    }

    const T& operator[](int idx) const {
        if (idx >= size()) {
            throw std::out_of_range("Index out of range");
        }
        return _start[idx];
    }

private:
    void reallocate() {
        T* new_start = _alloc.allocate(2 * (_end_of_storage - _start));
        T* new_finish = new_start;
        for (T* it = _start; it != _finish; ++it) {
            _alloc.construct(new_finish, *it);
            ++new_finish;
        }
        _alloc.deallocate(_start, _end_of_storage - _start);
        _start = new_start;
        _finish = new_finish;
        _end_of_storage = new_start + 2 * (_end_of_storage - _start);
    }

private:
    static std::allocator<T> _alloc;
    T* _start;
    T* _finish;
    T* _end_of_storage;
};

template<typename T>
std::allocator<T> Vector<T>::_alloc;//静态成员的初始化

void test() {
    Vector<int> v1;
    v1.push_back(10);
    v1.push_back(9);
    v1.push_back(8);
    v1.push_back(7);
    v1.push_back(6);
    v1.push_back(5);
    v1.push_back(4);
    v1.push_back(3);
    v1.push_back(2);

    v1.push_back(1);
    v1.push_back(0);

    for (int i = 0; i < v1.size(); ++i) {
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    test();
    return 0;
}
