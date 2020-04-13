#include "vector2d.h"
#include <fstream>

std::ostream& operator<<(std::ostream& os, const Vector2D& rhs)
{
  os << " " << rhs.x << " " << rhs.y;

  return os;
}

  
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs)
{
  is >> lhs.x >> lhs.y;

  return is;
}



//------------------------- Length ---------------------------------------
//
//  returns the length of a 2D vector
//------------------------------------------------------------------------
double Vector2D::Length()
{
        return sqrt(x * x + y * y);
}

//------------------------- Normalize ------------------------------------
//
//  normalizes a 2D Vector
//------------------------------------------------------------------------
void Vector2D::Normalize()
{
        double vector_length = this->Length();

        if (vector_length > std::numeric_limits<double>::epsilon())
        {
                this->x /= vector_length;
                this->y /= vector_length;
        }
}

////------------------------- LengthSq -------------------------------------
//
//  returns the squared length of a 2D vector
//------------------------------------------------------------------------
double Vector2D::LengthSq()
{
        return (x * x + y * y);
}


//------------------------- Vec2DDot -------------------------------------
//
//  calculates the dot product
//------------------------------------------------------------------------
double Vector2D::Dot(const Vector2D &v2)
{
        return x*v2.x + y*v2.y;
}

//------------------------ Sign ------------------------------------------
//
//  returns positive if v2 is clockwise of this vector,
//  minus if anticlockwise (Y axis pointing down, X axis to right)
//------------------------------------------------------------------------

int Vector2D::Sign(const Vector2D& v2)
{
        enum {clockwise = 1, anticlockwise = -1};

        if (y*v2.x > x*v2.y)
        {
                return anticlockwise;
        }
        else
        {
                return clockwise;
        }
}

//------------------------------ Perp ------------------------------------
//
//  Returns a vector perpendicular to this vector
//------------------------------------------------------------------------
Vector2D Vector2D::Perp()
{
        return Vector2D(-y, x);
}

//------------------------------ Distance --------------------------------
//
//  calculates the euclidean distance between two vectors
//------------------------------------------------------------------------
double Vector2D::Distance(const Vector2D &v2)
{
        double ySeparation = v2.y - y;
        double xSeparation = v2.x - x;

        return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

//------------------------------ DistanceSq ------------------------------
//
//  calculates the euclidean distance squared between two vectors 
//------------------------------------------------------------------------
double Vector2D::DistanceSq(const Vector2D &v2)
{
        double ySeparation = v2.y - y;
        double xSeparation = v2.x - x;

        return ySeparation*ySeparation + xSeparation*xSeparation;
}

//----------------------------- Truncate ---------------------------------
//
//  truncates a vector so that its length does not exceed max
//------------------------------------------------------------------------
void Vector2D::Truncate(double max)
{
        if (this->Length() > max)
        {
                this->Normalize();
                *this *= max;
        }
}


//----------------------- GetReverse ----------------------------------------
//
//  returns the vector that is the reverse of this vector
//------------------------------------------------------------------------
Vector2D Vector2D::GetReverse()
{
        return Vector2D(-this->x, -this->y);
}

//--------------------------- Reflect ------------------------------------
//
//  given a normalized vector this method reflects the vector it
//  is operating upon. (like the path of a ball bouncing off a wall)
//------------------------------------------------------------------------
void Vector2D::Reflect(Vector2D& norm)
{
        *this += 2.0 * this->Dot(norm) * norm.GetReverse();
}


