#include <bits/stdc++.h>
#include "../leetcode_parser.hpp"

using namespace std;
using namespace leetcode_vector_printer;
using namespace leetcode_input_wrapper;

using LL = long long;

int main() {
	freopen("input.txt","r",stdin);
	
	auto [i1] = read<int>();
	auto [i2] = read<int>();
	auto [i3] = read<int>();
	auto [i4] = read<int>();
	print(i1);
	print(i2);
	print(i3);
	print(i4);
		
	auto [ll1] = read<LL>();
	auto [ll2] = read<LL>();
	auto [ll3] = read<LL>();
	auto [ll4] = read<LL>();
	print(ll1);
	print(ll2);
	print(ll3);
	print(ll4);
	
	auto [b1] = read<bool>();
	auto [b2] = read<bool>();
	print(b1);
	print(b2);
	
	auto [d1] = read<double>();
	auto [d2] = read<double>();
	auto [d3] = read<double>();
	print(d1);
	print(d2);
	print(d3);
	
	auto [c1] = read<char>();
	auto [c2] = read<char>();
	auto [c3] = read<char>();
	print(c1);
	print(c2);
	print(c3);
	
	auto [s1] = read<string>();
	auto [s2] = read<string>();
	auto [s3] = read<string>();
	print(s1);
	print(s2);
	print(s3);
	
	auto [v_empty] = read<vector<int>>();
	auto [v_int] = read<vector<int>>();
	auto [v_string] = read<vector<string>>();
	auto [v_double] = read<vector<double>>();
	print(v_empty);
	print(v_int);
	print(v_string);
	print(v_double);
		
	auto [vv_empty] = read<vector<vector<int>>>();
	auto [vv_1row_0elements] = read<vector<vector<int>>>();
	auto [vv_1row_1element] = read<vector<vector<int>>>();
	auto [vv_2x2] = read<vector<vector<int>>>();
	auto [vv_3rows] = read<vector<vector<int>>>();
	auto [vv_2x1_double] = read<vector<vector<double>>>();
	auto [vv_2x1_string] = read<vector<vector<string>>>();
	print(vv_empty);
	print(vv_1row_0elements);
	print(vv_1row_1element);
	print(vv_2x2);
	print(vv_3rows);
	print(vv_2x1_double);
	print(vv_2x1_string);

	auto [_string, _bool, vv_double, _ll] = read<string, bool, vector<vector<double>>, LL>();
	print(_string);
	print(_bool);
	print(vv_double);
	print(_ll);
	return 0;
}