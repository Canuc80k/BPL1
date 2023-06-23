#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
using namespace std;

template <class T>
struct SegmentTreeNode {
    T value;
    SegmentTreeNode<T> *leftNode = NULL, *rightNode = NULL;

    void createSubNode() {
        if (leftNode == NULL) {
            leftNode = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>)); 
            leftNode -> value = 0;
            leftNode -> leftNode = leftNode -> rightNode = NULL;
        }
        if (rightNode == NULL) {
            rightNode = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>));
            rightNode -> value = 0;
            rightNode -> leftNode = rightNode -> rightNode = NULL;
        }
    }
};

template <class T>
struct SegmentTree {
    SegmentTreeNode<T> *root;
    int activeNode = 0;
    
    void createTree() {
        root = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>));
        root -> value = 0;
        root -> leftNode = root -> rightNode = NULL;
    }

    void update(SegmentTreeNode<T> *currNode, int l, int r, int pos, T value,  
        function<void(SegmentTreeNode<T>*, T)> change, function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> mergeSubNode) {
        
        if (l > pos || r < pos) return;
        if (l == r) {            
            change(currNode, value);
            return;
        }
        currNode -> createSubNode();

        int mid = (l + r) >> 1;
        update(currNode -> leftNode, l, mid, pos, value, change, mergeSubNode);
        update(currNode -> rightNode, mid + 1, r, pos, value, change, mergeSubNode);
        mergeSubNode(currNode, currNode -> leftNode, currNode -> rightNode);
    }

    SegmentTreeNode<T>* get(SegmentTreeNode<T> *currNode, int l, int r, int u, int v, SegmentTreeNode<T>* defaultValue,
        function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> mergeSubNode) {

        if (l > v || r < u) return defaultValue;
        if (u <= l && r <= v) return currNode; 

        int mid = (l + r) >> 1; 
        currNode -> createSubNode();
        SegmentTreeNode<T>* result = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>)); 
        mergeSubNode(
            result,
            get(currNode -> leftNode, l, mid, u, v, defaultValue, mergeSubNode), 
            get(currNode -> rightNode, mid + 1, r, u, v, defaultValue, mergeSubNode)
        );
        return result;
    }
};