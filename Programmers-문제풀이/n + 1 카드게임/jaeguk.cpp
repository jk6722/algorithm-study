#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <iostream>
using namespace std;
using pii = pair<int,int>;

const int MAX_N = 1000 + 5;
bool card_in_hand[MAX_N]; //현재 가지고 있는 카드
bool passed_card[MAX_N]; //가질 기회가 있었지만 일단 패스한 카드
int N;

int solution(int coin, vector<int> cards) {
    N = cards.size();
    int idx = N / 3;
    
    //N + 1을 만들 수 있는 조합
    queue<pii> can_make;
    
    //뽑긴 했지만 안 산 카드
    vector<int> passed_card;
    
    for(int i = 0; i < idx; i++) {
        card_in_hand[cards[i]] = true;
        if(card_in_hand[N + 1 - cards[i]]) {
            //만들 수 있는 조합 저장
            can_make.push({cards[i], N + 1 - cards[i]});
        }
    }
    
    int round = 1;
    
    while(true) {
        //round
        if(idx < N) {
            //뽑을 카드가 있다면
            int first_card = cards[idx];
            int second_card = cards[idx + 1];
            
            if(card_in_hand[N + 1 - first_card] && coin >= 1) {
                //코인 하나만 써서 만들 수 있다면 무조건 만드는 게 좋음
                coin--;
                card_in_hand[first_card] = true;
                can_make.push({first_card, N + 1 - first_card});
            }
            else if(coin >= 1) {
                passed_card.push_back(first_card);
            }
            
            if(card_in_hand[N + 1 - second_card] && coin >= 1) {
                coin--;
                card_in_hand[second_card] = true;
                can_make.push({second_card, N + 1 - second_card});
            }
            else if(coin >= 1) {
                passed_card.push_back(second_card);
            }
        }
        
        if(!can_make.empty()) {
            //현재 라운드 일단 통과 가능
            pii now = can_make.front();
            can_make.pop();
            card_in_hand[now.first] = false;
            card_in_hand[now.second] = false;
        }
        else {
            //코인 2개 사용해서 한턴 버텨야 함
            if(coin < 2) {
                //코인 2개 없으면 종료
                break;
            }
            
            bool is_ok = false;
            for(int i = 0; i < passed_card.size() - 1; i++) {
                for(int j = 0; j < passed_card.size(); j++) {
                    if(passed_card[i] + passed_card[j] == N + 1) {
                        coin -= 2;
                        is_ok = true;
                        //이제 사용할 수 없는 카드
                        passed_card[i] = passed_card[j] = 1002;
                        goto Lend;
                    }
                }
            }
        Lend:
            //2개를 써도 만들 수 없다면 종료
            if(!is_ok) break;
        }
        
        round++;
        idx += 2;
        
        //더이상 뽑을 카드가 없다면 종료
        if(idx == N) break;
    }
    
    return round;
}