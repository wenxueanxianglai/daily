#include <memory>
#include <unordered_map>
#include <iostream>
using namespace std;

int main() {
   // std::shared_ptr<int> p;
    std::unordered_map<std::string, std::shared_ptr<int>> map;


    auto& it2 = map["insert_can\0uild"];
    //std::cout << "value2 : " << it2 << std::endl;

    auto& it = map["insert_can"];

    if(it2 == nullptr) {
        it2 = make_shared<int>(1);
    }

    if(it == nullptr) {
        it = make_shared<int>(2);//..>(Args &&args...)
    }

    //it = 2;
    //std::cout << "value: " << it << std::endl;

    return 0;
}