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
