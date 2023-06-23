#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include "segmentTree.h"
using namespace std;

const long long N = 1e6 + 1;

long long n, q, type, u, v, val;
long long a[N];
SegmentTree<long long> st;

void changeNode(SegmentTreeNode<long long>* node, long long value) {
    node -> value += value;
    node -> lazy += value;
}

void mergeSubNode(SegmentTreeNode<long long>* par, SegmentTreeNode<long long>* l, SegmentTreeNode<long long>* r) {
    par -> value = max(l -> value, r -> value);
}

void down(SegmentTreeNode<long long>* currNode, int l, int r) {
    if (currNode -> lazy == 0) return;

    currNode -> leftNode -> value += currNode -> lazy;
    currNode -> rightNode -> value += currNode -> lazy;
    currNode -> leftNode -> lazy += currNode -> lazy;
    currNode -> rightNode -> lazy += currNode -> lazy;

    currNode -> lazy = 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    st.createTree();
    SegmentTreeNode<long long> *defaultValue = (SegmentTreeNode<long long>*)malloc(sizeof(defaultValue));
    defaultValue -> value = -1e18;

    cin >> n >> q;

    while (q --) {
        cin >> type;
        if (type == 0) {
            cin >> u >> v >> val;
            st.update_lazy(st.root, 1, n, u, v, val, changeNode, mergeSubNode, down);
        } else {
            cin >> u >> v;
            cout << st.get_lazy(st.root, 1, n, u, v, defaultValue, mergeSubNode, down) -> value << '\n';
        }
    }
}