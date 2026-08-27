class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        
        for (int i = n - 1; i >= 0; i--) {

            vector<int> cnt = freq;
            bool possible = true;

            
            for (int j = 0; j < i; j++) {
                int x = target[j] - 'a';

                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }

                cnt[x]--;
            }

            if (!possible)
                continue;

            
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {

                if (cnt[c] > 0) {

                    string ans = target.substr(0, i);

                    ans += char('a' + c);
                    cnt[c]--;

                    
                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] > 0) {
                            ans += char('a' + k);
                            cnt[k]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};