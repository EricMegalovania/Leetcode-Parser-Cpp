#ifndef __LEETCODE_PARSER_HPP__
#define __LEETCODE_PARSER_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>

namespace leetcode_parser {

	namespace internal_basic {
		inline std::string readLine(std::istream& is) {
			std::string line;
			while(std::getline(is, line)){
				if (std::any_of(line.begin(), line.end(), [](char c)-> bool { 
					return !std::isspace(c); 
				})) {
					return line;
				}
			}
			return "";
		}
		inline void skipWhitespace(std::istream& is) {
			while (std::isspace(is.peek())) is.get();
		}
		inline char peekNextChar(std::istream& is) {
			return static_cast<char>(is.peek());
		}
		inline bool isVectorStart(char ch) {
			return ch == '[';
		}
		inline bool isVectorEnd(char ch) {
			return ch == ']';
		}
		inline bool isSeparator(char ch) {
			return ch == ',';
		}
	} // namespace internal_basic
	
	namespace internal_parser{
		using namespace internal_basic;

		template <typename T>
		T _parse(std::istream& is) {
			skipWhitespace(is);
			T value; is >> value;
			return value;
		}
		
		template <>
		inline bool _parse<bool>(std::istream& is) {
			skipWhitespace(is);
			std::string str;
			is >> str;
			if (str == "true") {
				return true;
			} else if (str == "false") {
				return false;
			} else {
				throw std::invalid_argument("Invalid boolean value: " + str);
			}
		}
		
		template <>
		inline std::string _parse<std::string>(std::istream& is) {
			std::string result; char ch;
			skipWhitespace(is);
			is >> ch;
			if (ch != '"') {
				throw std::invalid_argument("String must START with a quote");
			}
			bool end_with_quote = false;
			while (is.get(ch)) {
				if (ch == '"') {
					end_with_quote = true;
					break;
				}
				if (ch == '\\') {
					if (is.get(ch)) {
						switch (ch) {
							case 'n': result += '\n'; break;
							case 't': result += '\t'; break;
							case 'r': result += '\r'; break;
							case '\\': result += '\\'; break;
							case '"': result += '"'; break;
							default: result += ch; break;
						}
					}
				} else {
					result += ch;
				}
			}
			if (!end_with_quote) {
				throw std::invalid_argument("String must END with a quote");
			}
			return result;
		}
		
		template <>
		inline char _parse<char>(std::istream& is) {
			std::string str = _parse<std::string>(is);
			if (str.length() != 1) {
				throw std::invalid_argument("Invalid char input: " + str + ", char length: " + std::to_string(str.length()));
			}
			return str[0];
		}
		
		template <typename T>
		std::vector<T> _parseVector(std::istream& is) {
			std::vector<T> result;
			skipWhitespace(is);
			if (!isVectorStart(peekNextChar(is))) {
				throw std::invalid_argument("Vector must start with '['");
			} else {
				is.get();
			}
			
			skipWhitespace(is);
			if(is.eof()) {
				throw std::invalid_argument("Vector must end with ']'");
			}
			if (isVectorEnd(peekNextChar(is))) {
				is.get();
				return result;
			}

			while (true) {
				skipWhitespace(is);
				if (isVectorStart(peekNextChar(is))) {
					throw std::invalid_argument("Unexpected nested vector in vector");
				} else {
					result.emplace_back(_parse<T>(is));
				}
				
				skipWhitespace(is);
				if (isVectorEnd(peekNextChar(is))) {
					is.get(); break;
				} else if (isSeparator(peekNextChar(is))) {
					is.get();
				} else {
					throw std::invalid_argument("Expected ',' or ']' after vector element");
				}
			}
			
			return result;
		}
		
		template <typename T>
		std::vector<std::vector<T>> _parseVector2D(std::istream& is) {
			std::vector<std::vector<T>> result;

			skipWhitespace(is);
			if (!isVectorStart(peekNextChar(is))) {
				throw std::invalid_argument("2D vector must start with '['");
			} else {
				is.get();
			}
			
			skipWhitespace(is);
			if (isVectorEnd(peekNextChar(is))) {
				is.get();
				return result;
			}
			
			while (true) {
				skipWhitespace(is);
				if (isVectorStart(peekNextChar(is))) {
					result.emplace_back(_parseVector<T>(is));
				} else {
					throw std::invalid_argument("Expected '[' at start of 2D vector row");
				}
				
				skipWhitespace(is);
				if (isVectorEnd(peekNextChar(is))) {
					is.get(); break;
				} else if (isSeparator(peekNextChar(is))) {
					is.get();
				} else {
					throw std::invalid_argument("Expected ',' or ']' after 2D vector row");
				}
			}
			
			return result;
		}
	} // namespace internal_parser
	
	template <typename T>
	T parse() {
		std::string line=internal_basic::readLine(std::cin);
		std::istringstream iss(line);
		return internal_parser::_parse<T>(iss);
	}
	
	template <typename T>
	std::vector<T> parseVector() {
		std::string line=internal_basic::readLine(std::cin);
		std::istringstream iss(line);
		return internal_parser::_parseVector<T>(iss);
	}
	
	template <typename T>
	std::vector<std::vector<T>> parseVector2D() {
		std::string line=internal_basic::readLine(std::cin);
		std::istringstream iss(line);
		return internal_parser::_parseVector2D<T>(iss);
	}
	
} // namespace leetcode_parser

namespace leetcode_vector_printer {

	template<typename T>
	void printElement(const T& element) {
		std::cout << element;
	}

	template<typename T>
	void printElement(const std::vector<T>& element) {
		printVector("", element, false);
	}
	
	template<typename T>
	void printVector(const std::string& name, const std::vector<T>& vec, bool printName = true, bool printEndl = true) {
		if (printName) {
			std::cout << name << " = ";
		}
		
		std::cout << "[";
		for (size_t i = 0; i < vec.size(); ++i) {
			printElement(vec[i]);
			if (i != vec.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << "]";
		if (printEndl) {
			std::cout << std::endl;
		}
	}

	template<typename T>
	void printVector2D(const std::string& name, const std::vector<std::vector<T>>& vec2D, bool printName = true) {
		if (printName) {
			std::cout << name << " = ";
		}
		
		std::cout << "[" << std::endl;
		for (size_t i = 0; i < vec2D.size(); ++i) {
			std::cout << "  ";
			printVector("", vec2D[i], false, false);
			if (i != vec2D.size() - 1) {
				std::cout << ",";
			}
			std::cout << std::endl;
		}
		std::cout << "]" << std::endl;
	}

} // namespace leetcode_vector_printer

#endif // __LEETCODE_PARSER_HPP__