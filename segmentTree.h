#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
using namespace std;

struct SegmentTreeNode {
    int value;
    SegmentTreeNode *leftNode, *rightNode;

    void createSubNode() {
        if (leftNode == NULL) leftNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode)); 
        if (rightNode == NULL) rightNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
    }
    SegmentTreeNode() {value = 0; leftNode = rightNode = NULL;}
    SegmentTreeNode(int value) {value = value; leftNode = rightNode = NULL;}
    ~SegmentTreeNode() {delete leftNode; delete rightNode; leftNode = rightNode = NULL;}
};

struct SegmentTree {
    SegmentTreeNode *root;
    int activeNode = 0;
    
    void createTree() {
        root = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
    }

    void update(SegmentTreeNode *currNode, int l, int r, int pos, int value,  
        function<void(SegmentTreeNode*, int)> change, function<void(SegmentTreeNode*, SegmentTreeNode*, SegmentTreeNode*)> merge) {
        
        if (l > pos || r < pos) return;
        if (l == r) {
            change(currNode, value);
            return;
        }

        int mid = (l + r) >> 1;
        currNode -> createSubNode();
        update(currNode -> leftNode, l, mid, pos, value, change, merge);
        update(currNode -> rightNode, mid + 1, r, pos, value, change, merge);
        merge(currNode, currNode -> leftNode, currNode -> rightNode);
    }

    SegmentTreeNode* get(SegmentTreeNode *currNode, int l, int r, int u, int v, SegmentTreeNode* defaultValue,
        function<void(SegmentTreeNode*, SegmentTreeNode*, SegmentTreeNode*)> merge) {

        if (l > v || r < u) return defaultValue;
        if (u <= l && r <= v) currNode; 

        int mid = (l + r) >> 1; 
        currNode -> createSubNode();
        SegmentTreeNode* result = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode)); 
        merge(
            result,
            get(currNode -> leftNode, l, mid, u, v, defaultValue, merge), 
            get(currNode -> rightNode, mid + 1, r, u, v, defaultValue, merge)
        );
        return result;
    }
};