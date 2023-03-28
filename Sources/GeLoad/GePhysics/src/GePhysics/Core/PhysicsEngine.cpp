#include <algorithm>

#include "GePhysics/Core/PhysicsEngine.h"
#include "GePhysics/Tools/Conversion.h"
#include "GePhysics/Entities/PhysicalObject.h"

#include <GeDebug/Logger.h>

using namespace GePhysics::Tools;
using namespace GePhysics::Entities;

std::map< std::pair<PhysicalObject*, PhysicalObject*>, bool> GePhysics::Core::PhysicsEngine::m_collisionEvents;

GePhysics::Core::PhysicsEngine::PhysicsEngine(const Settings::PhysicsSettings & p_settings)
{
	m_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfig.get());
	m_broadphase = std::make_unique<btDbvtBroadphase>();
	m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
	m_world = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_broadphase.get(), m_solver.get(), m_collisionConfig.get());

	m_world->setGravity(Conversion::ToBtVector3(p_settings.gravity));

	ListenToPhysicalObjects();
	SetCollisionCallback();
}

void GePhysics::Core::PhysicsEngine::PreUpdate()
{
	std::for_each(m_physicalObjects.begin(), m_physicalObjects.end(), std::mem_fn(&PhysicalObject::UpdateBtTransform));

	ResetCollisionEvents();
}

void GePhysics::Core::PhysicsEngine::PostUpdate()
{
	std::for_each(m_physicalObjects.begin(), m_physicalObjects.end(), std::mem_fn(&PhysicalObject::UpdateFTransform));

	CheckCollisionStopEvents();
}

bool GePhysics::Core::PhysicsEngine::Update(float p_deltaTime)
{
	PreUpdate();

	if (m_world->stepSimulation(p_deltaTime, 10))
	{
		PostUpdate();
		return true;
	}

	return false;
}

std::optional<RaycastHit> GePhysics::Core::PhysicsEngine::Raycast(GeMaths::FVector3 p_origin, GeMaths::FVector3 p_direction, float p_distance)
{
	if (p_direction == GeMaths::FVector3::Zero)
		return {};

	btVector3 origin = Tools::Conversion::ToBtVector3(p_origin);
	btVector3 target = Tools::Conversion::ToBtVector3(p_origin + p_direction * p_distance);

	RaycastHit resultHit;

  //Try获得第一次命中
	btCollisionWorld::ClosestRayResultCallback ClosestRayCallback(origin, target);
	m_world->rayTest(origin, target, ClosestRayCallback);

	if (ClosestRayCallback.hasHit())
	{
    //获得第一次命中
		resultHit.FirstResultObject = reinterpret_cast<GePhysics::Entities::PhysicalObject*>(ClosestRayCallback.m_collisionObject->getUserPointer());

    //尝试获得所有命中
		btCollisionWorld::AllHitsRayResultCallback rayCallback(origin, target);
		m_world->rayTest(origin, target, rayCallback);

		//获得所有命中
		for (int i = 0; i < rayCallback.m_collisionObjects.size(); i++)
			resultHit.ResultObjects.push_back(reinterpret_cast<GePhysics::Entities::PhysicalObject*>(rayCallback.m_collisionObjects[i]->getUserPointer()));

		return resultHit;
	}
	else
		return {};
}

void GePhysics::Core::PhysicsEngine::SetGravity(const GeMaths::FVector3 & p_gravity)
{
	m_world->setGravity(Conversion::ToBtVector3(p_gravity));
}

GeMaths::FVector3 GePhysics::Core::PhysicsEngine::GetGravity() const
{
	return Conversion::ToOvVector3(m_world->getGravity());
}

void GePhysics::Core::PhysicsEngine::ListenToPhysicalObjects()
{
	PhysicalObject::CreatedEvent += std::bind(static_cast<void(PhysicsEngine::*)(PhysicalObject&)>(&PhysicsEngine::Consider), this, std::placeholders::_1);
	PhysicalObject::DestroyedEvent += std::bind(static_cast<void(PhysicsEngine::*)(PhysicalObject&)>(&PhysicsEngine::Unconsider), this, std::placeholders::_1);

	PhysicalObject::ConsiderEvent += std::bind(static_cast<void(PhysicsEngine::*)(btRigidBody&)>(&PhysicsEngine::Consider), this, std::placeholders::_1);
	PhysicalObject::UnconsiderEvent += std::bind(static_cast<void(PhysicsEngine::*)(btRigidBody&)>(&PhysicsEngine::Unconsider), this, std::placeholders::_1);
}

void GePhysics::Core::PhysicsEngine::Consider(PhysicalObject& p_toConsider)
{
	m_physicalObjects.push_back(std::ref(p_toConsider));
}

void GePhysics::Core::PhysicsEngine::Unconsider(PhysicalObject& p_toUnconsider)
{
	{
		auto found = std::find_if(m_physicalObjects.begin(), m_physicalObjects.end(), [&p_toUnconsider](std::reference_wrapper<PhysicalObject> element)
		{
			return std::addressof(p_toUnconsider) == std::addressof(element.get());
		});

		if (found != m_physicalObjects.end())
			m_physicalObjects.erase(found);
	}

	{
		decltype(m_collisionEvents)::iterator iter = m_collisionEvents.begin();
		decltype(m_collisionEvents)::iterator endIter = m_collisionEvents.end();

		for (; iter != endIter; )
		{
			if (iter->first.first == std::addressof(p_toUnconsider) || iter->first.second == std::addressof(p_toUnconsider))
			{
				m_collisionEvents.erase(iter++);
			}
			else {
				++iter;
			}
		}
	}
}

void GePhysics::Core::PhysicsEngine::Consider(btRigidBody& p_toConsider)
{
	m_world->addRigidBody(&p_toConsider);
}

void GePhysics::Core::PhysicsEngine::Unconsider(btRigidBody& p_toUnconsider)
{
	m_world->removeRigidBody(&p_toUnconsider);
}

void GePhysics::Core::PhysicsEngine::ResetCollisionEvents()
{
	for (auto& element : m_collisionEvents)
		element.second = false;
}

void GePhysics::Core::PhysicsEngine::CheckCollisionStopEvents()
{
	for (auto it = m_collisionEvents.begin(); it != m_collisionEvents.end();)
	{
		auto objects = it->first;
		if (!it->second)
		{
			if (!objects.first->IsTrigger() && !objects.second->IsTrigger())
			{
				objects.first->CollisionStopEvent.Invoke(*objects.second);
				objects.second->CollisionStopEvent.Invoke(*objects.first);
			}
			else
			{
				if (objects.first->IsTrigger())
					objects.first->TriggerStopEvent.Invoke(*objects.second);
				else
					objects.second->TriggerStopEvent.Invoke(*objects.first);
			}

			it = m_collisionEvents.erase(it);
		}
		else
			++it;
	}
}

bool GePhysics::Core::PhysicsEngine::CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
{
	auto object1 = reinterpret_cast<PhysicalObject*>(obj1->getCollisionObject()->getUserPointer());
	auto object2 = reinterpret_cast<PhysicalObject*>(obj2->getCollisionObject()->getUserPointer());

	if (object1 && object2)
	{
    //如果不是所有的对象都触发，则进入
		if (!object1->IsTrigger() || !object2->IsTrigger())
		{
			if (m_collisionEvents.find({ object1 , object2 }) == m_collisionEvents.end())
			{
        //如果对象是触发器，则调用 Trigger 事件，
        // 否则：是另一个对象触发器吗？ 是 -> 什么都不做，否 -> 调用碰撞事件
				if (object1->IsTrigger())
					object1->TriggerStartEvent.Invoke(*object2);
				else
				{
					if (!object2->IsTrigger())
						object1->CollisionStartEvent.Invoke(*object2);
				}

				if (object2->IsTrigger())
					object2->TriggerStartEvent.Invoke(*object1);
				else
				{
					if (!object1->IsTrigger())
						object2->CollisionStartEvent.Invoke(*object1);
				}

				if (object1->IsTrigger())
					object1->TriggerStayEvent.Invoke(*object2);
				else
				{
					if (!object2->IsTrigger())
						object1->CollisionStayEvent.Invoke(*object2);
				}

				if (object2->IsTrigger())
					object2->TriggerStayEvent.Invoke(*object1);
				else
				{
					if (!object1->IsTrigger())
						object2->CollisionStayEvent.Invoke(*object1);
				}

				m_collisionEvents[{ object1, object2 }] = true;
			}
			else
			{
				if (!m_collisionEvents[{ object1, object2 }])
				{
					if (object1->IsTrigger())
						object1->TriggerStayEvent.Invoke(*object2);
					else
					{
						if (!object2->IsTrigger())
							object1->CollisionStayEvent.Invoke(*object2);
					}

					if (object2->IsTrigger())
						object2->TriggerStayEvent.Invoke(*object1);
					else
					{
						if (!object1->IsTrigger())
							object2->CollisionStayEvent.Invoke(*object1);
					}

					m_collisionEvents[{ object1, object2 }] = true;
				}
			}
		}
	}

	return false;
}

void GePhysics::Core::PhysicsEngine::SetCollisionCallback()
{
	gContactAddedCallback = &PhysicsEngine::CollisionCallback;
}
