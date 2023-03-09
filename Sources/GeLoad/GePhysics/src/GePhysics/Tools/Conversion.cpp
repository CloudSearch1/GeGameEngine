#include "GePhysics/Tools/Conversion.h"

btTransform GePhysics::Tools::Conversion::ToBtTransform(const GeMaths::FTransform& p_transform)
{
	return btTransform(ToBtQuaternion(p_transform.GetWorldRotation()), ToBtVector3(p_transform.GetWorldPosition()));
}

btVector3 GePhysics::Tools::Conversion::ToBtVector3(const GeMaths::FVector3& p_vector)
{
	return btVector3(p_vector.x, p_vector.y, p_vector.z);
}

btQuaternion GePhysics::Tools::Conversion::ToBtQuaternion(const GeMaths::FQuaternion& p_quaternion)
{
	return btQuaternion(p_quaternion.x, p_quaternion.y, p_quaternion.z, p_quaternion.w);
}

GeMaths::FTransform GePhysics::Tools::Conversion::ToOvTransform(const btTransform& p_transform)
{
	GeMaths::FQuaternion q = ToOvQuaternion(p_transform.getRotation());
	GeMaths::FVector3  v = ToOvVector3(p_transform.getOrigin());
	return GeMaths::FTransform(v, q);
}

GeMaths::FVector3 GePhysics::Tools::Conversion::ToOvVector3(const btVector3& p_vector)
{
	return GeMaths::FVector3(p_vector.getX(), p_vector.getY(), p_vector.getZ());
}

GeMaths::FQuaternion GePhysics::Tools::Conversion::ToOvQuaternion(const btQuaternion& p_quaternion)
{
	return GeMaths::FQuaternion(p_quaternion.getX(), p_quaternion.getY(), p_quaternion.getZ(), p_quaternion.getW());
}
