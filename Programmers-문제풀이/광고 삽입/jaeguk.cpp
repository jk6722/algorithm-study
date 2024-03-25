#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int MAX_N = 400000 + 5;
ll sum[MAX_N]; //해당 구간까지의 재생 시간의 합

int get_second(string t) {
    int hours = stoi(t.substr(0,2));
    int minutes = stoi(t.substr(3,5));
    int seconds = stoi(t.substr(6));
    
    return hours * 60 * 60 + minutes * 60 + seconds;
}

string get_time(int seconds) {
    int hours = seconds / (60 * 60);
    seconds %= (60 * 60);
    int minutes = seconds / 60;
    seconds %= 60;
    
    string hour = hours >= 10 ? to_string(hours) : "0" + to_string(hours);
    string minute = minutes >= 10 ? to_string(minutes) : "0" + to_string(minutes);
    string second = seconds >= 10 ? to_string(seconds) : "0" + to_string(seconds);
    
    return hour + ":" + minute + ":" + second;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    
    //동영상이 끝나는 시간
    int play_ed = get_second(play_time);
    //총 광고 길이
    int adv_length = get_second(adv_time);

    for(auto log : logs) {
        string from = log.substr(0, 8);
        string to = log.substr(9);
        
        int from_second = get_second(from);
        int to_second = get_second(to);
        
        sum[from_second]++;
        sum[to_second]--;
    }
    
    for(int i = 1; i <= play_ed; i++) {
        //해당 구간에서 재생되는 영상 개수 누적합
        sum[i] += sum[i-1];
    }
    
    for(int i = 1; i <= play_ed; i++) {
        //영상 개수의 누적합 (누적 재생 시간)
        sum[i] += sum[i-1];
    }
    
    ll max_play = 0;
    
    for(int sec = 0; sec < MAX_N; sec++) {
        int st = sec; //영상 시작 시간
        
        //해당 지점에 광고를 넣을 시에 영상 범위를 넘어가면
        if(st + adv_length > play_ed) break;
        
        ll temp = st - 1 >= 0 ? sum[st - 1] : 0;
        ll total_played = sum[st + adv_length - 1] - temp;
        
        if(max_play < total_played) {                        
            max_play = total_played;
            
            string start_time = get_time(st);
            answer = start_time;
        }
    }
    
    return answer;
}