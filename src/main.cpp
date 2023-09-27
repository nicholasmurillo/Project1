#include <iostream>
#include "../src/avltree.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
	MyAVLTree tree("Nicholas", "55182448");
	tree.insert("prof", "00001234");
	tree.insert("bruh", "00123420");
	return 0;
}

