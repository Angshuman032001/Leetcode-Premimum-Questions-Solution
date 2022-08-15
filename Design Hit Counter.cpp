// https://leetcode.com/problems/design-hit-counter/
// https://leetcode.com/submissions/detail/774226965/ - brute
// https://leetcode.com/submissions/detail/774229055/ - optimal

class HitCounter {
public:
    deque<pair<int, int>>q;
    int total;
    HitCounter() {
        this->total = 0;
    }
    
    void hit(int timestamp) {
        if(q.empty() || q.back().first != timestamp){
            q.push_back(make_pair(timestamp, 1));
        }
        else q.back().second++;
        this->total++;
    }
    
    int getHits(int timestamp) {
        while(!q.empty() && (timestamp - q.front().first >= 300)){
            this->total -= q.front().second;
            q.pop_front();
        }
        return this->total;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */
