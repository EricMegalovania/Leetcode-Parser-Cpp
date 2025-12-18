#ifndef __VECTOR_PRINTER_HPP__
#define __VECTOR_PRINTER_HPP__

#include <iostream>
#include <vector>
#include <string>

namespace VectorPrinter {

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

} // namespace VectorPrinter

#endif // __VECTOR_PRINTER_HPP__