#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <stdexcept>

class MyList {
public:
MyList() {
    arr_ = new int[capacity_];
}

~MyList() {
    delete [] arr_;
}

int size() const {return size_; }
int capacity() const {return capacity_;}

int get(int index) {
    if(index < 0 || index >= size()) throw std::out_of_range("索引越界");
    return arr_[index];
}

void set(int index, int num) {
    if(index < 0 || index >= size()) throw std::out_of_range("索引越界");
    arr_[index] = num;
}

void insert(int index, int num) {
    if(index < 0 || index >= size()) throw std::out_of_range("索引越界");

    if(size() == capacity()) {
        exten
    }
}

private:

int* arr_;
int capacity_{10};
int size_{0};
int extend_ratio_{2};
};

int main() {

    return 0;
}