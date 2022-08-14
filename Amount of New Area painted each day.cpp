// https://leetcode.com/problems/amount-of-new-area-painted-each-day/
// https://leetcode.com/submissions/detail/770777575/

const int N = 5e4 + 10;
class Solution {
public:
    int get_par(int x, vector<int> &par) {
        return (x == par[x] ? x : par[x] = get_par(par[x], par));
    }
    vector<int> amountPainted(vector<vector<int>>& paint) {
        vector<int> par(N);
        for(int i = 0; i < N - 1; ++i) par[i] = i;
        vector<int> ans;
        for(int i = 0; i < (int)paint.size(); ++i) {
            int l = paint[i][0], r = paint[i][1];
            int cnt = 0;
            for(int j = l; j < r; ++j) {
                int p = get_par(j, par);
                if(p >= r) break;
                par[p] = p + 1;
                j = p;
                ++ cnt;
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};
