#include <string>
#include <vector>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = -1;
    int l = 1, r = 1;
    
    for(auto stone : stones) {
        r = max(stone, r);
    }
    
    while(l <= r) {
        int mid = (l + r) / 2;
        //최대값이 mid인 구간의 길이가 k 이상인가?
        
        int cnt = 0;
        bool is_over = false;
        
        for(auto stone : stones) {
            if(stone <= mid) {
                cnt++;
            }
            else{
                if(cnt >= k) {
                    is_over = true;
                    break;
                }
                cnt = 0;
            }
        }
        
        if(cnt >= k) {
            is_over = true;
        }
        
        if(is_over) {
            answer = answer == -1 ? mid : min(mid, answer);
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return answer;
}