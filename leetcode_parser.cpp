#include "leetcode_parser.hpp"

namespace _meguhine_leetcode {

// 实现：读取非空行（跳过空白字符）
std::string readNonEmptyLine() {
    std::string line;
    while (std::getline(std::cin, line)) {
        // 检查是否是非空白行
        if (std::any_of(line.begin(), line.end(), [](char c) { 
            return !std::isspace(c); 
        })) {
            return line;
        }
    }
    return "";
}

// 实现：去除字符串两端的空白字符
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

// 实现：便捷的解析函数，直接返回Parser对象
Parser parseLine(const std::string& line) {
    return Parser(line);
}

} // namespace _meguhine_leetcode