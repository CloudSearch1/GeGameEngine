#pragma once

#include "GeCore/ECS/Components/AComponent.h"

#include <GeMaths/FTransform.h>
#include <GeMaths/FVector3.h>
#include <GeMaths/FQuaternion.h>

#include "AComponent.h"

namespace GeCore::ECS { class Actor; }

namespace GeCore::ECS::Components
{
  //表示应用于动作的 3D 变换
	class CTransform : public AComponent
	{
	public:
    //在不设置父级的情况下创建一个转换
		CTransform(ECS::Actor& p_owner, struct GeMaths::FVector3 p_localPosition = GeMaths::FVector3(0.0f, 0.0f, 0.0f), GeMaths::FQuaternion p_localRotation = GeMaths::FQuaternion::Identity, struct GeMaths::FVector3 p_localScale = GeMaths::FVector3(1.0f, 1.0f, 1.0f));

    //返回组件的名称
		std::string GetName() override;

    //定义转换的父对象
		void SetParent(CTransform& p_parent);

    //将父级设置为 nullptr 并重新计算世界矩阵
		bool RemoveParent();

    //检查转换是否有父级
		bool HasParent() const;

    //设置变换在局部空间的位置
		void SetLocalPosition(struct GeMaths::FVector3 p_newPosition);

    //设置变换在局部空间的旋转
		void SetLocalRotation(GeMaths::FQuaternion p_newRotation);

    //设置局部空间变换的比例
		void SetLocalScale(struct GeMaths::FVector3 p_newScale);


    //设置变换在世界空间中的位置
		void SetWorldPosition(struct GeMaths::FVector3 p_newPosition);

    //设置变换在世界空间中的旋转
		void SetWorldRotation(GeMaths::FQuaternion p_newRotation);

    //设置世界空间变换的比例
		void SetWorldScale(struct GeMaths::FVector3 p_newScale);

    //在本地空间转换
		void TranslateLocal(const struct GeMaths::FVector3& p_translation);

    //在局部空间旋转
		void RotateLocal(const GeMaths::FQuaternion& p_rotation);

    //在局部空间中缩放
		void ScaleLocal(const struct GeMaths::FVector3& p_scale);

    //返回局部空间的位置
		const GeMaths::FVector3& GetLocalPosition() const;

    //返回局部空间的旋转
		const GeMaths::FQuaternion& GetLocalRotation() const;

    //返回局部空间的比例
		const GeMaths::FVector3& GetLocalScale() const;

    //返回世界空间中的位置
		const GeMaths::FVector3& GetWorldPosition() const;

    //返回世界空间的旋转
		const GeMaths::FQuaternion& GetWorldRotation() const;

    //返回世界空间的比例
		const GeMaths::FVector3& GetWorldScale() const;

    //返回局部矩阵
		const GeMaths::FMatrix4& GetLocalMatrix() const;

    //返回世界矩阵
		const GeMaths::FMatrix4& GetWorldMatrix() const;

    //返回附加到 CTransform 的 FTransform
		GeMaths::FTransform& GetFTransform();

    //使变革世界向前回归
		GeMaths::FVector3 GetWorldForward() const;

    //返回变换世界
		GeMaths::FVector3 GetWorldUp() const;

    //归还变换世界的权利
		GeMaths::FVector3 GetWorldRight() const;

    //返回局部前向变换
		GeMaths::FVector3 GetLocalForward() const;

    //返回局部向上的变换
		GeMaths::FVector3 GetLocalUp() const;

    //返回变换局部权
		GeMaths::FVector3 GetLocalRight() const;

		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

    //定义组件在检查器中的绘制方式
		virtual void OnInspector(GeUI::Internal::WidgetContainer& p_root) override;

	private:
		GeMaths::FTransform m_transform;
	};
}
