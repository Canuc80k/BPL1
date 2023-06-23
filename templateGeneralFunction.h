#include <bits/stdc++.h>
#include <cstdlib>
#include <functional>
#include "SegmentTreeNode.h"
using namespace std;

template <class T> void change_assign(SegmentTreeNode<T>* node, T value);
template <class T> void change_add(SegmentTreeNode<T>* node, T value);
template <class T> void merge_sum(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_max(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_min(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_gcd(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_lcm(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_or(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
template <class T> void merge_and(SegmentTreeNode<T>* par, SegmentTreeNode<T>* l, SegmentTreeNode<T>* r);
