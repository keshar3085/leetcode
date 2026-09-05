class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();

        // rightMin[i] = minimum element from i to n-1
        vector<int> rightMin(n);

        rightMin[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            rightMin[i] = min(nums[i], rightMin[i + 1]);
        }

        // Find first stable index
        int leftMax = nums[0];

        for (int i = 0; i < n; i++) {
            leftMax = max(leftMax, nums[i]);

            int instability = leftMax - rightMin[i];

            if (instability <= k) {
                return i;
            }
        }

        return -1;
    }
};