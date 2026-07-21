class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";
        int m = t.size();

        vector<pair<char,int>> runs;
        for (int i = 0; i < m; ) {
            int j = i;
            while (j < m && t[j] == t[i]) j++;
            runs.push_back({t[i], j - i});
            i = j;
        }

        int ones = 0;
        for(char c : s)
            if(c == '1') ones++;

        int ans = ones;

        for(int i = 2; i + 2 < runs.size(); i += 2) {
            // runs[i] is a 1-block surrounded by 0-blocks
            int leftZero = runs[i-1].second;
            int rightZero = runs[i+1].second;

            int gain = leftZero + rightZero;
            ans = max(ans, ones + gain);
        }

        return ans;
    }
};