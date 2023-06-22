#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
using namespace std;

struct SegmentTreeNode {
    long long value;
    SegmentTreeNode *leftNode = NULL, *rightNode = NULL;

    void createSubNode() {
        if (leftNode == NULL) {
            leftNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode)); 
            leftNode -> value = 0;
            leftNode -> leftNode = leftNode -> rightNode = NULL;
        }
        if (rightNode == NULL) {
            rightNode = (SegmentTreeNode*)malloc(sizeof(SegmentTreeNode));
            rightNode -> value = 0;
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
        // cout << currNode -> leftNode -> value << " " << currNode -> rightNode -> value << endl;

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