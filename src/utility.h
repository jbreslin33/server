#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

class Vector2D;

class Utility
{
	public:
		Utility();
		std::string padZerosLeft(int sizeWanted, std::string s);
		std::vector<std::string> split(const std::string str, const std::string delim);

		Vector2D Vec2DNormalize(const Vector2D &v);
	
	private:
		
};

#endif

