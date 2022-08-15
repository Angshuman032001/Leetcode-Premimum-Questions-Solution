## 1659. Maximize Grid Happiness


#### Statement
You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.

You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.

The happiness of each person is calculated as follows:

Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.

The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.


#### Solution
we search all possible placements of introvert, extrovert or empty of each cell in the grid
we place people from top to bottom, left to right. each position can be identified by p, which is [0,24]. The row(i) and column(j) is therefore i = p / n, j = p % n
first we consider leaving current cell empty int res = dfs(m, n, p + 1, in, ex, n_mask_in, n_mask_ex);

3.1 if current cell is empty, then the score is simply decided by what we do in next cell second, we consider placing introvert at current cell if there's still introvert people left (if (in > 0) {...})

4.1 (see below)
last, similar to #4, we consider extrovert people (if (ex > 0) {...})

5.1 (see below)
in the process, we use max to keep the max happiness score
let's discuss 4.1 (5.1 is very similar). if we place introvert people at (i, j), we get 120 but also need to subtract 30 for any people surrounding. This is what nCost does.

```
i 0 i
x ? ?
? ? ?
```

First, mask_in is the placement of introvert people in the last m cells. For example, if we have m=3, n=3, i=1, j=0, then mask_in=101 means

x is where we're currently at.
? is cell we haven't processed yet.
i is we place introvert people there.

so nCost is basically to check if the left or up cell of current cell is empty or not. If empty, then we d-30 if we place introvert people at current cell (need to double the penalty due to mutual repulsion).

once we calculate the cost of placing, we just need to add on top of it the cost of placing for the rest cells. we just need to increment position index p+1, decrement introvert people number, and then shift the bitmask by accounting for current placement diff + dfs(m, n, p + 1, in - 1, ex, n_mask_in + 1, n_mask_ex)

That's all.

```cpp
int dp[25][7][7][64][64];

class Solution {
private:
    int happinessContribution(int m, int n, int row, int col, int inMask, int exMask, int d){
        int diff = 0, up = (1 << (n - 1));
        if(col > 0 && (inMask & 1)) diff += d - 30;
        if(row > 0 && (inMask & up)) diff += d - 30;
        if(col > 0 && (exMask & 1)) diff += d + 20;
        if(row > 0 && (exMask & up)) diff += d + 20;
        return diff;
    }
    int solve(int m, int n, int index, int inCnt, int exCnt, int inMask, int exMask){
        int row = index / n, col = index % n;
        if(row >= m) return 0;
        int &ans = dp[index][inCnt][exCnt][inMask][exMask];
        if(ans != -1) return ans;
        int newInMask = (inMask << 1) & 63, newExMask = (exMask << 1) & 63;
        ans = solve(m, n, index + 1, inCnt, exCnt, newInMask, newExMask);
        if(inCnt > 0){
            int diff = 120 + happinessContribution(m, n, row, col, inMask, exMask, -30);
            ans = max(ans, diff + solve(m, n, index + 1, inCnt - 1, exCnt, newInMask + 1, newExMask));
        }
        if(exCnt > 0){
            int diff = 40 + happinessContribution(m, n, row, col, inMask, exMask, 20);
            ans = max(ans, diff + solve(m, n, index + 1, inCnt, exCnt - 1, newInMask, newExMask + 1));
        }
        return ans;
    }
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        memset(dp, -1, sizeof(dp));
        int ans = solve(m, n, 0, introvertsCount, extrovertsCount, 0, 0);
        return ans;
    }
};

static const auto speedup = []() {
	std::ios::sync_with_stdio(false); std::cin.tie(nullptr); return 0;
}();
