class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector <int> suff(m, -1);
        int i = n-1;
        int j = m-1;
        while(i>=0 && j>= 0){
            if(word1[i] == word2[j]){
                suff[j]=i;
                j--;
            }
            i--;

        }
        vector<int> ans;
        j=0;
        bool changed = false;
        for(i=0; i<n && j <m; i++){
            if(word1[i] == word2[j]){
                ans.push_back(i);
                j++;

            }
            else if(!changed && (j == m-1 || i < suff[j+1])){
                ans.push_back(i);
                j++;
                changed = true;
            }
        }
        if( j != m)
            return{};
        return ans;
        
    }
};