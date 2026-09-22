class Solution {
public:

    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    vector<Node> tree;

    Node merge(Node left, Node right) {
        Node res;

        
        res.prod = (left.prod * right.prod) % k;

        
        for (int r = 0; r < k; r++) {
            res.cnt[r] = left.cnt[r];
        }

        
        for (int r = 0; r < k; r++) {
            int newRemainder = (left.prod * r) % k;
            res.cnt[newRemainder] += right.cnt[r];
        }

        return res;
    }

    void build(int node, int l, int r, vector<int>& nums) {

        if (l == r) {
            int val = nums[l] % k;

            tree[node].prod = val;
            tree[node].cnt[val] = 1;

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, nums);
        build(node * 2 + 1, mid + 1, r, nums);

        tree[node] = merge(tree[node * 2],
                            tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int index, int value) {

        if (l == r) {

            value %= k;

            tree[node].prod = value;

            memset(tree[node].cnt, 0, sizeof(tree[node].cnt));

            tree[node].cnt[value] = 1;

            return;
        }

        int mid = (l + r) / 2;

        if (index <= mid) {
            update(node * 2, l, mid, index, value);
        }
        else {
            update(node * 2 + 1, mid + 1, r, index, value);
        }

        tree[node] = merge(tree[node * 2],
                            tree[node * 2 + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {

        
        if (ql <= l && r <= qr) {
            return tree[node];
        }

        int mid = (l + r) / 2;

        
        if (qr <= mid) {
            return query(node * 2, l, mid, ql, qr);
        }

        
        if (ql > mid) {
            return query(node * 2 + 1, mid + 1, r, ql, qr);
        }

        
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);

        return merge(left, right);
    }

    vector<int> resultArray(vector<int>& nums,
                            int K,
                            vector<vector<int>>& queries) {

        k = K;

        int n = nums.size();

        tree.resize(4 * n);

        build(1, 0, n - 1, nums);

        vector<int> answer;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

           
            update(1, 0, n - 1, index, value);

            
            Node res = query(1, 0, n - 1,
                             start, n - 1);

            
            answer.push_back(res.cnt[x]);
        }

        return answer;
    }
};