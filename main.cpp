#include <bits/stdc++.h>
#include "segmentTree.h"
using namespace std;

const int N = 1e5 + 1;

int n, q, u, v, type;
long long a[N];
SegmentTree<long long> st;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> q;
    st.createTree(1, n, 0, change_add<long long>, merge_sum<long long>);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        st.update(i, a[i]);
    }

    while (q --) {
        cin >> type >> u >> v;
        if (type == 1) st.update(u, v);
        else cout << st.get(u, v) -> value << '\n';
    }
    
    st.deleteTree(st.root);
    cout << endl;
}