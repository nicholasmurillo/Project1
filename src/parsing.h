#include <iostream>
#include <sstream>

bool checkName(std::string name)
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

bool checkID(std::string id)
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