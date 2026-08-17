class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> prefix(n+1,0);
        for(int i = 0;i<n;i++){
            prefix[i+1]=prefix[i]+stoneValue[i];

        }
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int len=2;len<=n;len++){
            for(int l=0;l+len<=n;l++){
                int r =l+len-1;
                for(int k = l;k<r;k++){
                    int left = prefix[k+1]-prefix[l];
                    int right = prefix[r+1]-prefix[k+1];
                    if(left<right){
                        dp[l][r]=max(
                            dp[l][r],
                            dp[l][k]+left
                        );
                    }
                    else if(left>right){
                        dp[l][r]=max(
                            dp[l][r],
                            dp[k+1][r]+right
                        );
                    }
                    else{
                        dp[l][r]=max({
                            dp[l][r],
                            dp[l][k]+left,
                            dp[k+1][r]+right
                        });
                    }
                }
            }
        }
        return dp[0][n-1];

        
    }
};