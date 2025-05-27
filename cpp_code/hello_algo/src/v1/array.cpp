#include <cstdio>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/format.h>
// 随机访问元素
int randomAccess(int* nums, int size) {
    int randomIdx = rand() % size;

    int resNum = nums[randomIdx];
    return resNum;
}

// 插入元素
void  insert(int* nums, int size, int num, int index) {
    for(int i = size - 1; i > index; i--) {
        nums[i] = nums[i - 1];
    }

    nums[index] = num;
}

// 删除元素
void remove(int* nums, int size, int index) {
    for(int i = index; i < size -1; ++i) {
        nums[i] = nums[i + 1];
    }
}


// 遍历数组
void traverse(int* nums, int size) {
    int count = 0;

    for(int i = 0; i < size; ++i) {
        count += nums[i];
    }
}

// 查找元素
int find(int* nums, int size, int target) {
    for(int i = 0; i < size; ++i) {
        if(nums[i] == target) {
            return i;
        }
    }

    return -1;
}

// 扩展数组长度
int* extend(int* nums, int size, int enlarge) {
    int* res = new int[size + enlarge];

    for(int i = 0; i < size; ++i) {
        res[i] = nums[i];
    }

    delete [] nums;
    return res;
}

int main() {
    // init
    int arr[5];
    int nums[5] = {1, 2, 3, 4, 5};

    // test access
    int num = randomAccess(nums, 5);
    fmt::println("access by rand is : {}", num);

    // test insert
    insert(nums, 5, 10, 1);
    for(int i = 0; i < 5; ++i) {
        fmt::print("{}, ", nums[i]);
    }
    fmt::println("");


    // test remove
    remove(nums, 5, 1);

    for(int i = 0; i < 5; ++i) {
        fmt::print("{}, ", nums[i]);
    }
    fmt::println("");

    // test traverse
    traverse(nums, 4);

    
    // test find
    int index = find(nums, 4, 2);
    fmt::println("target index : {}, value:{}", index, nums[index]);



    int* arr1 = new int[5];
    int* nums1 = new int[5]{1, 2, 3, 4, 5};

    // test extend
    nums1 = extend(nums1, 5, 2);
    nums1[5] = 6;
    nums1[6] = 7;
    for(int i = 0; i < 7; ++i) {
        fmt::print("{}, ", nums1[i]);
    }
    fmt::println("");

    delete[] arr1;
    delete[] nums1;


    return 0;
}