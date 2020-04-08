#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

class Utility
{
	public:
		Utility();
		std::string padZerosLeft(int sizeWanted, std::string s);
		std::vector<std::string> split(const std::string str, const std::string delim);

	
	private:
		
};

#endif

