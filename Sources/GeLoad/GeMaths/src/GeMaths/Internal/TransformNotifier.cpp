#include "GeMaths/Internal/TransformNotifier.h"

GeMaths::Internal::TransformNotifier::NotificationHandlerID GeMaths::Internal::TransformNotifier::AddNotificationHandler(NotificationHandler p_notificationHandler)
{
	NotificationHandlerID handlerID = m_availableHandlerID++;
	m_notificationHandlers.emplace(handlerID, p_notificationHandler);
	return handlerID;
}

void GeMaths::Internal::TransformNotifier::NotifyChildren(ENotification p_notification)
{
	if (!m_notificationHandlers.empty())
		for (auto const&[id, handler] : m_notificationHandlers)
			handler(p_notification);
}

bool GeMaths::Internal::TransformNotifier::RemoveNotificationHandler(const NotificationHandlerID& p_notificationHandlerID)
{
	return m_notificationHandlers.erase(p_notificationHandlerID) != 0;
}
