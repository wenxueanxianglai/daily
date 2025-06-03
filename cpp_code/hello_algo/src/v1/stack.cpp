#include <stack>

int main() {

    // 初始化
    std::stack<int> stack;

    // 入栈
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    // 访问栈顶元素
    int top = stack.top();

    //元素出栈
    stack.pop();

    // 获取栈的长度
    int size = stack.size();


    bool is_empty = stack.empty();

    

    return 0;
}