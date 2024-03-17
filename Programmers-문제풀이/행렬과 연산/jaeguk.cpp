#include <string>
#include <vector>
#include <queue>

using namespace std;
const int MAX_N = 50000 + 5;
deque<int> left_col_queue;
deque<int> right_col_queue;
deque<int> deques[MAX_N];
deque<deque<int>*> mid_queues;

void rotate() {
    int temp_left_top = left_col_queue.front();
    left_col_queue.pop_front();
    int temp_right_bot = right_col_queue.front();
    right_col_queue.pop_front();
    
    deque<int>* bot_deque = mid_queues.back();
    mid_queues.pop_back();
    deque<int>* top_deque = mid_queues.front();
    mid_queues.pop_front();
    
    top_deque->push_front(temp_left_top);
    right_col_queue.push_back(top_deque->back());
    top_deque->pop_back();
    
    bot_deque->push_back(temp_right_bot);
    left_col_queue.push_back(bot_deque->front());
    bot_deque->pop_front();
    
    mid_queues.push_back(bot_deque);
    mid_queues.push_front(top_deque);
}

void shift_row() {
    int temp = left_col_queue.back();
    left_col_queue.pop_back();
    left_col_queue.push_front(temp);
    
    temp = right_col_queue.front();
    right_col_queue.pop_front();
    right_col_queue.push_back(temp);
    
    deque<int>* temp_deque = mid_queues.back();
    mid_queues.pop_back();
    mid_queues.push_front(temp_deque);
}

vector<vector<int>> solution(vector<vector<int>> rc, vector<string> operations) {
    int row = rc.size();
    int col = rc[0].size();
    int mid_queue_idx = 0;
    for(auto r : rc) {
        deque<int>* temp_row = &deques[mid_queue_idx++];
        for(int i = 0; i < r.size(); i++) {
            if(i == 0) left_col_queue.push_back(r[i]);
            else if(i == r.size() - 1) {
                right_col_queue.push_front(r[i]);
            }
            else {
                temp_row->push_back(r[i]);
            }
        }
        mid_queues.push_back(temp_row);
    }
    
    for(auto oper : operations) {
        if(oper == "Rotate") {
            rotate();
        }
        else if(oper == "ShiftRow") {
            shift_row();
        }
    }
    
    vector<vector<int>> answer;
    
    for(int i = 0; i < row; i++) {
        vector<int> temp;
        
        deque<int>* temp_deque = mid_queues.front();
        mid_queues.pop_front();
        
        for(int j = 0; j < col; j++) {
            if(j == 0) {
                temp.push_back(left_col_queue.front());
                left_col_queue.pop_front();
            }
            else if(j == col - 1) {
                temp.push_back(right_col_queue.back());
                right_col_queue.pop_back();
            }
            else {
                temp.push_back(temp_deque->front());
                temp_deque->pop_front();
            }
        }
        
        answer.push_back(temp);
    }
    
    return answer;
}