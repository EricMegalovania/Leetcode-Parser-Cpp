#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i=0;i<(int)nums.size();++i){
            if(mp.count(target-nums[i])) return {mp[target-nums[i]],i};
            mp[nums[i]]=i;
        }
        return {};
    }
};

#include"../leetcode_parser.hpp"
using namespace leetcode_vector_printer;
using namespace leetcode_input_wrapper;
int main(){
    auto [nums,target]=read<vector<int>,int>();
	vector<int> ans=Solution().twoSum(nums,target);
	printRaw(ans);
	return 0;
}