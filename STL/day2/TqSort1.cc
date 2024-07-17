#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector; 

template<typename T, typename Compare = std::less<T>>
class MyQsort {
public:
    MyQsort(T *arr, size_t size) : MyQsort(arr, size, Compare()) {}

    MyQsort(T *arr, size_t size, Compare com) {
        for (size_t i = 0; i < size; ++i) {
            _vec.push_back(arr[i]);
        }
    }

    void quick(int left, int right);
    int partition(int left, int right);
    void print();

private:
    std::vector<T> _vec;
    Compare _com; 
};

template<typename T, typename Compare>
void MyQsort<T, Compare>::quick(int left, int right) {
    if (left < right) {
        int mid = partition(left, right);
        quick(left, mid - 1);
        quick(mid + 1, right);
    }
}

template<typename T, typename Compare>
int MyQsort<T, Compare>::partition(int left, int right) {
    T pivot = _vec[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (!_com(_vec[j], pivot)) {
            i++;
            std::swap(_vec[i], _vec[j]);
        }
    }
    std::swap(_vec[i + 1], _vec[right]);
    return i + 1;
}

template<typename T, typename Compare>
void MyQsort<T, Compare>::print() {
    for (const auto &elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}

int main() {
    int arr[11] = {4, 5, 3, 2, 1, 12,3243,5253,1213,11,0};
    MyQsort<int> q1(arr, 11);
    q1.quick(1, 7);
    q1.print();
}
