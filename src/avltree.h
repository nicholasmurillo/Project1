#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <exception>
#include "../src/parsing.h"

struct TreeNode {
    int height;
    std::string id;
    std::string name;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    void setRight(TreeNode* root) 
    {
        this->right = root;
    }
    void setLeft(TreeNode* root) 
    {
        this->left = root;
    }
    TreeNode(std::string id, std::string name) 
    {
        this->id = id;
        this->name = name;
    }
};

struct MyAVLTree {
    int height = 0;
    TreeNode* root = nullptr;
    // TODO: BALANCE TREE FUNC
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
        try
        {
            if(root == nullptr)
            {
                std::cout << "successful insert" << std::endl;
                root = new TreeNode(id, name);
                return root;
            }
            if(std::stoi(id) < std::stoi(root->id))
            {
                root->setLeft(insertHelper(root->left, name, id));
            }
            else if(std::stoi(id) > std::stoi(root->id))
            {
                root->setRight(insertHelper(root->right, name, id));
            }
            else // If id == root->id, id is a duplicate and is an unsuccessful insert
            {
                throw nullptr;
            }
            // TODO: INSERT BALANCE FUNCTION HERE
            return root;
        }
        catch(...)
        {
            std::cout << "unsuccessful" << std::endl;
            return nullptr;
        }
    }
    // TODO: REMOVE ID, PRIORITIZE IN ORDER SUCCESSOR (ONE RIGHT, THEN FURTHEST LEFT)
    TreeNode* remove(TreeNode* root, std::string id) 
    {
        try
        {
            if(root == nullptr)
            {
                throw nullptr;
            }
        }
        catch(...)
        {
            std::cout << "unsucessful" << std::endl;
        }
    }
    // searchID
    void searchID(TreeNode* root, std::string id) 
    {
        try
        {
            if(root == nullptr) // If root is nullptr, id is not in tree
            {
                throw nullptr;
            }
            if(std::stoi(id) == std::stoi(root->id))
            {
                std::cout << root->name << std::endl;
            }
            else if(std::stoi(id) < std::stoi(root->id))
            {
                searchID(root->left, id);
            }
            else
            {
                searchID(root->right, id);
            }
            return;
        }
        catch(...)
        {
            std::cout << "unsuccessful" << std::endl;
        }
        
    }
    // Search Name
    void searchName(const std::string& name)
    {
        try
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
                throw nullptr;
            }
        }
        catch(...)
        {
            std::cout << "unsuccessful" << std::endl;
        }
        
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
    // Print Level Count, goes through all the nodes everytime (keep a counter instead?)
    void printLevelCount()
    {
        this->height = getHeight(this->root);
        std::cout << this->height << std::endl;
    }
    // getHeight returns the height of the tree
    int getHeight(TreeNode* root)
    {
        if(root == nullptr)
        {
            return 0;
        }
        else
        {
            int left_height = getHeight(root->left);
            int right_height = getHeight(root->right);
            return std::max(left_height, right_height) + 1;
        }
    }
    // TODO: REMOVE IN ORDER NODE  
    MyAVLTree(std::string name, std::string id) {
        this->root = insertHelper(this->root, name, id);
        this->height++;
    }
};