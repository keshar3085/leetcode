class Solution {
public:
    static const long long LIM = 10000001;

    long long combCap(int n, int r){
        if(r < 0 || r > n)return 0;
        r = min(r, n - r);
        long long res =1;
        for(int i =1; i <= r; i++){
            res = res *(n - r + i)/i;
            if (res >= LIM )return LIM;
        }
        return res;
    }
    long long countWays(vector<int> & cnt){
        int total = 0;
        for(int x : cnt) total +=x;

        long long ans =1;
        int rem = total;

        for(int i =0; i < 26; i++){
            if(cnt[i] == 0) continue;
            ans *= combCap(rem, cnt[i]);
            if(ans >= LIM) return LIM;
            rem -= cnt[i];

        }
        return min(ans,LIM);
    }
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for(char c : s)freq[c - 'a']++;
        vector<int> cnt(26);
        string mid = "";
        for(int i = 0; i<26; i++){
            cnt[i] = freq[i]/2;
            if(freq[i] % 2)mid.push_back(char('a'+i));

        }
        if(countWays(cnt) < k)return "";
        int len = s.size()/2;
        string left = "";

        for(int pos = 0;pos < len;pos++ ){
            for(int c = 0;c < 26;c++){
                if(cnt[c] == 0)continue;
                cnt[c]--;
                long long ways = countWays(cnt);
                if(ways >= k){
                    left.push_back(char('a'+c));
                    break;
                }
                else{
                    k-=ways;
                    cnt[c]++;

                }
            }
        }
        string right = left;
        reverse(right.begin(),right.end());
        return left + mid + right;
    }
};