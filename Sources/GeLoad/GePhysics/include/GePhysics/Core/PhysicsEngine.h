#pragma once

#include <vector>
#include <map>
#include <optional>

#include "GePhysics/Entities/PhysicalObject.h"
#include "GePhysics/Settings/PhysicsSettings.h"
#include "GePhysics/Entities/RaycastHit.h"

namespace GePhysics::Core
{
  //GePhysics 的主要类，它处理物理世界的创建。 它必须在任何 PhysicalObject 之前创建，以确保考虑 PhysicalObject
	class PhysicsEngine
	{
	public:
		//创建物理引擎
		PhysicsEngine(const Settings::PhysicsSettings& p_settings);

		bool Update(float p_deltaTime);

    //对场景中的所有物理对象投射光线并返回有关被击中的信息
		std::optional<Entities::RaycastHit> Raycast(GeMaths::FVector3 p_origin, GeMaths::FVector3 p_direction, float p_distance);

    //定义要应用的世界重力
		void SetGravity(const GeMaths::FVector3& p_gravity);

    //返回当前世界重力
		GeMaths::FVector3 GetGravity() const;

	private:
		void PreUpdate();
		void PostUpdate();

		void ListenToPhysicalObjects();

		void Consider(GePhysics::Entities::PhysicalObject& p_toConsider);
		void Unconsider(GePhysics::Entities::PhysicalObject& p_toUnconsider);

		void Consider(btRigidBody& p_toConsider);
		void Unconsider(btRigidBody& p_toUnconsider);

		void ResetCollisionEvents();
		void CheckCollisionStopEvents();

		static bool CollisionCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2);
		void SetCollisionCallback();

	private:
		std::unique_ptr<btDynamicsWorld>			    m_world;
		std::unique_ptr<btDispatcher>				      m_dispatcher;
		std::unique_ptr<btCollisionConfiguration>	m_collisionConfig;
		std::unique_ptr<btBroadphaseInterface>		m_broadphase;
		std::unique_ptr<btConstraintSolver>			  m_solver;

		static std::map< std::pair<Entities::PhysicalObject*, Entities::PhysicalObject*>, bool> m_collisionEvents;
		std::vector<std::reference_wrapper<Entities::PhysicalObject>>							              m_physicalObjects;
	};
}
