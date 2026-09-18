class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {

        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';

            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        
        for (int c = 0; c < 26; c++) {

            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];

            bool valid = true;

            for (int i = l; i <= r; i++) {

                int x = s[i] - 'a';

                
                if (first[x] < l) {
                    valid = false;
                    break;
                }

                
                r = max(r, last[x]);
            }

            if (valid) {
                intervals.push_back({l, r});
            }
        }

        
        sort(intervals.begin(), intervals.end(),
             [](const pair<int,int>& a,
                const pair<int,int>& b) {

            if (a.second != b.second)
                return a.second < b.second;

            return a.first > b.first;
        });

        vector<string> ans;

        int lastEnd = -1;

        
        for (auto [l, r] : intervals) {

            if (l > lastEnd) {

                ans.push_back(s.substr(l, r - l + 1));

                lastEnd = r;
            }
        }

        return ans;
    }
};