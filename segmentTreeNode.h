#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
using namespace std;

template <class T>
struct SegmentTreeNode {
    T value, lazy;
    SegmentTreeNode<T> *leftNode = NULL, *rightNode = NULL;

    void createSubNode() {
        if (leftNode == NULL) {
            leftNode = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>)); 
            leftNode -> value = leftNode -> lazy = 0;
            leftNode -> leftNode = leftNode -> rightNode = NULL;
        }
        if (rightNode == NULL) {
            rightNode = (SegmentTreeNode<T>*)malloc(sizeof(SegmentTreeNode<T>));
            rightNode -> value = rightNode -> lazy = 0;
            rightNode -> leftNode = rightNode -> rightNode = NULL;
        }
    }
};