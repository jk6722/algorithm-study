#include <string>
#include <vector>
#include <iostream>
using namespace std;

//완전 이진트리가 될 수 있는 길이
vector<int> can_full_binary = {1, 3, 7, 15, 31, 63};
string binary = "";

string change_to_binary(long long number) {
    string ret = "";
    
    while(number) {
        ret = to_string(number % 2) + ret;
        number /= 2;
    }
    
    return ret;
}

bool is_ok(int now, int to_child, bool is_zero) {
        
    //만약 부모가 0인데, 내가 1이면 잘못된 트리
    if(is_zero && binary[now] == '1') return false;
    
    is_zero = binary[now] == '0' ? true : is_zero;
    
    if(to_child == 0) return true;    
    
    
    return is_ok(now - to_child, to_child / 2, is_zero) 
        && is_ok(now + to_child, to_child / 2, is_zero);
}

vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    
    for(auto number : numbers) {
        binary = change_to_binary(number);
        
        if(binary == "1"){
            answer.push_back(1);
            continue;
        }
        
        int len = binary.length(); //2진수의 길이
        
        int idx = lower_bound(can_full_binary.begin(), can_full_binary.end(), len) - can_full_binary.begin();
        int gap = can_full_binary[idx] - len;
        
        //앞에 0 추가해서 완전 이진트리로 변환
        for(int i = 0; i < gap; i++) {
            binary = "0" + binary;
        }
        
        int root = binary.length() / 2;
        
        if(binary[root] == '0') {
            answer.push_back(0);
            continue;
        }
        
        if(is_ok(root, (root + 1) / 2, false)) {
            answer.push_back(1);
        }
        else answer.push_back(0);
        
    }
    
    return answer;
}