#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include "templateGeneralFunction.h"
using namespace std;

template <class T>
struct SegmentTree {
    SegmentTreeNode<T> *root, *defaultNode;
    int activeNode = 0, head = -1, tail = -1;
    function<void(SegmentTreeNode<T>*, T)> defaultChangeMethod;
    function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> defaultMergeMethod;

    void createTree() {
        root = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>));
        root -> value = root -> lazy = 0;
        root -> leftNode = root -> rightNode = NULL;
    }

    void createTree(int headValue, int tailValue, int defaultValue,
        function<void(SegmentTreeNode<T>*, T)> change, 
        function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> mergeSubNode) {
        
        createTree();
        head = headValue;
        tail = tailValue;
        defaultNode = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>));
        defaultNode -> value = defaultValue;
        defaultChangeMethod = change;
        defaultMergeMethod = mergeSubNode;
    }

    void update(int pos, T value) {
        update(root, head, tail, pos, value, defaultChangeMethod, defaultMergeMethod);
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

    void update_lazy(SegmentTreeNode<T> *currNode, int l, int r, int u, int v, T value,  
        function<void(SegmentTreeNode<T>*, T)> change, 
        function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> mergeSubNode,
        function<void(SegmentTreeNode<T>*, int, int)> down) {
        
        if (u > r || v < l) return;
        if (u <= l && v >= r) {
            change(currNode, value);
            return;
        }
        currNode -> createSubNode();
        down(currNode, l, r);

        int mid = (l + r) >> 1;
        update_lazy(currNode -> leftNode, l, mid, u, v, value, change, mergeSubNode, down);
        update_lazy(currNode -> rightNode, mid + 1, r, u, v, value, change, mergeSubNode, down);
        mergeSubNode(currNode, currNode -> leftNode, currNode -> rightNode);
    }

    SegmentTreeNode<T>* get(int u, int v) {
        return get(root, head, tail, u, v, defaultNode, defaultMergeMethod);
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

    SegmentTreeNode<T>* get_lazy(SegmentTreeNode<T> *currNode, int l, int r, int u, int v, SegmentTreeNode<T>* defaultValue,
        function<void(SegmentTreeNode<T>*, SegmentTreeNode<T>*, SegmentTreeNode<T>*)> mergeSubNode,
        function<void(SegmentTreeNode<T>*, int, int)> down) {

        if (l > v || r < u) return defaultValue;
        if (u <= l && r <= v) return currNode; 

        currNode -> createSubNode();
        down(currNode, l, r);

        int mid = (l + r) >> 1; 
        SegmentTreeNode<T>* result = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>)); 
        mergeSubNode(
            result,
            get_lazy(currNode -> leftNode, l, mid, u, v, defaultValue, mergeSubNode, down), 
            get_lazy(currNode -> rightNode, mid + 1, r, u, v, defaultValue, mergeSubNode, down)
        );
        return result;
    }

    void deleteTree(SegmentTreeNode<T> *currNode) {
        if (currNode == NULL) return;

        deleteTree(currNode -> leftNode);
        deleteTree(currNode -> rightNode);
        free(currNode);
    }
};

