#include <iostream>
#include <vector>
#include <stack>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int>freq_cnt;
        for(int i=0;i<nums.size();i++){
            freq_cnt[nums[i]]++;
        }

        //test
        for(auto x:freq_cnt){
            cout << x.first << " " << x.second << endl;
        }


        deque<pair<int,int>> max_k;
        stack<pair<int,int>> store_max;

        for(i){
            if(max_k.empty())
                max_k.push_back(*x);
        }

        for(const auto& x:freq_cnt){
            if(!max_k.empty()&&max_k.back().second <= x.second)
                max_k.push_back(x);
            else if(!max_k.empty()&&max_k.front().second < x.second){
                while(max_k.front().second < x.second){
                    store_max.push(max_k.front());
                    max_k.pop_front();
                }
                while(!store_max.empty()){
                    max_k.push_front(store_max.top());
                    store_max.pop();
                }
            }
            else if(max_k.empty())
                max_k.push_back(x);


            if(max_k.size()>k)
                max_k.pop_front();

        }
        //

        for(auto x:max_k){
            cout << x.first << " " << x.second << endl;
        }

        vector<int> result(k);

        for(int i=0;i < k;i++){
            result[i] = max_k.front().first;
            max_k.pop_front();
        }

        return result;
    }
};

int main() {
    vector<int> nums{5,3,1,1,1,3,73,1};
    int k=2;
    Solution mysolution;
    mysolution.topKFrequent(nums,k);
    return 0;
}
