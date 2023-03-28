#pragma once

#include <GeUtils/Filesystem/tinyxml2.h>


#include "GeCore/Helpers/Serializer.h"

namespace GeCore::API
{
  //ISerializable 是任何可以序列化的类的接口
	class ISerializable
	{
	public:
    //序列化请求时调用
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;

    //反序列化请求时调用
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) = 0;

    //默认多态析构函数
		virtual ~ISerializable() = default;
	};
}
