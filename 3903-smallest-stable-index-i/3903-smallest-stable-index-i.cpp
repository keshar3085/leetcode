class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        for (int i = 0; i < n; i++) {

            int leftMax = nums[0];
            for (int j = 0; j <= i; j++) {
                leftMax = max(leftMax, nums[j]);
            }

            int rightMin = nums[i];
            for (int j = i; j < n; j++) {
                rightMin = min(rightMin, nums[j]);
            }

            int instability = leftMax - rightMin;

            if (instability <= k)
                return i;
        }

        return -1;
    }
};