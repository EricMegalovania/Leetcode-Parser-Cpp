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

#include<local/leetcode_parser.hpp>
using namespace leetcode_parser;
using namespace leetcode_vector_printer;
int main(){
	vector<int> nums=parseVector<int>();
	int target=parse<int>();
	vector<int> ans=Solution().twoSum(nums,target);
	printVector("ans",ans,false);
	return 0;
}