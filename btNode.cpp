#include "btNode.h"

//Inserts a new integer into the BST in an iterative manner
void bst_insert(btNode*& bst_root, int insInt) {
    //if the tree is empty, create a new root node with the given value 
    if (!bst_root) {
        bst_root = new btNode{ insInt, nullptr, nullptr };
        return;
    }
    // Use a cursor pointer to traverse the tree
    btNode* cursor = bst_root;
    while (true) {
        if (insInt < cursor->data) {
            if (cursor->left) {
                cursor = cursor->left;// Continue traversing left
            }
            else {
                cursor->left = new btNode{ insInt, nullptr, nullptr };//Insert as left child
                break;
            }
        }
        //If the insertion value is greater, move right
        else if (insInt > cursor->data) {
            if (cursor->right) {
                cursor = cursor->right;//continue traversing right
            }
            else {
                cursor->right = new btNode{ insInt, nullptr, nullptr };//Insert at the right
                break;
            }
        }
        //If the value already exsists, overwrite it(mimicking key update)
        else {
            cursor->data = insInt;
            break;
        }
    }
}
//Remive a specified integer from the BST if it exists
bool bst_remove(btNode*& bst_root, int remInt) {
    //If the tree is empty, nothing to remove
    if (!bst_root) return false;

    // if trmInt is less than the current node, move to the left subtree
    if (remInt < bst_root->data) {
        return bst_remove(bst_root->left, remInt);
    }
    // if remInt is greater than the current node, move to the right subtree
    else if (remInt > bst_root->data) {
        return bst_remove(bst_root->right, remInt);
    }
    //found the node to remove
    else {
        //Case 1: Node has no children (Leaf node)
        if (!bst_root->left && !bst_root->right) {
            delete bst_root; //delete the node
            bst_root = nullptr;//set pointer to null
        }
        //case 2: Node has only a left child
        else if (bst_root->left && !bst_root->right) {
            btNode* oldNode = bst_root;
            bst_root = bst_root->left; //Promote the left child to the current position
            delete oldNode;
        }
        //case 3: Node only has a right child
        else if (!bst_root->left && bst_root->right) {
            btNode* oldNode = bst_root;
            bst_root = bst_root->right;//Promote the right child to the current position
            delete oldNode;
        }
        //Case 4: Node has two children
        else {
            int maxLeft;
            bst_remove_max(bst_root->left, maxLeft);//Find and remove the largest value in the left subtree
            bst_root->data = maxLeft;//Reaplce current node's value with maxLeft
        }
        return true;//Successfully removed
    }
}

//Remove the largest integer in the BST and set the removed value
void bst_remove_max(btNode*& bst_root, int& removed) {
    //Base case: rightmost node (Largest) is found
    if (!bst_root->right) {
        removed = bst_root->data; //Store the largest value
        btNode* oldNode = bst_root;
        bst_root = bst_root->left; //Promote the left child(if any) to replace the removed node
        delete oldNode;
    }
    else {
        //recursive case: keep moving right
        bst_remove_max(bst_root->right, removed);
    }
}



void portToArrayInOrder(btNode* bst_root, int* portArray)
{
    if (bst_root == 0) return;
    int portIndex = 0;
    portToArrayInOrderAux(bst_root, portArray, portIndex);
}

void portToArrayInOrderAux(btNode* bst_root, int* portArray, int& portIndex)
{
    if (bst_root == 0) return;
    portToArrayInOrderAux(bst_root->left, portArray, portIndex);
    portArray[portIndex++] = bst_root->data;
    portToArrayInOrderAux(bst_root->right, portArray, portIndex);
}

void tree_clear(btNode*& root)
{
    if (root == 0) return;
    tree_clear(root->left);
    tree_clear(root->right);
    delete root;
    root = 0;
}

int bst_size(btNode* bst_root)
{
    if (bst_root == 0) return 0;
    return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}