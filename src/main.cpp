#include <iostream>
#include "../src/avltree.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
	MyAVLTree tree("Nicholas", "00000008");
	tree.insert("prof", "00000006");
	tree.insert("bruh", "00000001");
	tree.insert("matt", "99999999");
	tree.insert("pog", "99999998");
	std::cout << tree.successorNode(tree.root->right)->id << std::endl;
	std::cout << tree.root->height << std::endl;
	std::cout << tree.root->left->height << std::endl;
	std::cout << tree.root->right->height << std::endl;
	return 0;
}

