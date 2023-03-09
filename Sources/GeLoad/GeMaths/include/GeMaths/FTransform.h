#pragma once

#include "GeMaths/Internal/TransformNotifier.h"
#include "GeMaths/FQuaternion.h"
#include "GeMaths/FMatrix4.h"
#include "GeMaths/FVector3.h"

namespace GeMaths
{
  //具有浮点精度的 3D 变换的数学表示
	class FTransform
	{
	public:
    //在不设置父级的情况下创建一个转换
		FTransform(FVector3 p_localPosition = FVector3(0.0f, 0.0f, 0.0f), FQuaternion p_localRotation = FQuaternion::Identity, FVector3 p_localScale = FVector3(1.0f, 1.0f, 1.0f));

    //变换的析构函数。
		~FTransform();

    //处理父通知的简单回调
		void NotificationHandler(Internal::TransformNotifier::ENotification p_notification);

    //定义转换的父级
		void SetParent(FTransform& p_parent);

    //将父级设置为 nullptr 并重新计算世界矩阵
		bool RemoveParent();

    //检查转换是否有父级
		bool HasParent() const;

    //使用原始数据初始化转换
		void GenerateMatrices(FVector3 p_position, FQuaternion p_rotation, FVector3 p_scale);

    //重新更新世界矩阵以使用父变换
		void UpdateWorldMatrix();

    //设置变换在局部空间的位置
		void SetLocalPosition(FVector3 p_newPosition);

    //设置变换在局部空间的旋转
		void SetLocalRotation(FQuaternion p_newRotation);

    //设置局部空间变换的比例
		void SetLocalScale(FVector3 p_newScale);

    //设置变换在世界空间中的位置
		void SetWorldPosition(FVector3 p_newPosition);

    //设置变换在世界空间中的旋转
		void SetWorldRotation(FQuaternion p_newRotation);

    //设置世界空间变换的比例
		void SetWorldScale(FVector3 p_newScale);

    //在本地空间翻译
		void TranslateLocal(const FVector3& p_translation);

    //在局部空间旋转
		void RotateLocal(const FQuaternion& p_rotation);

    //在局部空间中缩放
		void ScaleLocal(const FVector3& p_scale);

    //返回局部空间的位置
		const FVector3& GetLocalPosition() const;

    //返回局部空间的旋转
		const FQuaternion& GetLocalRotation() const;

    //返回局部空间的比例
		const FVector3& GetLocalScale() const;

    //返回世界空间中的位置
		const FVector3& GetWorldPosition() const;

    //返回世界空间的旋转
		const FQuaternion& GetWorldRotation() const;

    //返回世界空间的比例
		const FVector3& GetWorldScale() const;

    //返回局部矩阵
		const FMatrix4& GetLocalMatrix() const;

    //返回世界矩阵
		const FMatrix4& GetWorldMatrix() const;

    //使变革世界向前回归
		FVector3 GetWorldForward() const;

    //返回变换世界
		FVector3 GetWorldUp() const;

    //归还变换世界的权利
		FVector3 GetWorldRight() const;

    //返回局部前向变换
		FVector3 GetLocalForward() const;

    //返回局部向上的变换
		FVector3 GetLocalUp() const;

    //返回变换局部权
		FVector3 GetLocalRight() const;

	public:
		Internal::TransformNotifier Notifier;
		Internal::TransformNotifier::NotificationHandlerID m_notificationHandlerID;

	private:
		void PreDecomposeWorldMatrix();
		void PreDecomposeLocalMatrix();

    //预分解数据，防止多次分解
		FVector3 m_localPosition;
		FQuaternion m_localRotation;
		FVector3 m_localScale;
		FVector3 m_worldPosition;
		FQuaternion m_worldRotation;
		FVector3 m_worldScale;

		FMatrix4 m_localMatrix;
		FMatrix4 m_worldMatrix;

		FTransform*	m_parent;
	};
}
