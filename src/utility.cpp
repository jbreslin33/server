#include "utility.h"

Utility::Utility()
{

}

std::string Utility::padZerosLeft(int sizeWanted, std::string s)
{
	while (s.size() < sizeWanted)
	{
		s.insert(0,"0");	
	}	
	return s;
}

std::vector<std::string> Utility::split(std::string s, std::string delim)
{
        std::vector<std::string> stringVector;

        size_t pos = 0;
        std::string token;
       	while ((pos = s.find(delim)) != std::string::npos)
       	{
       		token = s.substr(0, pos);
                stringVector.push_back(token);
                s.erase(0, pos + delim.length());
                //printf("e:%s\n",token.c_str());
	}

	return stringVector;
}
