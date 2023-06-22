#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
// #include "segmentTree.h"
using namespace std;

struct SegmentTreeNode {
    long long value, defaultValue = 0;
    SegmentTreeNode *leftNode = NULL, *rightNode = NULL;

    void createSubNode() {
        if (leftNode == NULL) {
            leftNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode)); 
            leftNode -> value = defaultValue;
            leftNode -> leftNode = leftNode -> rightNode = NULL;
        }
        if (rightNode == NULL) {
            rightNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
            rightNode -> value = defaultValue;
            rightNode -> leftNode = rightNode -> rightNode = NULL;
        }
    }
};

struct SegmentTree {
    SegmentTreeNode *root;
    long long activeNode = 0;
    
    void createTree() {
        root = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
        root -> value = 0;
        root -> leftNode = root -> rightNode = NULL;
    }

    void update(SegmentTreeNode *currNode, long long l, long long r, long long pos, long long value,  
        function<void(SegmentTreeNode*, long long)> change, function<void(SegmentTreeNode*, SegmentTreeNode*, SegmentTreeNode*)> mergeSubNode) {
        
        if (l > pos || r < pos) return;
        if (l == r) {            
            change(currNode, value);
            return;
        }
        currNode -> createSubNode();

        long long mid = (l + r) >> 1;
        update(currNode -> leftNode, l, mid, pos, value, change, mergeSubNode);
        update(currNode -> rightNode, mid + 1, r, pos, value, change, mergeSubNode);
        mergeSubNode(currNode, currNode -> leftNode, currNode -> rightNode);
    }

    SegmentTreeNode* get(SegmentTreeNode *currNode, long long l, long long r, long long u, long long v, SegmentTreeNode* defaultValue,
        function<void(SegmentTreeNode*, SegmentTreeNode*, SegmentTreeNode*)> mergeSubNode) {

        if (l > v || r < u) return defaultValue;
        if (u <= l && r <= v) return currNode; 

        long long mid = (l + r) >> 1; 
        currNode -> createSubNode();
        SegmentTreeNode* result = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode)); 
        mergeSubNode(
            result,
            get(currNode -> leftNode, l, mid, u, v, defaultValue, mergeSubNode), 
            get(currNode -> rightNode, mid + 1, r, u, v, defaultValue, mergeSubNode)
        );
        return result;
    }
};

const long long N = 1e6 + 1;

long long n, q, type, u, v;
long long a[N];
SegmentTree st;

void changeNode(SegmentTreeNode* node, long long value) {
    node -> value += value;
}

void mergeSubNode(SegmentTreeNode* par, SegmentTreeNode* l, SegmentTreeNode* r) {
    par -> value = l -> value + r -> value;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    st.createTree();
    SegmentTreeNode *defaultValue = (SegmentTreeNode*)malloc(sizeof(defaultValue));
    defaultValue -> value = 0;

    cin >> n >> q;
    for (long long i = 1; i <= n; i ++) {
        cin >> a[i];
        st.update(st.root, 1, n, i, a[i], changeNode, mergeSubNode);
    }

    while (q --) {
        cin >> type >> u >> v;
        if (type == 1) st.update(st.root, 1, n, u, v, changeNode, mergeSubNode);
        else cout << st.get(st.root, 1, n, u, v, defaultValue, mergeSubNode) -> value << '\n';
    }
}