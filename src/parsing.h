#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <set>

// TODO: Check each line for a valid command, then the following depending on the command
bool checkLine(std::string line)
{
    return true;
}
// TODO: Check if command is valid
int checkCommand(const std::string& command)
{
    std::vector<std::string> goodCommands = {"insert", "remove", "search", "printInorder", "printPreorder", "printPostorder", "printLevelCount", "removeInorder"};
    for(int i = 0; i < (int)(goodCommands.size()); i++)
    {
        if(command == goodCommands[i])
        {
            return i;
        }
    }
    return -1;
}

// FIXME: Excess spaces handling with names, want to remove them?
bool checkName(const std::string& name)
{
    for(auto c : name) // Checking for characters a-z, A-Z, or space
        {
            if(not (isalpha(c) or c == ' '))
            {
                return false;
            }
        }
    return true;
}

bool checkID(const std::string& id)
{
    if(id.size() != 8)
    {
        return false;
    }
    for(auto num : id)
    {
        if(!isdigit(num))
        {
            return false;
        }
    }
    return true;
}

bool checkNum(const std::string& number)
{
    for(auto num : number)
    {
        if(!isdigit(num))
        {
            return false;
        }
    }
    return true;
}