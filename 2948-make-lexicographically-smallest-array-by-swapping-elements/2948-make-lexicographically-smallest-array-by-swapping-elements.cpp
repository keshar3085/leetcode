class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({nums[i], i});
        }

        // Sort by value
        sort(a.begin(), a.end());

        vector<int> ans(n);

        int i = 0;

        while (i < n) {
            int j = i;

            // Find all elements belonging to the same group
            while (j + 1 < n && a[j + 1].first - a[j].first <= limit) {
                j++;
            }

            // Collect original indices of this group
            vector<int> indices;

            for (int k = i; k <= j; k++) {
                indices.push_back(a[k].second);
            }

            // Smallest original indices should get smallest values
            sort(indices.begin(), indices.end());

            for (int k = i; k <= j; k++) {
                ans[indices[k - i]] = a[k].first;
            }

            i = j + 1;
        }

        return ans;
    }
};
