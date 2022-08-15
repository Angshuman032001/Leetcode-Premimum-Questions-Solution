//time : O(N) for constructor and queries = O(max(K, L)) where K is the number of 
// occurence of word1 and L is the number of occurence of word2

//space: O(N)
class WordDistance {
public:
    map<string, vector<int>>pos;
    WordDistance(vector<string>& wordsDict) {
        for(int i = 0;i<int(wordsDict.size());i++){
            pos[wordsDict[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int i = 0, j = 0, ans = INT_MAX;
        while(i < int(pos[word1].size()) && j < pos[word2].size()){
            ans = min(ans, abs(pos[word1][i] - pos[word2][j]));
            if(pos[word1][i] < pos[word2][j]) i++;
            else j++;
        }
        return ans;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */
