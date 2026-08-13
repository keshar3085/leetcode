class Solution {
public:
    struct node{
        int len;
        int pref;
        int suff;
        int best;
        char leftChar;
        char rightChar;
        node(){
            len = pref = suff = best = 0;
            leftChar = rightChar = '#';

        }
    };
    vector<node> seg;
    string s;
    node merge(node a, node b){
        if(a.len == 0) return b;
        if(b.len == 0) return a;
        node res;
        res.len = a.len +b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;
        res.pref = a.pref;
        if(a.pref == a.len && a.rightChar == b.leftChar)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if(b.suff == b.len && a.rightChar == b.leftChar)
            res.suff = b.len + a.suff;
        res.best = max(a.best, b.best);
        if(a.rightChar == b.leftChar){
            res.best = max(res.best, a.suff + b.pref);
        }
        return res;
    }
    void build(int node, int l, int r){
        if(l == r){
            seg[node].len = 1;
            seg[node].pref = 1;
            seg[node].suff = 1;
            seg[node].best = 1;
            seg[node].leftChar = s[l];
            seg[node].rightChar = s[l];
            return;
        }
        int mid = l + (r - l)/2;
        build(node * 2,l,mid);
        build(node * 2 + 1, mid+ 1, r);

        seg[node]= merge(seg[node*2], seg[node* 2+1]);
    }
    void update(int node, int l, int r, int idx,char c){
        if(l == r){
            seg[node].leftChar = c;
            seg[node].rightChar = c;
            seg[node].pref = 1;
            seg[node].suff = 1;
            seg[node].best = 1;
            return;
        }
        int mid = l+(r-l)/2;
        if (idx <= mid)
            update(node*2, l,mid,idx,c);
        else
            update(node*2+1,mid+1,r,idx,c);
            seg[node]= merge(seg[node*2], seg[node * 2+1]);
    }
    
    
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        this->s = s;
        int n = s.size();
        seg.resize(4*n+5);
        build(1,0,n -1);
        vector<int> ans;
        for(int i = 0; i <queryIndices.size(); i++){
            int idx = queryIndices[i];
            char c = queryCharacters[i];
            update(1,0,n-1,idx,c);
            ans.push_back(seg[1].best);
        }
        return ans;
    }
};