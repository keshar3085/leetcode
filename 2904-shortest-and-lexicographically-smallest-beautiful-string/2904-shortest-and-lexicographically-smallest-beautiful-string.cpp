class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> pos;
        for(int i =0;i<s.size();i++){
            if(s[i] == '1')
                pos.push_back(i);
            
        }
        if (pos.size() < k)
            return "";
        string ans = "";
        int minLen = INT_MAX; 
        
        for(int i=0; i+k-1 < pos.size();i++){
            int start = pos[i];
            int end = pos[i+k-1];
            int len = end - start +1;
            string curr = s.substr(start, len);

            if(len < minLen){
                minLen = len;
                ans = curr;
            }
            else if(len == minLen && curr < ans ){
                ans = curr;
            }

        }
        return ans;


    }
};