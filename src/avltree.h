#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <exception>
#include "../src/parsing.h"

struct TreeNode {
    int height = 1;
    std::string id;
    std::string name;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(std::string name, std::string id) 
    {
        this->id = id;
        this->name = name;
    }
};

struct MyAVLTree {
    int height = 0;
    TreeNode* topNode = nullptr;
    // Balance Factor Function
    // TODO: Find source for rotations
    int balFactor(TreeNode* root)
    {
        if(root == nullptr)
        {
            return 0;
        }
        else
        {
            int left_height = root->left ? root->left->height : 0;
            int right_height = root->right ? root->right->height : 0;
            return left_height - right_height;
        }
    }
    // Left Rotation
    TreeNode* leftRotate(TreeNode* root)
    {
        TreeNode* rightchild = root->right;
        TreeNode* childleft = rightchild->left;
        rightchild->left = root;
        root->right = childleft;
        root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        rightchild->height = 1 + std::max(rightchild->left ? rightchild->left->height : 0, rightchild->right ? rightchild->right->height : 0);
        if(root == this->topNode)
        {
            this->topNode = rightchild;
        }
        return rightchild;
    }
    // Right Rotation
    TreeNode* rightRotate(TreeNode* root)
    {
        TreeNode* leftchild = root->left;
        TreeNode* childright = leftchild->right;
        leftchild->right = root;
        root->left = childright;
        root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        leftchild->height = 1 + std::max(leftchild->left ? leftchild->left->height : 0, leftchild->right ? leftchild->right->height : 0);
        if(root == this->topNode)
        {
            this->topNode = leftchild;
        }
        return leftchild;
    }
    // Insert function, called once
    void insert(std::string name, std::string id)
    {
        if(!checkName(name) or !checkID(id)) // Checking if name and id are valid
            {
                std::cout << "unsuccessful\n";
                return;
            }
        insertHelper(this->topNode, name, id);
        std::cout << "successful\n";
    }
    // Insert Helper Function, recursively called
    TreeNode* insertHelper(TreeNode* root, std::string name, std::string id) 
    {
        if(this->topNode == nullptr)
        {
            this->topNode = new TreeNode(name, id);
            return this->topNode;
        }
        if(root == nullptr)
        {
            return new TreeNode(name, id);
        }
        if(std::stoi(id) < std::stoi(root->id))
        {
            root->left = insertHelper(root->left, name, id);
        }
        else if(std::stoi(id) > std::stoi(root->id))
        {
            root->right = insertHelper(root->right, name, id);
        }
        else
        {
            return root;
        }
        // Updating heights after insertion
        // Source: In class review from professor (from slides in class)
        root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        // After updating heights, check all balance factors of affected nodes
        int balFac = balFactor(root);
        // Balancing Subtrees After Insertion
        // TODO: Find source for balance cases
        // Left Left Case
        if(balFac > 1 && std::stoi(id) < std::stoi(root->left->id))
        {
            return rightRotate(root);
        }
        // Right Right Case
        else if(balFac < -1 && std::stoi(id) > std::stoi(root->right->id))
        {
            return leftRotate(root);
        }
        // Left Right Case
        else if(balFac > 1 && std::stoi(id) > std::stoi(root->left->id))
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        // Right Left Case
        else if(balFac < -1 && std::stoi(id) < std::stoi(root->right->id))
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    // Remove ID Function, Prioritizes In Order Successor
    void remove(std::string id) 
    {
        // Check if ID is valid first
        if(checkID(id))
        {
            TreeNode* temp = searchIDHelper(this->topNode, id);
            // If temp is nullptr, below if statement does not run, prints unsuccessful
            if(temp == nullptr)
            {
                std::cout << "unsuccessful\n";
            }
            else
            {
                removeHelper(this->topNode, id);
                std::cout << "successful\n";
            }
        }
        else
        {
            std::cout << "unsuccessful\n";
        }
    }
    // Successor Node Finder Function
    TreeNode* successorNode(TreeNode* node)
    {
        if(node->left == nullptr)
        {
            return node;
        }
        else
        {
            return successorNode(node->left);
        }
    }

    // Remove ID Helper Function
    TreeNode* removeHelper(TreeNode* root, std::string id)
    {
        // If root is nullptr, id is not in tree
        if(root == nullptr)
        {
            std::cout << "unsuccessful\n";
            return root;
        }
        // Id is less than root id, recurse through left node
        if(std::stoi(id) < std::stoi(root->id))
        {
            root->left = removeHelper(root->left, id);
        }
        // Id is more than root id, recurse through right node
        else if(std::stoi(id) > std::stoi(root->id))
        {
            root->right = removeHelper(root->right, id);
        }
        else
        {
            // No children or one child case
            // TODO: Find source for deletion of AVL Tree
            if(root->left == nullptr or root->right == nullptr)
            {
                TreeNode* temp = root->left ? root->left : root->right;
                // No Children Case if root->left and root->right are nullptr
                if(temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                // One Child Case
                else
                {
                    // Dereferenced node contents of temp copied into root
                    *root = *temp;
                    free(temp);
                }
            }
            // Two Children Case
            else
            {
                TreeNode* temp = successorNode(root->right);
                root->id = temp->id;
                root->name = temp->name;
                root->right = removeHelper(root->right, temp->id);
            }
            // If TreeNode was only one in tree, return and set height to 0
            if(root == nullptr)
            {
                this->height = 0;
                this->topNode = nullptr;
                return root;
            }
            // Updating heights of nodes after deletion
            root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        }
        return root;
    }
    void searchID(std::string id)
    {
        // Check if ID is valid first
        if(checkID(id))
        {
            TreeNode* temp = searchIDHelper(this->topNode, id);
            // If temp is nullptr, below if statement does not run, prints unsuccessful
            if(temp)
            {
                std::cout << temp->name << "\n";
            }
            else
            {
                std::cout << "unsuccessful\n";
            }
        }
        else
        {
            std::cout << "unsuccessful\n";
        }
    }
    // searchIDHelper
    TreeNode* searchIDHelper(TreeNode* root, std::string id) 
    {
        if(root == nullptr || std::stoi(id) == std::stoi(root->id))
        {
            return root;
        }
        else if(std::stoi(id) < std::stoi(root->id))
        {
            return searchIDHelper(root->left, id);
        }
        else
        {
            return searchIDHelper(root->right, id);
        }
    }
    // Search Name
    void searchName(const std::string& name)
    {
        bool foundName = false;
        std::vector<TreeNode*> nodelist;
        traversePreorder(this->topNode, nodelist);
        for(int i = 0; i < (int)(nodelist.size()); i++)
        {
            if(nodelist[i]->name == name)
            {
                std::cout << nodelist[i]->id << "\n";
                foundName = true;
            }
        }
        if(!foundName)
        {
            std::cout << "unsuccessful\n";
        }
        return;   
    }
    // Print Inorder
    void printInorder()
    {
        try
        {
            std::vector<TreeNode*> nodelist;
            traverseInorder(this->topNode, nodelist);
            for(int i = 0; i < (int)(nodelist.size()); i++)
            {
                if(i == (int)(nodelist.size() - 1))
                {
                    std::cout << nodelist[i]->name << "\n";
                }
                else
                {
                    std::cout << nodelist[i]->name << ", ";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printInorder\n";
        }
    }
    // Inorder Traversal (Helper function for printInorder)
    void traverseInorder(TreeNode* root, std::vector<TreeNode*>& nodelist)
    {
        if(root != nullptr)
        {
            traverseInorder(root->left, nodelist);
            nodelist.push_back(root);
            traverseInorder(root->right, nodelist);
        }
    }
    // Print Preorder
    void printPreorder()
    {
        try
        {
            std::vector<TreeNode*> nodelist;
            traversePreorder(this->topNode, nodelist);
            for(int i = 0; i < (int)(nodelist.size()); i++)
            {
                if(i == (int)(nodelist.size() - 1))
                {
                    std::cout << nodelist[i]->name << "\n";
                } 
                else
                {
                    std::cout << nodelist[i]->name << ", ";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printpreorder\n";
        }
    }
    // Preorder Traversal (Helper function for printPreorder)
    void traversePreorder(TreeNode* root, std::vector<TreeNode*>& nodelist)
    {
        if(root != nullptr)
        {
            nodelist.push_back(root);
            traversePreorder(root->left, nodelist);
            traversePreorder(root->right, nodelist);
        }
    }
    // Print Postorder
    void printPostorder()
    {
        try
        {
            std::vector<TreeNode*> nodelist;
            traversePostorder(this->topNode, nodelist);
            for(int i = 0; i < (int)(nodelist.size()); i++)
            {
                if(i == (int)(nodelist.size() - 1))
                {
                    std::cout << nodelist[i]->name << "\n";
                }
                else
                {
                    std::cout << nodelist[i]->name << ", ";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printPostorder\n";
        }
    }
    // Postorder Traversal (Helper function for printPostorder)
    void traversePostorder(TreeNode* root, std::vector<TreeNode*>& nodelist)
    {
        if(root != nullptr)
        {
            traversePostorder(root->left, nodelist);
            traversePostorder(root->right, nodelist);
            nodelist.push_back(root);
        }
    }
    // Print Level Count (Just height of root node of tree)
    void printLevelCount()
    {
        if(this->topNode != nullptr)
        {
            this->height = this->topNode->height;
        }
        else
        {
            this->height = 0;
        }
        std::cout << this->height << "\n";
    }
    // Remove nth In order node
    void removeInorder(int n)
    {
        std::vector<TreeNode*> nodelist;
        traverseInorder(this->topNode, nodelist);
        if(n < (int)(nodelist.size()))
        {
            removeHelper(this->topNode, nodelist[n]->id);
            std::cout << "successful\n";
        }
        else
        {
            std::cout << "unsuccessful\n";
        }
    }  
    MyAVLTree() {}
    MyAVLTree(std::string name, std::string id) 
    {
        if(checkID(id) && checkName(name))
        {
            this->topNode = insertHelper(this->topNode, name, id);
            this->height++;
            std::cout << "successful\n";
        }
        else
        {
            std::cout << "unsuccessful\n";
        }
    }
    ~MyAVLTree()
    {
        std::vector<TreeNode*> templist;
        traverseInorder(this->topNode, templist);
        this->topNode = nullptr;
        this->height = 0;
        for(auto tempNode : templist)
            free(tempNode);
    }
};