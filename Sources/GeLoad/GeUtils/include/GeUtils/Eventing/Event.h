#pragma once

#include <functional>


namespace GeUtils::Eventing
{
  //监听器ID
	using ListenerID = uint64_t;

  //包含一组函数回调的简单事件。这些函数将在调用时被调用
	template<class... ArgTypes>
	class Event
	{
	public:
    //没有返回值的通用函数的简单快捷方式
		using Callback = std::function<void(ArgTypes...)>;

    //为这个事件添加一个函数回调,同时返回新监听器的ID
		ListenerID AddListener(Callback p_callback);

    //为这个事件添加一个函数回调,同时返回新监听器的ID
		ListenerID operator+=(Callback p_callback);

    //使用监听器移除对此事件的函数回调，调用 AddListener 时创建
		bool RemoveListener(ListenerID p_listenerID);

		//使用监听器删除对此事件的函数回调（调用 AddListener 时创建）
		bool operator-=(ListenerID p_listenerID);
    
    //移除此事件的所有监听器
		void RemoveAllListeners();

    //返回注册的回调数
		uint64_t GetListenerCount();

    //调用附加到此事件的每个回调
		void Invoke(ArgTypes... p_args);

	private:
		std::unordered_map<ListenerID, Callback> m_callbacks;
		ListenerID m_availableListenerID = 0;
	};
}

#include "GeUtils/Eventing/Event.inl"
