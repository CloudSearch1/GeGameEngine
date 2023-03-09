#pragma once

#include <functional>


namespace GeMaths::Internal
{
  //TransformNotifier 是一个简单的通知系统，由 transform 用来向他的孩子发送通知
	class TransformNotifier
	{
	public:

    //转换可以发送的通知
		enum class ENotification
		{
			TRANSFORM_CHANGED,
			TRANSFORM_DESTROYED
		};
    
    //NotificationHandler 是一个函数回调，在参数中接受一个 ENotification
		using NotificationHandler = std::function<void(ENotification)>;
    
    //NotificationHandler 的 ID
		using NotificationHandlerID = uint64_t;
    
    //将 NotificationHandler 添加到通知程序。 NotificationHandler 将接收此通知程序发送的所有通知。
    //此方法还返回稍后删除处理程序所需的 NotificationHandlerID
		NotificationHandlerID AddNotificationHandler(NotificationHandler p_notificationHandler);

    //通过发送给定的通知通知孩子（NotificationHandler）
		void NotifyChildren(ENotification p_notification);

    //使用生成的 NotificationHandlerID 删除通知程序的 NotificationHandler
		bool RemoveNotificationHandler(const NotificationHandlerID& p_notificationHandlerID);

	private:
		std::unordered_map<NotificationHandlerID, NotificationHandler> m_notificationHandlers;
		NotificationHandlerID m_availableHandlerID = 0;
	};
}
