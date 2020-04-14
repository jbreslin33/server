#include "utility.h"
#include "common/2d/vector2d.h"

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

Vector2D Utility::Vec2DNormalize(const Vector2D &v)
{
        Vector2D vec = v;

        double vector_length = vec.Length();

        if (vector_length > std::numeric_limits<double>::epsilon())
        {
                vec.x /= vector_length;
                vec.y /= vector_length;
        }

        return vec;
}

double Vec2DDistance(const Vector2D &v1, const Vector2D &v2)
{
        double ySeparation = v2.y - v1.y;
        double xSeparation = v2.x - v1.x;

        return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

double Vec2DDistanceSq(const Vector2D &v1, const Vector2D &v2)
{
        double ySeparation = v2.y - v1.y;
        double xSeparation = v2.x - v1.x;

        return ySeparation*ySeparation + xSeparation*xSeparation;
}

double Vec2DLength(const Vector2D& v)
{
        return sqrt(v.x*v.x + v.y*v.y);
}

double Vec2DLengthSq(const Vector2D& v)
{
        return (v.x*v.x + v.y*v.y);
}

