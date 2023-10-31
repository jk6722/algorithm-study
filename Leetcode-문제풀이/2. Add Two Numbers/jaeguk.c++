/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        string str1 = "";
        string str2 = "";

        ListNode *now = l1;
        while(now != NULL) {
            str1 += to_string(now->val);
            now = now->next;
        }

        now = l2;
        while(now != NULL) {
            str2 += to_string(now->val);
            now = now->next;
        }


        string ans = "";
        int edge = 0;
        for(int i = 0; i < max(str1.length(), str2.length()); i++) {
            int a = i < str1.length() ? str1[i] - '0' : 0;
            int b = i < str2.length() ? str2[i] - '0' : 0;

            ans += to_string((a + b + edge) % 10);
            edge = (a + b + edge) / 10;
        }

        cout << ans << "\n";

        ListNode *ret = new ListNode(ans[0] - '0');
        ListNode *temp = ret;

        for(int i = 1; i < ans.length(); i++) {
            temp->next = new ListNode(ans[i] - '0');
            temp = temp->next;
        }

        if(edge)
            temp->next = new ListNode(edge);

        return ret;
    }
};