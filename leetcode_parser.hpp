#ifndef __LEETCODE_PARSER_HPP__
#define __LEETCODE_PARSER_HPP__

#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <optional>
#include <type_traits>
#include <queue>

class internal_debug {
	static bool debug_mode;
public:
	void toggle_debug_mode() {
		debug_mode = !debug_mode;
	}
	void unset_debug_mode() {
		debug_mode = false;
	}
	void set_debug_mode(bool _f = true) {
		debug_mode = _f;
	}
	bool is_debug_mode() const {
		return debug_mode;
	}
};
inline bool internal_debug::debug_mode = false;

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

namespace leetcode_struct {
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(nullptr), right(nullptr) {}
		TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
		TreeNode(int x, TreeNode *ls, TreeNode *rs) : val(x), left(ls), right(rs) {}
	};
}

namespace leetcode_input {

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
	
	namespace internal_parser {
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

		template <>
		inline leetcode_struct::TreeNode* _parse<leetcode_struct::TreeNode*>(std::istream& is) {
			skipWhitespace(is);
			if (!isVectorStart(peekNextChar(is))) {
				throw std::invalid_argument("TreeNode* must start with '['");
			} else {
				is.get();
			}
			
			skipWhitespace(is);
			if(is.eof()) {
				throw std::invalid_argument("TreeNode* must end with ']'");
			}
			if (isVectorEnd(peekNextChar(is))) {
				is.get();
				return nullptr;
			}
			
			std::queue<leetcode_struct::TreeNode*> waitReadChildren;
			auto readTreeNodeAndPush = [&](auto&& node) -> bool {
				skipWhitespace(is);
				if (isVectorStart(peekNextChar(is))) {
					throw std::invalid_argument("Unexpected nested vector in TreeNode*");
				} else {
					if (peekNextChar(is) == 'n') {
						char buffer[4];
						is.read(buffer, 4);
						if (!is || std::strncmp(buffer, "null", 4) != 0) {
							throw std::invalid_argument("Invalid null input");
						}
						node = nullptr;
					} else {
						node = new leetcode_struct::TreeNode(_parse<int>(is));
						waitReadChildren.push(node);
					}
				}
				
				skipWhitespace(is);
				if (isVectorEnd(peekNextChar(is))) {
					is.get(); return 0;
				} else if (isSeparator(peekNextChar(is))) {
					is.get();
				} else {
					throw std::invalid_argument("Expected ',' or ']' after TreeNode* element \'" + std::string(1, peekNextChar(is)) + std::string("\'"));
				}

				return 1;
			};

			leetcode_struct::TreeNode* root = nullptr;
			if(!readTreeNodeAndPush(root)) return root;

			while (true) {
				if (waitReadChildren.empty()) {
					throw std::runtime_error("TreeNode* queue is empty in reading");
				}

				leetcode_struct::TreeNode* node = waitReadChildren.front();
				waitReadChildren.pop();

				if(!readTreeNodeAndPush(node->left)) break;
				if(!readTreeNodeAndPush(node->right)) break;
			}
			
			return root;
		}
	} // namespace internal_parser
	
	template <typename T>
	T input() {
		constexpr int depth = internal_vector_depth::vector_depth<T>::value;
		if(internal_debug().is_debug_mode()) {
			std::cerr << "[input] type name: " << typeid(T).name() << " depth: " << depth << std::endl;
		}
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
	
} // namespace leetcode_input

namespace leetcode_output {

	namespace internal_output {

		template <typename T, bool printEndl = true, bool printSpace = true>
		void _printElement(const T& element, const std::optional<std::string>& name = std::nullopt) {
			if (name.has_value()) {
				std::cout << name.value();
				if constexpr (printSpace) std::cout << " ";
				std::cout << "=";
				if constexpr (printSpace) std::cout << " ";
			}
			constexpr bool quote = std::is_same_v<T, std::string> || std::is_same_v<T, char>;
			if constexpr (quote) std::cout<<"\"";
			if constexpr (std::is_same_v<T, bool>){
				std::cout << (element ? "true" : "false");
			}
			else{
				std::cout << element;
			}
			if constexpr (quote) std::cout<<"\"";
			if constexpr (printEndl) std::cout << std::endl;
		}

		template <bool printEndl = true, bool printSpace = true>
		void _printTreeNode(const leetcode_struct::TreeNode* root, const std::optional<std::string>& name = std::nullopt) {
			if (name.has_value()) {
				std::cout << name.value();
				if constexpr (printSpace) std::cout << " ";
				std::cout << "=";
				if constexpr (printSpace) std::cout << " ";
			}
			std::cout << "[";

			bool print_first = true;
			std::queue<leetcode_struct::TreeNode*> waitPrintChildren;
			std::stringstream buf;
			auto printTreeNodeAndPush = [&](const leetcode_struct::TreeNode* node) -> void {
				if (!print_first){
					buf << ",";
					if constexpr (printSpace) buf << " ";
				}
				else print_first = false;

				if (node != nullptr) {
					buf << node->val;
					std::cout << buf.str();
					buf.str("");
					waitPrintChildren.push(node->left);
					waitPrintChildren.push(node->right);
				} else {
					buf << "null";
				}
			};
			printTreeNodeAndPush(root);

			while (!waitPrintChildren.empty()) {
				printTreeNodeAndPush(waitPrintChildren.front());
				waitPrintChildren.pop();
			}

			std::cout << "]";
			if constexpr (printEndl) std::cout << std::endl;
		}
		
		template <typename T, bool printEndl = true, bool printSpace = true>
		void _printVector(const std::vector<T>& vec, const std::optional<std::string>& name = std::nullopt) {
			if (name.has_value()) {
				std::cout << name.value();
				if constexpr (printSpace) std::cout << " ";
				std::cout << "=";
				if constexpr (printSpace) std::cout << " ";
			}
			std::cout << "[";
			for (size_t i = 0; i < vec.size(); ++i) {
				_printElement<T, false, printSpace>(vec[i], std::nullopt);
				if (i != vec.size() - 1) {
					std::cout << ",";
					if constexpr (printSpace) std::cout << " ";
				}
			}
			std::cout << "]";
			if constexpr (printEndl) std::cout << std::endl;
		}

		template <typename T, bool printEndl = true, bool printSpace = true>
		void _printVector2D(const std::vector<std::vector<T>>& vec2D, const std::optional<std::string>& name = std::nullopt) {
			// well, printEndl is not used in this function
			if (name.has_value()) {
				std::cout << name.value();
				if constexpr (printSpace) std::cout << " ";
				std::cout << "=";
				if constexpr (printSpace) std::cout << " ";
			}
			std::cout << "[" << std::endl;
			for (size_t i = 0; i < vec2D.size(); ++i) {
				std::cout << "  ";
				_printVector<T, false, printSpace>(vec2D[i], std::nullopt);
				if (i != vec2D.size() - 1) std::cout << ",";
				std::cout << std::endl;
			}
			std::cout << "]" << std::endl;
		}

	} // namespace internal_output

	template <typename T, bool printSpace = true>
	void _print(const T& variable, const std::optional<std::string>& name = std::nullopt) {
		if(internal_debug().is_debug_mode()) {
			std::cerr << "[print] type name: " << typeid(T).name() << std::endl;
		}
		constexpr int depth = internal_vector_depth::vector_depth<T>::value;
		using _T = typename internal_vector_depth::vector_depth<T>::inner_type;
		if constexpr (depth == 0) {
			if constexpr (std::is_same_v<_T, leetcode_struct::TreeNode*>) {
				internal_output::_printTreeNode<true, printSpace>(variable, name);
			} else {
				internal_output::_printElement<_T, true, printSpace>(variable, name);
			}
		} else if constexpr (depth == 1) {
			internal_output::_printVector<_T, true, printSpace>(variable, name);
		} else if constexpr (depth == 2) {
			internal_output::_printVector2D<_T, true, printSpace>(variable, name);
		} else {
			throw std::invalid_argument("Unsupported vector depth");
		}
	}
	
} // namespace leetcode_output

namespace leetcode_IOWrapper {
	
	template <typename T, typename... Ts>
	auto read() {
		if(internal_debug().is_debug_mode()) {
			std::cerr << "[read] type name: " << typeid(T).name() << std::endl;
		}
		auto tuple_x = std::make_tuple(leetcode_input::input<T>());
		if constexpr (sizeof...(Ts) == 0) {
			return tuple_x;
		} else {
			return std::tuple_cat(std::move(tuple_x), read<Ts...>());
		}
	}
	
	#define _INTERNAL_OWRAPPER_COUNT_ARGS(...) _INTERNAL_OWRAPPER_COUNT_ARGS_IMPL(__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)
	#define _INTERNAL_OWRAPPER_COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH(func, ...) _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL(_INTERNAL_OWRAPPER_COUNT_ARGS(__VA_ARGS__), func, __VA_ARGS__)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL(count, func, ...) _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_(count, func, __VA_ARGS__)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_(count, func, ...) _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_##count(func, __VA_ARGS__)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_0(func)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_1(func, a) func(a)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_2(func, a, b) func(a) func(b)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_3(func, a, b, c) func(a) func(b) func(c)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_4(func, a, b, c, d) func(a) func(b) func(c) func(d)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_5(func, a, b, c, d, e) func(a) func(b) func(c) func(d) func(e)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_6(func, a, b, c, d, e, f) func(a) func(b) func(c) func(d) func(e) func(f)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_7(func, a, b, c, d, e, f, g) func(a) func(b) func(c) func(d) func(e) func(f) func(g)
	#define _INTERNAL_OWRAPPER_APPLY_TO_EACH_IMPL_8(func, a, b, c, d, e, f, g, h) func(a) func(b) func(c) func(d) func(e) func(f) func(g) func(h)

	#define _internal_print(x) leetcode_output::_print<decltype(x), true>(x, #x);
	#define write(...) _INTERNAL_OWRAPPER_APPLY_TO_EACH(_internal_print, __VA_ARGS__)

	#define _internal_printRaw(x) leetcode_output::_print<decltype(x), true>(x);
	#define writeRaw(...) _INTERNAL_OWRAPPER_APPLY_TO_EACH(_internal_printRaw, __VA_ARGS__)

	#define _internal_printNoSpace(x) leetcode_output::_print<decltype(x), false>(x, #x);
	#define writeNoSpace(...) _INTERNAL_OWRAPPER_APPLY_TO_EACH(_internal_printNoSpace, __VA_ARGS__)

	#define _internal_printRawNoSpace(x) leetcode_output::_print<decltype(x), false>(x);
	#define writeRawNoSpace(...) _INTERNAL_OWRAPPER_APPLY_TO_EACH(_internal_printRawNoSpace, __VA_ARGS__)

} // namespace leetcode_IOWrapper

#endif // __LEETCODE_PARSER_HPP__