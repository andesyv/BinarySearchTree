#include "binarynode.h"
#include <iostream>

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
    RemoveSubtree(root);
}

BinarySearchTree::Node* BinarySearchTree::CreateLeaf(int key)
{
    Node* n = new Node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;

    return n;
}

void BinarySearchTree::AddLeafPrivate(int key, BinarySearchTree::Node *Ptr)
{
    if(root == nullptr)
    {
        root = CreateLeaf(key);
    }
    else if(key < Ptr->key)
    {
        if(Ptr->left != nullptr)
        {
            AddLeafPrivate(key, Ptr->left);
        }
        else
        {
            Ptr->left = CreateLeaf(key);
        }
    }
    else if(key > Ptr->key)
    {
        if(Ptr->right != nullptr)
        {
            AddLeafPrivate(key, Ptr->right);
        }
        else
        {
            Ptr->right = CreateLeaf(key);
        }
    }
    else
    {
        std::cout << "The key " << key << " has already been added to the tree\n";
    }
}


void BinarySearchTree::AddLeaf(int key)
{
    AddLeafPrivate(key, root);
}


void BinarySearchTree::PrintInOrderPrivate(BinarySearchTree::Node* Ptr)
{
    if(root != nullptr)
    {
        //In-order traversal
        if (Ptr->left != nullptr)
        {
            PrintInOrderPrivate(Ptr->left);
        }

        std::cout << Ptr->key << ", ";

        if (Ptr->right != nullptr)
        {
            PrintInOrderPrivate(Ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty \n";
    }
}


void BinarySearchTree::PrintInPreOrderPrivate(BinarySearchTree::Node* Ptr)
{
    if(root != nullptr)
    {
        //Pre-order traversal
        std::cout << Ptr->key << ", ";
        if (Ptr->left != nullptr)
        {
            PrintInOrderPrivate(Ptr->left);
        }

        if (Ptr->right != nullptr)
        {
            PrintInOrderPrivate(Ptr->right);
        }
    }
    else
    {
        std::cout << "The tree is empty \n";
    }
}


void BinarySearchTree::PrintInOrder()
{
    PrintInOrderPrivate(root);
}

void BinarySearchTree::PrintPreOrder()
{

}

BinarySearchTree::Node *BinarySearchTree::ReturnNodePrivate(int key, BinarySearchTree::Node *Ptr)
{
    if(Ptr != nullptr)
    {
        if(Ptr->key == key)
        {
            return Ptr;
        }
        else
        {
            if(key < Ptr->key)
            {
                return ReturnNodePrivate(key, Ptr->left);
            }
            else
            {
                return ReturnNodePrivate(key, Ptr->right);
            }
        }
    }
    else
    {
        return nullptr;
    }
}

BinarySearchTree::Node *BinarySearchTree::ReturnNode(int key)
{
    return ReturnNodePrivate(key, root);
}

int BinarySearchTree::ReturnRootKey()
{
    if(root != nullptr)
    {
        return root->key;
    }
    else
    {
        return -1000;
    }
}



void BinarySearchTree::PrintChildren(int key)
{
    Node* Ptr = ReturnNode(key);

    if(Ptr != nullptr)
    {
        std::cout << "Parent Node = " << Ptr->key << std::endl;

        Ptr->left == nullptr ?
                    std::cout << "Left child = NULL\n" :
                    std::cout << "Left child = " << Ptr->left->key << std::endl;

        Ptr->right == nullptr ?
                    std::cout << "Right child = NULL\n" :
                    std::cout << "Right child = " << Ptr->right->key << std::endl;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Key " << key << " is not in the tree\n";
    }
}

int BinarySearchTree::FindSmallestPrivate(BinarySearchTree::Node *Ptr)
{
    if(root == nullptr)
    {
        std::cout << "The tree is empty\n";
        return -1000;
    }
    else
    {
        if(Ptr->left != nullptr)
        {
            return FindSmallestPrivate(Ptr->left);
        }
        else
        {
            return Ptr->key;
        }
    }
}

int BinarySearchTree::FindSmallest()
{
    return FindSmallestPrivate(root);
}


void BinarySearchTree::RemoveNodePrivate(int key, BinarySearchTree::Node *parent)
{
    if (root != nullptr)
    {
        if(root->key == key)
        {
            RemoveRootMatch();
        }
        else
        {
            if (key < parent->key && parent->left != nullptr)
            {
                parent->left->key == key ?
                RemoveMatch(parent, parent->left, true) :
                RemoveNodePrivate(key, parent->left);
            }
            else if (key > parent->key && parent->right != nullptr)
            {
                parent->right->key == key ?
                RemoveMatch(parent, parent->right, false) :
                RemoveNodePrivate(key, parent->right);
            }
            else
            {
                std::cout << "The key " << key << " was not found in the tree\n";
            }
        }
    }
    else
    {
        std::cout << "The tree is empty\n";
    }
}

void BinarySearchTree::RemoveRootMatch()
{
    if (root != nullptr)
    {
        Node* delPtr = root;
        int rootKey = root->key;
        int smallestKeyInRightSubTree;

        // Case 0 - 0 children
        if(root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            delete delPtr;
        }

        // Case 1 - 1 child
        else if(root->left == nullptr && root->right != nullptr)
        {
            root = root->right;
            delPtr->right = nullptr;
            delete delPtr;
            std::cout << "The root node conatining key " << rootKey << " was deleted. "
                      << "The new root contains key " << root->key << std::endl;
        }
        else if(root->left != nullptr && root->right == nullptr)
        {
            root = root->left;
            delPtr->left = nullptr;
            delete delPtr;
            std::cout << "The root node with key " << rootKey << " was deleted. "
                      << "The new root contains key " << root->key << std::endl;
        }

        // Case 2 - 2 children
        else
        {
            smallestKeyInRightSubTree = FindSmallestPrivate(root->right);
            RemoveNodePrivate(smallestKeyInRightSubTree, root);
            root->key = smallestKeyInRightSubTree;
            std::cout << "The root node containing key " << rootKey
                      << " was overwritten with key " << root->key << std::endl;
        }
    }
    else
    {
        std::cout << "Cannot remove root. The tree is empty\n";
    }
}

void BinarySearchTree::RemoveMatch(BinarySearchTree::Node *parent, BinarySearchTree::Node *match, bool left)
{
    if (root != nullptr)
    {
        Node* delPtr;
        int matchKey = match->key;
        int smallestKeyInRightSubTree;

        //Case 0 - 0 Children
        if(match->left == nullptr && match->right == nullptr)
        {
            delPtr = match;
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delPtr;
            std::cout << "The node containing key " << matchKey
                      << " was removed\n";
        }

        // Case 1 - 1 child
        else if (match->left == nullptr && match->right != nullptr)
        {
            left == true ? parent->left = match->right : parent = match->right;
            match->right = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey
                      << " was removed\n";
        }
        else if (match->left != nullptr && match->right == nullptr)
        {
            left == true ? parent->left = match->left : parent = match->left;
            match->left = nullptr;
            delPtr = match;
            delete delPtr;
            std::cout << "The node containing key " << matchKey
                      << " was removed\n";
        }

        // Case 2 - 2 Children
        else
        {
            smallestKeyInRightSubTree = FindSmallestPrivate(match->right);
            RemoveNodePrivate(smallestKeyInRightSubTree, match);
            match->key = smallestKeyInRightSubTree;
            std::cout << "The node containing key " << matchKey
                      << " was removed\n";
        }
    }
    else
    {
        std::cout << "Cannot remove root. The tree is empty\n";
    }
}

void BinarySearchTree::RemoveSubtree(BinarySearchTree::Node *Ptr)
{
    if(Ptr != nullptr)
    {
        //Post-order traversing
        if (Ptr->left != nullptr)
        {
            RemoveSubtree(Ptr->left);
        }
        if (Ptr->right != nullptr)
        {
            RemoveSubtree(Ptr->right);
        }
        std::cout << "Deleting the node containing key " << Ptr->key << std::endl;
        delete Ptr;
    }
}


void BinarySearchTree::RemoveNode(int key)
{
    RemoveNodePrivate(key, root);
}

