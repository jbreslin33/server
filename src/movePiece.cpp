#include "movePiece.h"
#include "common/2d/vector2d.h"
#include "common/2d/c2dMatrix.h"

MovePiece::MovePiece(int x, int y, int z, double facingAngle) : BasePiece(x,y,z)
{
        mVelocity.x = x;
        mVelocity.y = y;

	mMaxSpeed = 0.25;
	mMaxForce = 1.0;
	mMaxTurnRate = 0.4;

	mFacingAngle = facingAngle;
	mRotateVelocity = 0.0;
	
	mSide = mHeading.Perp();
	printf("Cx:%f Cy:%f\n",mSide.x,mSide.y);

}


//--------------------------- RotateHeadingToFacePosition ---------------------
//
//  given a target position, this method rotates the entity's heading and
//  side vectors by an amount not greater than m_dMaxTurnRate until it
//  directly faces the target.
//
//  returns true when the heading is facing in the desired direction
//-----------------------------------------------------------------------------
bool MovePiece::RotateHeadingToFacePosition(Vector2D target)
{
  Vector2D toTarget = utility.Vec2DNormalize(target - mPosition);

  double dot = mHeading.Dot(toTarget);

  //some compilers lose acurracy so the value is clamped to ensure it
  //remains valid for the acos
  Clamp(dot, -1, 1);

  //first determine the angle between the heading vector and the target
  double angle = acos(dot);

  //return true if the player is facing the target
  if (angle < 0.00001) return true;

  //clamp the amount to turn to the max turn rate
  if (angle > mMaxTurnRate) angle = mMaxTurnRate;

  //The next few lines use a rotation matrix to rotate the player's heading
  //vector accordingly
        C2DMatrix RotationMatrix;

  //notice how the direction of rotation has to be determined when creating
  //the rotation matrix
        RotationMatrix.Rotate(angle * mHeading.Sign(toTarget));
  RotationMatrix.TransformVector2Ds(mHeading);
  RotationMatrix.TransformVector2Ds(mVelocity);

  //finally recreate m_vSide
  mSide = mHeading.Perp();

  return false;
}

