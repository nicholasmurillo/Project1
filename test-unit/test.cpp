#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <algorithm>
#include "../src/avltree.h"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

std::string runAVLTree(const std::string& filename)
{
	// Create initial AVL Tree
	MyAVLTree tree;
	// Catch2 Test output stream
	// Code from stackoverflow: https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
	std::ostringstream oss;
	std::streambuf* p_cout_streambuf = std::cout.rdbuf();
	std::cout.rdbuf(oss.rdbuf());
	// Open input file
	std::ifstream infile;
	infile.open("../test-io/input-files/" + filename);
	// read how many lines of commands there are
	std::string firstline;
	std::getline(infile, firstline);
	if(!checkNum(firstline))
	{
		return "";
	}
	int numlines = std::stoi(firstline);

	for(int i = 0; i < numlines; i++)
	{
		// read one line of input from infile
		std::string line;
		std::getline(infile, line);

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
				std::cout << "unsuccessful\n";
				break;
			// 0: Insert
			case 0:
				// Getting whatever is in quotes
				std::getline(in, name, '\"');
				std::getline(in, name, '\"');
				if(!checkName(name))
				{
					std::cout << "unsuccessful\n";
					break;
				}
				// Get the rest of the line, should be id
				std::getline(in, id);
				// Remove spaces from rest of id string, found from stack overflow:
				// https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
				id.erase(std::remove(id.begin(), id.end(), ' '), id.end());
				if(!checkID(id))
				{
					std::cout << "unsuccessful\n";
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
					std::cout << "unsuccessful\n";
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
						std::cout << "unsuccessful\n";
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
						std::cout << "unsuccessful\n";
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
					std::cout << "unsuccessful\n";
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
	// Close infile
	infile.close();
	// Open outfile
	std::ofstream outfile;
	outfile.open("../test-io/output-files/" + filename);
	// Restore oss
	std::cout.rdbuf(p_cout_streambuf);
	std::string finalText;
	finalText = oss.str();
	// Send oss string to outfile and close outfile
	if(outfile.is_open())
	{
		// If last two chars of oss is newline, do not print newline
		if(finalText.back() == '\n')
		{
			finalText.pop_back();
			outfile << finalText;
		}
		else
		{
			outfile << finalText;
		}
	}
	// Return oss str
	return oss.str();
}

bool compareFiles(const std::string& filename)
{
	std::string expectedLine;
	std::string actualLine;
	std::ifstream expectedFile, actualFile;
	expectedFile.open("../test-io/expected-output-files/" + filename);
	actualFile.open("../test-io/output-files/" + filename);
	if(!actualFile.is_open() or !expectedFile.is_open())
	{
		return false;
	}
	try
	{
		while(std::getline(actualFile, actualLine))
		{
			std::getline(expectedFile, expectedLine);
			if(actualLine != expectedLine)
			{
				actualFile.close();
				expectedFile.close();
				return false;
			}
		}
	}
	catch(...)
	{
		actualFile.close();
		expectedFile.close();
		return false;
	}
	actualFile.close();
	expectedFile.close();
	return true;
}



TEST_CASE("Output File #1", "[flag]"){
	runAVLTree("1.txt");
	REQUIRE(compareFiles("1.txt"));
}

TEST_CASE("Output File #2", "[flag]"){
	runAVLTree("2.txt");
	REQUIRE(compareFiles("2.txt"));
}

TEST_CASE("Output File #3", "[flag]"){
	runAVLTree("3.txt");
	REQUIRE(compareFiles("3.txt"));
}

TEST_CASE("Output File #4", "[flag]"){
	runAVLTree("4.txt");
	REQUIRE(compareFiles("4.txt"));
}

TEST_CASE("Output File #5", "[flag]"){
	runAVLTree("5.txt");
	REQUIRE(compareFiles("5.txt"));
}

TEST_CASE("Unit Test #6: Incorrect Commands", "[flag]"){
	// 5 Incorrect Commands
	runAVLTree("6.txt");
	REQUIRE(compareFiles("6.txt"));
}

TEST_CASE("Unit Test #7.1: Remove Top Node of Tree", "[flag]"){
	// 3 Edge Cases: Removing topNode of Tree
	runAVLTree("7_removeTop.txt");
	REQUIRE(compareFiles("7_removeTop.txt"));
}

TEST_CASE("Unit Test #7.2: Removing a Node that Does Not Exist", "[flag]"){
	// 3 Edge Cases: Removing a Node that does not exist
	runAVLTree("7_removeNotExist.txt");
	REQUIRE(compareFiles("7_removeNotExist.txt"));
}

TEST_CASE("Unit Test #8.1: Right Rotation", "[flag]"){
	runAVLTree("8_right.txt");
	REQUIRE(compareFiles("8_right.txt"));
}

TEST_CASE("Unit Test #8.2: Left Rotation", "[flag]"){
	runAVLTree("8_left.txt");
	REQUIRE(compareFiles("8_right.txt"));
}

TEST_CASE("Unit Test #8.3: Right Left Rotation", "[flag]"){
	runAVLTree("8_rightleft.txt");
	REQUIRE(compareFiles("8_rightleft.txt"));
}

TEST_CASE("Unit Test #8.4: Left Right Rotation", "[flag]"){
	runAVLTree("8_leftright.txt");
	REQUIRE(compareFiles("8_leftright.txt"));
}

TEST_CASE("Unit Test #9.1: No Child Deletion", "[flag]"){
	runAVLTree("9_nochild.txt");
	REQUIRE(compareFiles("9_nochild.txt"));
}

TEST_CASE("Unit Test #9.2: One Child Deletion", "[flag]"){
	runAVLTree("9_onechild.txt");
	REQUIRE(compareFiles("9_onechild.txt"));
}

TEST_CASE("Unit Test #9.1: Two Child Deletion", "[flag]"){
	runAVLTree("9_twochild.txt");
	REQUIRE(compareFiles("9_twochild.txt"));
}

TEST_CASE("Unit Test #10: Insert 100 Nodes, Remove 10"){
	// Create AVL Tree, expected and actual string vectors, and node list
	MyAVLTree tree;
	std::vector<int> expectedOutput, actualOutput;
	std::vector<TreeNode*> actualNodes;
	// Insert 100 Random Node IDs into Tree
	for(int i = 0; i < 50; i++)
	{
		int randomInput = rand();
		randomInput = (randomInput % 89999999) + 10000000;
		if(std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
		{
			expectedOutput.push_back(randomInput);
			tree.insert("Test", std::to_string(randomInput));
		}
	}
	// Sort both vectors based off ID
	std::sort(expectedOutput.begin(), expectedOutput.end());
	tree.traverseInorder(tree.topNode, actualNodes);
	// TODO: Remove 10 random nodes
	for(auto node : actualNodes)
	{
		actualOutput.push_back(std::stoi(node->id));
	}
	// actualOutput should be 90 if removed 10 nodes from inital 100
	REQUIRE(actualOutput.size() == 50);
	// actualOutput should be the same as expectedOutput
	REQUIRE(actualOutput == expectedOutput);
}