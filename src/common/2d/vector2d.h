#ifndef S2DVECTOR_H
#define S2DVECTOR_H
//------------------------------------------------------------------------
//
//  Name:   Vector2D.h
//
//  Desc:   2D vector struct
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <math.h>
//#include <windows.h>
#include <iosfwd>
#include <limits>
#include "common/misc/utils.h"

#include "utility.h"


class Vector2D
{
	public:
		double x;
  		double y;

  		Vector2D():x(0.0),y(0.0){}
  		Vector2D(double a, double b):x(a),y(b){}

  		//sets x and y to zero
  		void Zero(){x=0.0; y=0.0;}

  		//returns true if both x and y are zero
  		bool isZero()const{return (x*x + y*y) < MinDouble;}

  		//returns the length of the vector
  		double    Length();

  		//returns the squared length of the vector (thereby avoiding the sqrt)
  		double    LengthSq();

  		void      Normalize();

  		double    Dot(const Vector2D& v2);

 	 	//returns positive if v2 is clockwise of this vector,
  		//negative if anticlockwise (assuming the Y axis is pointing down,
  		//X axis to right like a Window app)
  		int       Sign(const Vector2D& v2);

  		//returns the vector that is perpendicular to this one.
  		Vector2D  Perp();

  		//adjusts x and y so that the length of the vector does not exceed max
  		void      Truncate(double max);

 		//returns the distance between this vector and th one passed as a parameter
  		double    Distance(const Vector2D &v2);

  		//squared version of above.
  		double    DistanceSq(const Vector2D &v2);

  		void      Reflect(Vector2D& norm);

  		//returns the vector that is the reverse of this vector
  		Vector2D  GetReverse();

  		//we need some overloaded operators
  		const Vector2D& operator+=(const Vector2D &rhs)
  		{
    			x += rhs.x;
    			y += rhs.y;
    			return *this;
  		}

  		const Vector2D& operator-=(const Vector2D &rhs)
  		{
    			x -= rhs.x;
    			y -= rhs.y;
    			return *this;
  		}

  		const Vector2D& operator*=(const double& rhs)
  		{
    			x *= rhs;
    			y *= rhs;
    			return *this;
  		}

  		const Vector2D& operator/=(const double& rhs)
  		{
    			x /= rhs;
			y /= rhs;
    			return *this;
  		}

  		bool operator==(const Vector2D& rhs)const
  		{
    			return (isEqual(x, rhs.x) && isEqual(y,rhs.y) );
  		}

  		bool operator!=(const Vector2D& rhs)const
  		{
    			return (x != rhs.x) || (y != rhs.y);
  		}
};

//-----------------------------------------------------------------------some more operator overloads
inline Vector2D operator*(const Vector2D &lhs, double rhs);
inline Vector2D operator*(double lhs, const Vector2D &rhs);
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator/(const Vector2D &lhs, double val);
std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);


//------------------------------------------------------------------------member functions
//

//------------------------------------------------------------------------non member functions

inline double Vec2DDistance(const Vector2D &v1, const Vector2D &v2)
{
  	double ySeparation = v2.y - v1.y;
  	double xSeparation = v2.x - v1.x;

  	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vec2DDistanceSq(const Vector2D &v1, const Vector2D &v2)
{
	double ySeparation = v2.y - v1.y;
  	double xSeparation = v2.x - v1.x;

  	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double Vec2DLength(const Vector2D& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

inline double Vec2DLengthSq(const Vector2D& v)
{
	return (v.x*v.x + v.y*v.y);
}

//------------------------------------------------------------------------operator overloads
inline Vector2D operator*(const Vector2D &lhs, double rhs)
{
	Vector2D result(lhs);
  	result *= rhs;
  	return result;
}

inline Vector2D operator*(double lhs, const Vector2D &rhs)
{
	Vector2D result(rhs);
  	result *= lhs;
  	return result;
}

//overload the - operator
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
  	result.x -= rhs.x;
  	result.y -= rhs.y;
  
  	return result;
}

//overload the + operator
inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
{
	Vector2D result(lhs);
  	result.x += rhs.x;
  	result.y += rhs.y;
  
  	return result;
}

//overload the / operator
inline Vector2D operator/(const Vector2D &lhs, double val)
{
	Vector2D result(lhs);
  	result.x /= val;
  	result.y /= val;
  	return result;
}

///////////////////////////////////////////////////////////////////////////////


//treats a window as a toroid
inline void WrapAround(Vector2D &pos, int MaxX, int MaxY)
{
	if (pos.x > MaxX) 
	{
		pos.x = 0.0;
	}

  	if (pos.x < 0)    
	{
		pos.x = (double)MaxX;
	}

 	if (pos.y < 0)    
	{
		pos.y = (double)MaxY;
	}

  	if (pos.y > MaxY) 
	{
		pos.y = 0.0;
	}
}

//returns true if the point p is not inside the region defined by top_left
//and bot_rgt
inline bool NotInsideRegion(Vector2D p,
                            Vector2D top_left,
                            Vector2D bot_rgt)
{
	return (p.x < top_left.x) || (p.x > bot_rgt.x) || 
         (p.y < top_left.y) || (p.y > bot_rgt.y);
}

inline bool InsideRegion(Vector2D p,
                         Vector2D top_left,
                         Vector2D bot_rgt)
{
	return !((p.x < top_left.x) || (p.x > bot_rgt.x) || 
         (p.y < top_left.y) || (p.y > bot_rgt.y));
}

inline bool InsideRegion(Vector2D p, int left, int top, int right, int bottom)
{
	return !( (p.x < left) || (p.x > right) || (p.y < top) || (p.y > bottom) );
}

//------------------ isSecondInFOVOfFirst -------------------------------------
//
//  returns true if the target position is in the field of view of the entity
//  positioned at posFirst facing in facingFirst
//-----------------------------------------------------------------------------
inline bool isSecondInFOVOfFirst(Vector2D posFirst,
                                 Vector2D facingFirst,
                                 Vector2D posSecond,
                                 double    fov)
{
	Utility utility;
	Vector2D toTarget = utility.Vec2DNormalize(posSecond - posFirst);

  	return facingFirst.Dot(toTarget) >= cos(fov/2.0);
}


#endif
