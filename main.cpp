#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include "segmentTree.h"
using namespace std;

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