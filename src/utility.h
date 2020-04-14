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

		double Vec2DDistance(const Vector2D &v1, const Vector2D &v2);

		double Vec2DDistanceSq(const Vector2D &v1, const Vector2D &v2);

		double Vec2DLength(const Vector2D& v);

		double Vec2DLengthSq(const Vector2D& v);
	
	private:
		
};

#endif

