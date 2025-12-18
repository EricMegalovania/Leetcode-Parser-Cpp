#include <bits/stdc++.h>
#include "../leetcode_parse.hpp"
#include "vector_printer.hpp"

using namespace std;
using namespace leetcode_parser;
using namespace VectorPrinter;

using LL = long long;

int main() {
	freopen("input.txt","r",stdin);
	
	int i1 = parse<int>();
	int i2 = parse<int>();
	int i3 = parse<int>();
	int i4 = parse<int>();
	cout << "i1: " << i1 << endl;
	cout << "i2: " << i2 << endl;
	cout << "i3: " << i3 << endl;
	cout << "i4: " << i4 << endl;
	
	LL ll1 = parse<LL>();
	LL ll2 = parse<LL>();
	LL ll3 = parse<LL>();
	LL ll4 = parse<LL>();
	cout << "ll1: " << ll1 << endl;
	cout << "ll2: " << ll2 << endl;
	cout << "ll3: " << ll3 << endl;
	cout << "ll4: " << ll4 << endl;
	
	bool b1 = parse<bool>();
	bool b2 = parse<bool>();
	cout << "b1: " << (b1 ? "true" : "false") << endl;
	cout << "b2: " << (b2 ? "true" : "false") << endl;
	
	double d1 = parse<double>();
	double d2 = parse<double>();
	double d3 = parse<double>();
	cout << "d1: " << d1 << endl;
	cout << "d2: " << d2 << endl;
	cout << "d3: " << d3 << endl;
	
	char c1 = parse<char>();
	char c2 = parse<char>();
	char c3 = parse<char>();
	cout << "c1: '" << c1 << "'" << endl;
	cout << "c2: '" << c2 << "'" << endl;
	cout << "c3: '" << c3 << "'" << endl;
	
	string s1 = parse<string>();
	string s2 = parse<string>();
	string s3 = parse<string>();
	cout << "s1: \"" << s1 << "\"" << endl;
	cout << "s2: \"" << s2 << "\"" << endl;
	cout << "s3: \"" << s3 << "\"" << endl;
	
	vector<int> v_empty = parseVector<int>();
	vector<int> v_int = parseVector<int>();
	vector<string> v_string = parseVector<string>();
	vector<double> v_double = parseVector<double>();
	printVector("v_empty", v_empty);
	printVector("v_int", v_int);
	printVector("v_string", v_string);
	printVector("v_double", v_double);
	
	vector<vector<int>> vv_empty = parseVector2D<int>();
	vector<vector<int>> vv_1row_0elements = parseVector2D<int>();
	vector<vector<int>> vv_1row_1element = parseVector2D<int>();
	vector<vector<int>> vv_2x2 = parseVector2D<int>();
	vector<vector<int>> vv_3rows = parseVector2D<int>();
	vector<vector<double>> vv_2x1_double = parseVector2D<double>();
	printVector2D("vv_empty", vv_empty);
	printVector2D("vv_1row_0elements", vv_1row_0elements);
	printVector2D("vv_1row_1element", vv_1row_1element);
	printVector2D("vv_2x2", vv_2x2);
	printVector2D("vv_3rows", vv_3rows);
	printVector2D("vv_2x1_double", vv_2x1_double);

	return 0;
}