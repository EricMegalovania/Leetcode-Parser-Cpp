#ifndef __LEETCODE_PARSER_HPP__
#define __LEETCODE_PARSER_HPP__

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <optional>
#include <type_traits>

namespace internal_vector_depth {

	template <typename T>
	struct vector_depth {
		static constexpr int value = 0;
		using inner_type = T;
	};

	template<typename T>
	struct vector_depth<std::vector<T>> {
		static constexpr int value = 1 + vector_depth<T>::value;
		using inner_type = typename vector_depth<T>::inner_type;
	};

} // namespace internal_vector_depth

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
		constexpr int depth = internal_vector_depth::vector_depth<T>::value;
		// std::cerr << "[parse] type name: " << typeid(T).name() << " depth: " << depth << std::endl;
		using _T = typename internal_vector_depth::vector_depth<T>::inner_type;
		std::string line=internal_basic::readLine(std::cin);
		std::istringstream iss(line);
		if constexpr (depth == 0) {
			return internal_parser::_parse<_T>(iss);
		} else if constexpr (depth == 1) {
			return internal_parser::_parseVector<_T>(iss);
		} else if constexpr (depth == 2) {
			return internal_parser::_parseVector2D<_T>(iss);
		} else {
			throw std::invalid_argument("Unsupported vector depth");
		}
	}
	
} // namespace leetcode_parser

namespace leetcode_vector_printer {

	namespace internal_print {

		template <typename T>
		void _printElement(const T& element, const std::optional<std::string>& name = std::nullopt, bool printEndl = true) {
			if (name.has_value()) {
				std::cout << name.value() << " = ";
			}
			constexpr bool quote = std::is_same_v<T, std::string> || std::is_same_v<T, char>;
			if constexpr (quote) {
				std::cout<<"\"";
			}
			std::cout << element;
			if constexpr (quote) {
				std::cout<<"\"";
			}
			if (printEndl) {
				std::cout << std::endl;
			}
		}
		
		template <typename T>
		void _printVector(const std::vector<T>& vec, const std::optional<std::string>& name = std::nullopt, bool printEndl = true) {
			if (name.has_value()) {
				std::cout << name.value() << " = ";
			}
			std::cout << "[";
			for (size_t i = 0; i < vec.size(); ++i) {
				_printElement(vec[i], std::nullopt, false);
				if (i != vec.size() - 1) {
					std::cout << ", ";
				}
			}
			std::cout << "]";
			if (printEndl) {
				std::cout << std::endl;
			}
		}

		template <typename T>
		void _printVector2D(const std::vector<std::vector<T>>& vec2D, const std::optional<std::string>& name = std::nullopt) {
			if (name.has_value()) {
				std::cout << name.value() << " = ";
			}
			std::cout << "[" << std::endl;
			for (size_t i = 0; i < vec2D.size(); ++i) {
				std::cout << "  ";
				_printVector(vec2D[i], std::nullopt, false);
				if (i != vec2D.size() - 1) {
					std::cout << ",";
				}
				std::cout << std::endl;
			}
			std::cout << "]" << std::endl;
		}

		template <typename T>
		void _print(const T& variable, const std::optional<std::string>& name = std::nullopt) {
			constexpr int depth = internal_vector_depth::vector_depth<T>::value;
			if constexpr (depth == 0) {
				_printElement(variable, name);
			} else if constexpr (depth == 1) {
				_printVector(variable, name);
			} else if constexpr (depth == 2) {
				_printVector2D(variable, name);
			} else {
				throw std::invalid_argument("Unsupported vector depth");
			}
		}

	} // namespace internal_print

	#define printRaw(x) internal_print::_print(x)
	#define print(x) internal_print::_print(x, #x)

} // namespace leetcode_vector_printer

namespace leetcode_input_wrapper {
	
	template <typename T, typename... Ts>
	auto read() {
		// std::cerr << "[read] type name: " << typeid(T).name() << std::endl;
		auto tuple_x = std::make_tuple(leetcode_parser::parse<T>());
		if constexpr (sizeof...(Ts) == 0) {
			return tuple_x;
		} else {
			return std::tuple_cat(std::move(tuple_x), read<Ts...>());
		}
	}

} // namespace leetcode_input_wrapper

#endif // __LEETCODE_PARSER_HPP__