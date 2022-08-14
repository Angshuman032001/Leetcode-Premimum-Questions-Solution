// https://leetcode.com/problems/employee-free-time/
// https://leetcode.com/submissions/detail/773164706/

/*
// Definition for an Interval.
class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        map<int,int>m;
        for(auto &x : schedule){
            for(auto &y : x){                
                m[y.start]++;
                m[y.end]--;
            }
        }
        
        int start = -1, sum = 0;
        vector<Interval>ans;
        for(auto it : m){
            if(sum == 0 && start != -1) ans.push_back(Interval(start, it.first));
            sum += it.second;
            if(sum == 0) start = it.first;
        }
        return ans;
        
    }
};
