class Solution {
public:
    int maxPalindromes(string s, int k) {

        int n = s.size();

        
        vector<vector<bool>> pal(n, vector<bool>(n, false));

        
        for (int i = 0; i < n; i++) {
            pal[i][i] = true;
        }

        
        for (int len = 2; len <= n; len++) {

            for (int i = 0; i + len <= n; i++) {

                int j = i + len - 1;

                if (s[i] == s[j]) {

                    if (len == 2)
                        pal[i][j] = true;
                    else
                        pal[i][j] = pal[i + 1][j - 1];
                }
            }
        }

        
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= n; i++) {

            
            dp[i] = dp[i - 1];

            
            for (int j = 0; j < i; j++) {

                int len = i - j;

                if (len >= k && pal[j][i - 1]) {
                    dp[i] = max(dp[i],
                                dp[j] + 1);
                }
            }
        }

        return dp[n];
    }
};