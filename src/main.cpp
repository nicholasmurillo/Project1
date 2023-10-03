#include <iostream>
#include <sstream>
#include <algorithm>
#include "../src/avltree.h"

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
	// Create initial AVL Tree
	MyAVLTree tree;
	// read how many lines of commands there are
	std::string firstline;
	std::getline(std::cin, firstline);
	for(auto num : firstline)
	{
		if(!isdigit(num))
		{
			std::cout << "Invalid First Line, Input a Number" << std::endl;
			return 0;
		}
	}
	int numlines = std::stoi(firstline);

	for(int i = 0; i < numlines; i++)
	{
		// read one line of input from cin
		std::string line;
		std::getline(std::cin, line);

		// create an input stream from line
		std::istringstream in(line);

		// read the first word from input stream, should be a command
		std::string command;
		in >> command;
		// Checking if command is valid
		int commandIdx = checkCommand(command);
		std::string name;
		std::string id;
		switch (commandIdx)
		{
			// -1 means command is not found in command list
			case -1:
				std::cout << "unsuccessful" << std::endl;
				break;
			// 0: Insert
			case 0:
				// Getting whatever is in quotes
				std::getline(in, name, '\"');
				std::getline(in, name, '\"');
				if(!checkName)
				{
					std::cout << "unsuccessful" << std::endl;
					break;
				}
				// Get the rest of the line, should be id
				std::getline(in, id);
				// Remove spaces from rest of id string, found from stack overflow:
				// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
				id.erase(std::remove(id.begin(), id.end(), ' '), id.end());
				if(!checkID(id))
				{
					std::cout << "unsuccessful" << std::endl;
					break;
				}
				// If everything is valid, insert into AVL Tree
				tree.insert(name, id);
				break;
			// 1: Remove
			case 1:
				// Put rest of line in id string
				std::getline(in, id);
				// Remove spaces from rest of id string, found from stack overflow:
				// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
				id.erase(std::remove(id.begin(), id.end(), ' '), id.end());
				if(!checkID(id))
				{
					std::cout << "unsuccessful" << std::endl;
					break;
				}
				tree.remove(id);
				break;
			// 2: Search
			case 2:
				// Two cases: ID or Name search
				// Get everything into name first
				std::getline(in, name);
				// See if there are quotes, if true, name search
				if(name.find('\"') != std::string::npos)
				{
					// Quote is found, strip anything outside quotes
					std::size_t firstQuote = name.find('\"');
					std::size_t secondQuote = name.find('\"', firstQuote + 1);
					name = name.substr(firstQuote + 1, secondQuote - firstQuote - 1);
					// Check if name is valid
					if(!checkName(name))
					{
						std::cout << "unsuccessful" << std::endl;
						break;
					}
					tree.searchName(name);
				}
				else
				{
					id = name;
					// Quote not found, remove spaces then check ID
					// Remove spaces from rest of id string, found from stack overflow:
					// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
					id.erase(std::remove(id.begin(), id.end(), ' '), id.end());
					if(!checkID(id))
					{
						std::cout << "unsuccessful" << std::endl;
						break;
					}
					tree.searchID(id);
				}
				break;
			// 3: PrintInorder
			case 3:
				tree.printInorder();
				break;
			// 4: PrintPreorder
			case 4:
				tree.printPreorder();
				break;
			// 5: PrintPostorder
			case 5:
				tree.printPostorder();
				break;
			// 6: PrintLevelCount
			case 6:
				tree.printLevelCount();
				break;
			// 7: RemoveInorder
			case 7:
				// Use id string for number of inorder removal
				std::getline(in, id);
				// Remove spaces from rest of id string, found from stack overflow:
				// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
				id.erase(std::remove(id.begin(), id.end(), ' '), id.end());
				if(!checkNum(id))
				{
					std::cout << "unsuccessful" << std::endl;
					break;
				}
				else
				{
					tree.removeInorder(std::stoi(id));
				}
				break;
			default:
				break;
		}
	}

	return 0;
}

