
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        
        // Sort logs according to time
        sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
            return a[1] < b[1];
        });

        // Store queries with their original indices
        vector<pair<int, int>> q;
        
        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        // Sort queries according to time
        sort(q.begin(), q.end());

        vector<int> freq(n + 1, 0);
        vector<int> ans(queries.size());

        int left = 0;
        int right = 0;
        int active = 0;

        for (auto [time, idx] : q) {

            int start = time - x;

            // Add logs within the current right boundary
            while (right < logs.size() && logs[right][1] <= time) {
                int server = logs[right][0];

                if (freq[server] == 0) {
                    active++;
                }

                freq[server]++;
                right++;
            }

            // Remove logs outside the left boundary
            while (left < right && logs[left][1] < start) {
                int server = logs[left][0];

                freq[server]--;

                if (freq[server] == 0) {
                    active--;
                }

                left++;
            }

            // Servers with zero requests
            ans[idx] = n - active;
        }

        return ans;
    }
};
