#include <sstream>
#include <string>
#include <iostream>

int main() {
    std::string data = "100 example";
    int number;
    std::string text;

    // 创建istringstream对象
    std::istringstream iss(data);

    // 从iss中提取整数和字符串
    iss >> number >> text;

    // 输出提取的结果
    std::cout << "Number: " << number << ", Text: " << text << std::endl;

    return 0;
}
