// https://leetcode.com/problems/optimal-account-balancing/
// https://leetcode.com/submissions/detail/773388132/

class Solution {
public:
    vector<int>debts;
    
    int dfs(int start){
        int minOps = INT_MAX;
        while(start < int(debts.size()) && !debts[start]) start++;
        for(int i = start + 1;i<int(debts.size());i++){
            if(debts[i] * debts[start] < 0){
                debts[i] += debts[start];
                minOps = min(minOps, 1 + dfs(start + 1));
                debts[i] -= debts[start];
            }
        }
        return minOps == INT_MAX ? 0 : minOps;
    }
    
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> mp;
        for(auto &t : transactions){
            int lender = t[0], borrower = t[1], amount = t[2];
            mp[lender] -= amount;
            mp[borrower] += amount;
        }
        for(auto it : mp){
            if(it.second) debts.push_back(it.second);
        }
        
        sort(debts.begin(), debts.end());
        
        return dfs(0);
        
    }
};
