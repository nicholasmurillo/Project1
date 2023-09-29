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
    int height = 1;
    TreeNode* root = nullptr;
    // Balance Factor Function
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
        if(root == this->root)
        {
            this->root = rightchild;
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
        if(root == this->root)
        {
            this->root = leftchild;
        }
        return leftchild;
    }
    // Insert function, called once
    void insert(std::string name, std::string id)
    {
        if(!checkName(name) or !checkID(id)) // Checking if name and id are valid
            {
                std::cout << "unsucessful" << std::endl;
                return;
            }
        insertHelper(this->root, name, id);
    }
    // Insert Helper Function, recursively called
    TreeNode* insertHelper(TreeNode* root, std::string name, std::string id) 
    {
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
        root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        // After updating heights, check all balance factors of affected nodes
        int balance = balFactor(root);
        // TODO: Balance using the balance factor info
        return root;
    }
    // Remove ID Function, Prioritizes In Order Successor
    void remove(std::string id) 
    {
        removeHelper(this->root, id);
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
            // If has any nullptr children, no children or one child case
            if(root->left == nullptr or root->right == nullptr)
            {
                TreeNode* temp = root->left ? root->left : root->right;
                // No Children Case if root->left and root->right are nullptr
                if(temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    // Dereferenced node contents of temp copied into root
                    *root = *temp;
                    delete temp;
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
            // If TreeNode was only one in tree, return before changing height
            if(root == nullptr)
            {
                return root;
            }
            // Updating heights of nodes after deletion
            root->height = 1 + std::max(root->left ? root->left->height : 0, root->right ? root->right->height : 0);
        }
        return root;
    }
    void search(std::string idname)
    {
        bool goodName;
        bool goodID;
        try
        {
            if(checkID(idname))
            {
                searchIDHelper(this->root, idname);
                goodID = true;
                return;
            }
        }
        catch(...)
        {
            goodID = false;
        }
        try
        {
            if(checkName(idname))
            {
                searchNameHelper(idname);
                goodName = true;
                return;
            }
        }
        catch(...)
        {
            goodName = false;
        }
        if(!goodName && !goodID)
        {
            std::cout << "invalid name/id" << std::endl;
        }
        return;
    }
    // searchID
    TreeNode* searchIDHelper(TreeNode* root, std::string id) 
    {
        if(root == nullptr) // If root is nullptr, id is not in tree
        {
            return root;
        }
        if(std::stoi(id) == std::stoi(root->id))
        {
            std::cout << root->name << std::endl;
        }
        else if(std::stoi(id) < std::stoi(root->id))
        {
            searchIDHelper(root->left, id);
        }
        else
        {
            searchIDHelper(root->right, id);
        }
        return root;
    }
    // Search Name
    void searchNameHelper(const std::string& name)
    {
        bool foundName = false;
        std::vector<TreeNode*> nodelist;
        traversePreorder(this->root, nodelist);
        for(int i = 0; i < nodelist.size(); i++)
        {
            if(nodelist[i]->name == name)
            {
                std::cout << nodelist[i]->id << std::endl;
                foundName = true;
            }
        }
        if(!foundName)
        {
            std::cout << "unsuccessful" << std::endl;
        }
        return;   
    }
    // Print Inorder
    void printInorder()
    {
        try
        {
            std::vector<TreeNode*> nodelist;
            traverseInorder(this->root, nodelist);
            for(int i = 0; i < nodelist.size(); i++)
            {
                if(i == nodelist.size() - 1)
                {
                    std::cout << nodelist[i]->name << std::endl;
                }
                else
                {
                    std::cout << nodelist[i]->name << ",";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printInorder" << std::endl;
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
            traversePreorder(this->root, nodelist);
            for(int i = 0; i < nodelist.size(); i++)
            {
                if(i == nodelist.size() - 1)
                {
                    std::cout << nodelist[i]->name << std::endl;
                } 
                else
                {
                    std::cout << nodelist[i]->name << ",";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printpreorder" << std::endl;
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
            traversePostorder(this->root, nodelist);
            for(int i = 0; i < nodelist.size(); i++)
            {
                if(i == nodelist.size() - 1)
                {
                    std::cout << nodelist[i]->name << std::endl;
                }
                else
                {
                    std::cout << nodelist[i]->name << ",";
                }
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful printPostorder" << std::endl;
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
        this->height = this->root->height;
        std::cout << this->height << std::endl;
    }
    // Remove nth In order node
    void removeInorder(int n)
    {
        std::vector<TreeNode*> nodelist;
        traverseInorder(this->root, nodelist);
        try
        {
            removeHelper(nodelist[n], nodelist[n]->id);
            std::cout << "successful" << std::endl;
        }
        catch(...)
        {
            std::cout << "unsuccessful" << std::endl;
        }
    }  
    MyAVLTree(std::string name, std::string id) {
        this->root = insertHelper(this->root, name, id);
    }
};