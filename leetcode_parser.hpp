#ifndef __MEGUHINE_LEETCODE_PARSER
#define __MEGUHINE_LEETCODE_PARSER

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <type_traits>

namespace _meguhine_leetcode {

// 声明：读取非空行（跳过空白字符）
std::string readNonEmptyLine();

// 声明：去除字符串两端的空白字符
std::string trim(const std::string& str);

// 类型特征检查
template<typename T>
struct is_string : std::false_type {};

template<>
struct is_string<std::string> : std::true_type {};

template<typename T>
struct is_vector : std::false_type {};

template<typename T>
struct is_vector<std::vector<T>> : std::true_type {};

// 主解析模板
template<typename T>
T parse(const std::string& line);

// 特化：解析基本类型（int, double, float, long等）
template<typename T>
typename std::enable_if<!is_string<T>::value && !is_vector<T>::value, T>::type
parse(const std::string& line) {
    std::string trimmed = trim(line);
    if (trimmed.empty()) return T();
    
    std::istringstream iss(trimmed);
    T result;
    iss >> result;
    return result;
}

// 特化：解析std::string
template<>
std::string parse<std::string>(const std::string& line) {
    std::string trimmed = trim(line);
    if (trimmed.empty()) return "";
    
    // 如果字符串被引号包围，去除引号
    if (trimmed.size() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
        return trimmed.substr(1, trimmed.size() - 2);
    }
    return trimmed;
}

// 特化：解析char
template<>
char parse<char>(const std::string& line) {
    std::string trimmed = trim(line);
    if (trimmed.empty()) return '\0';
    
    // 如果字符被单引号包围，去除引号
    if (trimmed.size() >= 2 && trimmed.front() == '\'' && trimmed.back() == '\'') {
        return trimmed[1];
    }
    return trimmed[0];
}

// 解析一维vector
template<typename T>
std::vector<T> parseVector(const std::string& line) {
    std::vector<T> result;
    std::string str = trim(line);
    
    if (str.empty() || str.front() != '[' || str.back() != ']') {
        return result;
    }
    
    // 去除方括号
    str = str.substr(1, str.size() - 2);
    std::istringstream iss(str);
    std::string token;
    
    while (std::getline(iss, token, ',')) {
        token = trim(token);
        if (!token.empty()) {
            result.push_back(parse<T>(token));
        }
    }
    
    return result;
}

// 解析二维vector
template<typename T>
std::vector<std::vector<T>> parseVector2D(const std::string& line) {
    std::vector<std::vector<T>> result;
    std::string str = trim(line);
    
    if (str.empty() || str.front() != '[' || str.back() != ']') {
        return result;
    }
    
    // 去除最外层方括号
    str = str.substr(1, str.size() - 2);
    
    // 解析每个一维数组
    size_t start = 0;
    size_t depth = 0;
    
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '[') {
            if (depth == 0) start = i;
            depth++;
        } else if (str[i] == ']') {
            depth--;
            if (depth == 0) {
                // 找到一个完整的一维数组
                std::string subArray = str.substr(start, i - start + 1);
                result.push_back(parseVector<T>(subArray));
            }
        }
    }
    
    return result;
}

// 便捷函数：自动检测类型并解析
template<typename T>
T parseLine(const std::string& line) {
    return parse<T>(line);
}

template<typename T>
std::vector<T> parseLineToVector(const std::string& line) {
    return parseVector<T>(line);
}

template<typename T>
std::vector<std::vector<T>> parseLineToVector2D(const std::string& line) {
    return parseVector2D<T>(line);
}

// 便捷的链式解析函数
class Parser {
private:
    std::string line_;

public:
    Parser(const std::string& line) : line_(line) {}
    
    template<typename T>
    T as() const {
        return parse<T>(line_);
    }
    
    template<typename T>
    std::vector<T> asVector() const {
        return parseVector<T>(line_);
    }
    
    template<typename T>
    std::vector<std::vector<T>> asVector2D() const {
        return parseVector2D<T>(line_);
    }
};

// 声明：便捷的解析函数，直接返回Parser对象
Parser parseLine(const std::string& line);

} // namespace _meguhine_leetcode

#endif // __MEGUHINE_LEETCODE_PARSER