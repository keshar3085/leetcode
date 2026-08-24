class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        int sum =0;
        for(int x:stones)
            sum += x;
        int dp = sum;
        for (int i = n-2;i>=1;i--){
            sum -= stones[i+1];
            dp = max(sum-dp,dp);
        }
        return dp;
    }
};