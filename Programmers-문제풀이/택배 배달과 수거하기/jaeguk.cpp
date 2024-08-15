#include <string>
#include <iostream>
#include <vector>

using namespace std;

int find_idx(int now, int cap, vector<int>& vt) {
    if(now == -1) return now;
    
    int now_cap = 0;
    for(int i = now; i >= 0; i--) {
        if(vt[i] == 0) continue;
        
        if(now_cap + vt[i] <= cap) {
            now_cap += vt[i];
            vt[i] = 0; //완료
            if(now_cap == cap) return i - 1;
        }
        else {
            vt[i] -= (cap - now_cap);
            return i;
        }
    }
    return -1;
}

int reduce_idx(int now, vector<int>& vt) {
    for(int i = now; i >= 0; i--) {
        if(vt[i]) return i;
    }
}


long long solution(int cap, int n, vector<int> deliveries, vector<int> pickups) {
    long long answer = 0;
    
    int del_idx = -1;
    int pick_idx = -1;
    
    for(int i = n - 1; i >= 0; i--)
        if(deliveries[i]) {
            del_idx = i;
            break;
        }
    
    for(int i = n - 1; i >= 0; i--) {
        if(pickups[i]) {
            pick_idx = i;
            break;
        }   
    }
    
    while(!(del_idx == -1 && pick_idx == -1)) {
        del_idx = reduce_idx(del_idx, deliveries);
        pick_idx = reduce_idx(pick_idx, pickups);
        
        answer += max(del_idx + 1, pick_idx + 1) * 2;
        
        del_idx = find_idx(del_idx, cap, deliveries);
        pick_idx = find_idx(pick_idx, cap, pickups);
    }
    return answer;
}