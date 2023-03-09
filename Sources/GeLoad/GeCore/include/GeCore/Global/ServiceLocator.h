#pragma once

#include <any>
#include <unordered_map>



#define OVSERVICE(Type) GeCore::Global::ServiceLocator::Get<Type>()

namespace GeCore::Global
{
  //提供访问核心服务的途径
	class ServiceLocator
	{
	public:
    //在服务定位器中注册一个服务
		template<typename T>
		static void Provide(T& p_service)
		{
			__SERVICES[typeid(T).hash_code()] = std::any(&p_service);
		}
		
    //返回给定类型的服务（确保您在调用此方法之前提供了服务）
		template<typename T>
		static T& Get()
		{
			return *std::any_cast<T*>(__SERVICES[typeid(T).hash_code()]);
		}

	private:
		static std::unordered_map<size_t, std::any> __SERVICES;
	};
}
