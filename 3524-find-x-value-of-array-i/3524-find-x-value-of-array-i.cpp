class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k,0);
        vector<long long> dp(k,0);

        for(int num : nums){
            vector<long long> newdp(k,0);
            newdp[num % k]++;
            for (int r = 0;r<k;r++){
                if (dp[r] > 0){
                    int newR = (r * (num % k)) % k;
                    newdp[newR] += dp[r];
                }
            }
            for(int r = 0; r<k; r++){
                ans[r] += newdp[r];
            }
            dp = newdp;
        }
        return ans;
        
    }
};