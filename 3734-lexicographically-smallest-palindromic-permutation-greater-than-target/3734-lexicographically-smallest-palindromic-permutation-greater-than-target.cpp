class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {

        int n = s.size();
        int m = n / 2;

        vector<int> cnt(26, 0);

        for (char c : s)
            cnt[c - 'a']++;

        // Find middle character
        int odd = 0;
        int mid = -1;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = i;
            }
        }

        // More than one odd frequency -> impossible
        if (odd > 1)
            return "";

        // Characters available for left half
        vector<int> half(26);

        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;


        // Function to make palindrome from left half
        auto makePalindrome = [&](string left) {

            string ans = left;

            if (n % 2)
                ans += char('a' + mid);

            string rev = left;
            reverse(rev.begin(), rev.end());

            ans += rev;

            return ans;
        };


        // ------------------------------------------------
        // STEP 1:
        // Try using EXACT target's left half
        // ------------------------------------------------

        vector<int> rem = half;
        string left = target.substr(0, m);

        bool possible = true;

        for (char c : left) {

            if (rem[c - 'a'] == 0) {
                possible = false;
                break;
            }

            rem[c - 'a']--;
        }

        if (possible) {

            string ans = makePalindrome(left);

            // If same left half already gives a greater
            // palindrome, this is the smallest answer.
            if (ans > target)
                return ans;
        }


        // ------------------------------------------------
        // STEP 2:
        // Make left half just slightly greater
        // ------------------------------------------------

        for (int pos = m - 1; pos >= 0; pos--) {

            vector<int> rem = half;

            string prefix = target.substr(0, pos);

            bool possible = true;

            // Use target prefix
            for (char c : prefix) {

                if (rem[c - 'a'] == 0) {
                    possible = false;
                    break;
                }

                rem[c - 'a']--;
            }

            if (!possible)
                continue;


            // Choose smallest character greater than target[pos]
            for (int c = target[pos] - 'a' + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                string cur = prefix;

                cur += char('a' + c);

                rem[c]--;


                // Fill remaining positions with smallest chars
                for (int x = 0; x < 26; x++) {

                    cur += string(rem[x], char('a' + x));
                }


                // Since left half is greater than target's
                // left half, the palindrome is automatically
                // greater than target.
                return makePalindrome(cur);
            }
        }


        return "";
    }
};