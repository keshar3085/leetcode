class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;
        vector<vector<bool>> dp(4,vector<bool>(MAXX, false));
        dp[0][0] = true;

        vector<bool> ans (MAXX, false);
        for(int x : nums)
            ans[x] = true;
        for(int x : nums){
            for(int cnt = 2; cnt >= 0; cnt--){
                for(int xr = 0; xr < MAXX; xr++){
                    if(dp[cnt][xr]){
                        dp[cnt+1][xr^x] = true;

                    }
                }
            }
        }
        for(int xr = 0; xr< MAXX;xr++){
            if(dp[3][xr])
                ans[xr] = true;
        }
        int res = 0;
        for(bool v : ans)
            if(v) res++;
        return res;

        
    }
};