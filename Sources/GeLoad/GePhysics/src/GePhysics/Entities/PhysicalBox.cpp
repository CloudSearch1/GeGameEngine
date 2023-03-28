#include "GePhysics/Entities/PhysicalBox.h"
#include "GePhysics/Tools/Conversion.h"

GePhysics::Entities::PhysicalBox::PhysicalBox(const GeMaths::FVector3& p_size) : PhysicalObject()
{
	CreateCollisionShape(p_size);
	Init();
}

GePhysics::Entities::PhysicalBox::PhysicalBox(GeMaths::FTransform & p_transform, const GeMaths::FVector3& p_size) : PhysicalObject(p_transform)
{
	CreateCollisionShape(p_size);
	Init();
}

void GePhysics::Entities::PhysicalBox::SetSize(const GeMaths::FVector3& p_size)
{
	if (m_size != p_size)
		RecreateCollisionShape(p_size);
}

GeMaths::FVector3 GePhysics::Entities::PhysicalBox::GetSize() const
{
	return m_size;
}


void GePhysics::Entities::PhysicalBox::CreateCollisionShape(const GeMaths::FVector3& p_size)
{
	m_shape = std::make_unique<btBoxShape>(GePhysics::Tools::Conversion::ToBtVector3(p_size));
	m_size = p_size;
}

void GePhysics::Entities::PhysicalBox::RecreateCollisionShape(const GeMaths::FVector3& p_size)
{
	CreateCollisionShape(p_size);
	RecreateBody();
}

void GePhysics::Entities::PhysicalBox::SetLocalScaling(const GeMaths::FVector3 & p_scaling)
{
	m_shape->setLocalScaling(GePhysics::Tools::Conversion::ToBtVector3(p_scaling));
}
