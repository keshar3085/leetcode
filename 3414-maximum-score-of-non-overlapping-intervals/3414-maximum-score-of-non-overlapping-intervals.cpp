class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> indices;
    };

    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.indices < b.indices;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {l, r, weight, original_index}
        vector<array<int, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by ending point
        sort(a.begin(), a.end(), [](auto &x, auto &y) {
            return x[1] < y[1];
        });

        // ends[i] = ending point of sorted interval i
        vector<int> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = a[i][1];

        /*
            dp[i][k] = best answer using first i intervals
            and at most k intervals.

            i ranges from 0 to n
            k ranges from 0 to 4
        */
        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {

            // Option 1: skip current interval
            for (int k = 1; k <= 4; k++) {
                dp[i][k] = dp[i - 1][k];
            }

            // Option 2: take current interval
            int l = a[i - 1][0];
            int weight = a[i - 1][2];
            int originalIndex = a[i - 1][3];

            /*
                Find number of intervals whose end < l.

                lower_bound(l) gives first end >= l.
                So all elements before it are compatible.
            */
            int p = lower_bound(ends.begin(),
                                ends.begin() + (i - 1),
                                l) - ends.begin();

            for (int k = 1; k <= 4; k++) {

                State candidate;

                candidate.score =
                    dp[p][k - 1].score + weight;

                candidate.indices =
                    dp[p][k - 1].indices;

                candidate.indices.push_back(originalIndex);

                // We need indices in increasing order
                sort(candidate.indices.begin(),
                     candidate.indices.end());

                if (better(candidate, dp[i][k])) {
                    dp[i][k] = candidate;
                }
            }
        }

        return dp[n][4].indices;
    }
};