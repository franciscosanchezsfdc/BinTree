//
//  main.cpp
//  BinTree
//
//  Created by Diana Gutierrez on 12/14/19.
//  Copyright © 2019 Diana Gutierrez. All rights reserved.
//

#include "BinTree.h"

using namespace std;

BinTree::BinTree() {
}

BinTree::~BinTree() {
    makeEmpty();
}

BinTree::BinTree(const BinTree& bt)
{
    if (root != bt.root) {
        root = new NodeData(*bt.root);
        if (bt.left) {
            left = new BinTree(*bt.left);
        }
        if (bt.right) {
            right = new BinTree(*bt.right);
        }
    }
}

BinTree& BinTree::operator=(const BinTree& rhs)
{
    // if we are doing BT=BT then don't remove the original
    if (this != &rhs)
    {
        // make sure there is some data to copy
        if (rhs.root != NULL) {
            root = new NodeData(*rhs.root);
            if (rhs.left) {
                left = new BinTree(*rhs.left);
            }
            if (rhs.right) {
                right = new BinTree(*rhs.right);
            }
        }
    }
    return *this;
}

bool BinTree::operator==(const BinTree& p)
{
    if (this == &p)
        return true;
    if ((*root) == (*p.root)) {
        bool answer = true;
        if (left && p.left) {
            answer &= (*left) == (*p.left);
        }
        if (!answer) return answer;
        if (right && p.right) {
            answer &= (*right) == (*p.right);
        }
        return answer;
    }
    return false;
}

bool BinTree::operator!=(const BinTree& p)
{
    return false;
}

bool BinTree::makeEmpty()
{
    if (root) {
        delete root;
        root = NULL;
    }
    if (left) {
        delete left;
        left = NULL;
    }
    if (right) {
        delete right;
        right = NULL;
    }
    return true;
}

int BinTree::getHeight() const
{
    if (!root) {
        return 0;
    }
    int hl = 0;
    int hr = 0;
    int h = 1;
    if (left) {
        hl = left->getHeight();
    }
    if (right) {
        hr = right->getHeight();
    }
    int max = (hl > hr) ? hl : hr;
    h += max;
    return h;
}

bool BinTree::insert(const NodeData *node)
{
    if (!node)
        return false;

    if (!root) {
        root = new NodeData(*node);
        return true;
    }
    
    if ((*root) == (*node)) {
        // ignore duplicates
        return false;
    }
    
    if ((*root) > (*node) ) {
        if (!left) {
            left = new BinTree();
        }
        return left->insert(node);
    } else {
        if (!right) {
            right = new BinTree();
        }
        return right->insert(node);
    }
    return false;
}

void BinTree::bsTreeToArray(NodeData* array[])
{
    bsTreeToArray(array, 0);
    root = NULL;
    left = NULL;
    right = NULL;
}

int BinTree::bsTreeToArray(NodeData* array[], int index)
{
    if (root) {
        if (left) {
            index = left->bsTreeToArray(array, index);
        }
        array[index] = root;
        root = NULL;
        index++;
        if (right) {
            index = right->bsTreeToArray(array, index);
        }
    }
    return index;
}

void BinTree::arrayToBSTree(NodeData* array[])
{
    makeEmpty();
    int sz = 0;
    while (array[sz] ) { sz++; }
    arrayToBSTree(array, 0, sz);
}

void BinTree::arrayToBSTree(NodeData* array[] , int low, int high)
{
    makeEmpty();
    int middle = (low+high) / 2;
    root = array[middle];
    array[middle] = NULL;
    if (low < middle) {
        left = new BinTree();
        left->arrayToBSTree(array, low, middle -1 );
    }
    if ((high - 1) > middle) {
        right = new BinTree();
        right->arrayToBSTree(array, middle + 1, high);
    }
}

bool BinTree::retrieve(const NodeData &elem, NodeData* &answer)
{
    if (root) {
        if (*root == elem) {
            answer = root;
            return true;
        }
        if (*root > elem && left) {
            return left->retrieve(elem, answer);
        }
        if (*root < elem && right) {
            return right->retrieve(elem, answer);
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const BinTree& p)
{
    if (p.root) {
        if (p.left) {
            os << *p.left;
        }
        os << " " << *p.root << " ";
        if (p.right) {
            os << *p.right;
        }
    }
    return os;
}

void BinTree::displaySideways()
{
    cout << endl;
    displaySideways("");
}

void BinTree::displaySideways(string buff)
{
    size_t offset = 1;
    if (root) {
        offset += root->getDate().length();
    }
    string spacer = string(offset + buff.length(), ' ');
    if (right) {
        right->displaySideways(spacer);
    }
    if (root) {
        if (right) {
            cout << string(spacer.length() - 1, ' ') << '/' << endl;
        }
        cout << buff;
        cout << *root << endl;
        if (left) {
            cout << string(spacer.length() - 1, ' ') << '\\' << endl;
        }
    }
    if (left) {
        left->displaySideways(spacer);
    }
}

int BinTree::getHeight(const NodeData &node) const
{
    if (*root == node) {
        return getHeight();
    } else {
        if (left) {
            int lh = left->getHeight(node);
            if (lh != 0) {
                return lh;
            }
        }
        if (right) {
            int rh = right->getHeight(node);
            if (rh != 0) {
                return rh;
            }
        }
    }
    return 0;
}