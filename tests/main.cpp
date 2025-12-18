#include <bits/stdc++.h>
#include "../leetcode_parser.hpp"

using namespace std;
using namespace leetcode_IOWrapper;

using LL = long long;
int main() {
	freopen("input.txt","r",stdin);
	
	auto [i1] = read<int>();
	auto [i2] = read<int>();
	auto [i3] = read<int>();
	auto [i4] = read<int>();
	write(i1, i2, i3, i4);
		
	auto [ll1] = read<LL>();
	auto [ll2] = read<LL>();
	auto [ll3] = read<LL>();
	auto [ll4] = read<LL>();
	write(ll1, ll2, ll3, ll4);
	
	auto [b1] = read<bool>();
	auto [b2] = read<bool>();
	write(b1, b2);
	
	auto [d1] = read<double>();
	auto [d2] = read<double>();
	auto [d3] = read<double>();
	write(d1, d2, d3);
	
	auto [c1] = read<char>();
	auto [c2] = read<char>();
	auto [c3] = read<char>();
	write(c1, c2, c3);
	
	auto [s1] = read<string>();
	auto [s2] = read<string>();
	auto [s3] = read<string>();
	write(s1, s2, s3);
	
	auto [v_empty] = read<vector<int>>();
	auto [v_int] = read<vector<int>>();
	auto [v_string] = read<vector<string>>();
	auto [v_double] = read<vector<double>>();
	write(v_empty, v_int, v_string, v_double);
		
	auto [vv_empty] = read<vector<vector<int>>>();
	auto [vv_1row_0elements] = read<vector<vector<int>>>();
	auto [vv_1row_1element] = read<vector<vector<int>>>();
	auto [vv_2x2] = read<vector<vector<int>>>();
	auto [vv_3rows] = read<vector<vector<int>>>();
	auto [vv_2x1_double] = read<vector<vector<double>>>();
	auto [vv_2x1_string] = read<vector<vector<string>>>();
	write(vv_empty, vv_1row_0elements, vv_1row_1element);
	write(vv_2x2, vv_3rows, vv_2x1_double, vv_2x1_string);

	auto [_string, _bool, vv_double, _ll] = read<string, bool, vector<vector<double>>, LL>();
	write(_string, _bool, vv_double, _ll);
	return 0;
}