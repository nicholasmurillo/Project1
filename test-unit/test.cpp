#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream>
#include <algorithm>
#include "../src/avltree.h"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

std::string AVLTree(const std::string& filename)
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
	for(auto num : firstline)
	{
		if(!isdigit(num))
		{
			std::cout << "Invalid First Line, Input a Number" << "\n";
			return 0;
		}
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
	AVLTree("1.txt");
	REQUIRE(compareFiles("1.txt"));
}

TEST_CASE("Output File #2", "[flag]"){
	AVLTree("2.txt");
	REQUIRE(compareFiles("2.txt"));
}

TEST_CASE("Output File #3", "[flag]"){
	AVLTree("3.txt");
	REQUIRE(compareFiles("3.txt"));
}

TEST_CASE("Output File #4", "[flag]"){
	AVLTree("4.txt");
	REQUIRE(compareFiles("4.txt"));
}

TEST_CASE("Output File #5", "[flag]"){
	AVLTree("5.txt");
	REQUIRE(compareFiles("5.txt"));
}