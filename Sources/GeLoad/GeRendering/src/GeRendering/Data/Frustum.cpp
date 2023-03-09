#include <cmath>
#include <algorithm>

#include "GeRendering/Data/Frustum.h"

//视锥体前后左右上下边的枚举
enum FrustumSide
{
  RIGHT   = 0,		// 视锥体的右面
  LEFT    = 1,		// 视锥体的左面
  BOTTOM  = 2,		// 视锥体的下面
  TOP     = 3,		// 视锥体的上面
  BACK    = 4,		// 视锥体的后面
  FRONT   = 5		  // 视锥体的前面
};

//平面数据的枚举
enum PlaneData
{
  A = 0,				//平面的X值
  B = 1,				//平面的Y值
  C = 2,				//平面的Z值
  D = 3				  //平面到原点的距离
};

///////////////////////////////// 归一化平面 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	从给定的视锥体归一化平面
/////
///////////////////////////////// 归一化平面 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void NormalizePlane(float frustum[6][4], int side)
{
  //计算平面法线的大小
  //magnitude = sqrt(x`2+y`2+z`2) 此处(x = A
  float magnitude = (float)sqrt(
    frustum[side][A] * frustum[side][A] +
    frustum[side][B] * frustum[side][B] +
    frustum[side][C] * frustum[side][C]);

  //将平面的值除以它的大小
  frustum[side][A] /= magnitude;
  frustum[side][B] /= magnitude;
  frustum[side][C] /= magnitude;
  frustum[side][D] /= magnitude;
}


///////////////////////////////// 计算视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	从投影和模型视图中提取视锥体
/////
///////////////////////////////// 计算视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void GeRendering::Data::Frustum::CalculateFrustum(const GeMaths::FMatrix4& p_viewProjection)
{
  auto columnMajorViewProjection = GeMaths::FMatrix4::Transpose(p_viewProjection);
  float const* clip = columnMajorViewProjection.data;

  // 现在我们要获得视锥体的各个边. 我们通过上面收到的clip裁剪平面从中提取边
  // 提取视锥体的右边
  m_frustum[RIGHT][A] = clip[3]  - clip[0];
  m_frustum[RIGHT][B] = clip[7]  - clip[4];
  m_frustum[RIGHT][C] = clip[11] - clip[8];
  m_frustum[RIGHT][D] = clip[15] - clip[12];

  //获取视锥体左边的信息
  m_frustum[LEFT][A] = clip[3] + clip[0];
  m_frustum[LEFT][B] = clip[7] + clip[4];
  m_frustum[LEFT][C] = clip[11] + clip[8];
  m_frustum[LEFT][D] = clip[15] + clip[12];

  //获取视锥体的下面信息
  m_frustum[BOTTOM][A] = clip[3] + clip[1];
  m_frustum[BOTTOM][B] = clip[7] + clip[5];
  m_frustum[BOTTOM][C] = clip[11] + clip[9];
  m_frustum[BOTTOM][D] = clip[15] + clip[13];

  //获取视锥体上面的信息
  m_frustum[TOP][A] = clip[3] - clip[1];
  m_frustum[TOP][B] = clip[7] - clip[5];
  m_frustum[TOP][C] = clip[11] - clip[9];
  m_frustum[TOP][D] = clip[15] - clip[13];

  //获取视锥体上面的信息
  m_frustum[BACK][A] = clip[3] - clip[2];
  m_frustum[BACK][B] = clip[7] - clip[6];
  m_frustum[BACK][C] = clip[11] - clip[10];
  m_frustum[BACK][D] = clip[15] - clip[14];

  //获取视锥体上面的信息
  m_frustum[FRONT][A] = clip[3] + clip[2];
  m_frustum[FRONT][B] = clip[7] + clip[6];
  m_frustum[FRONT][C] = clip[11] + clip[10];
  m_frustum[FRONT][D] = clip[15] + clip[14];

  //得到了法线XYZ和到平面的距离之后，接下来进行法线和距离的归一化
  //归一化右边
  NormalizePlane(m_frustum, RIGHT);
  //归一化左边
  NormalizePlane(m_frustum, LEFT);
  //归一化下面
  NormalizePlane(m_frustum, BOTTOM);
  //归一化上面
  NormalizePlane(m_frustum, TOP);
  //归一化后面
  NormalizePlane(m_frustum, BACK);
  //归一化前面
  NormalizePlane(m_frustum, FRONT);
}

// 下面代码允许我们对视锥体内的信息进行检查
// 我们可以看到一个点、球、立方体等是否在视锥体内

///////////////////////////////// 点在视锥体内 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	确定一个点是否在视锥体内
/////
///////////////////////////////// 点在视锥体内 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool GeRendering::Data::Frustum::PointInFrustum(float x, float y, float z) const
{
  // 当点 (x, y, z) 在平面上时为真。
  // 当点不在平面上时，它要么是负数（点在平面后面），要么是正数（点在平面前面）。
  // 我们想检查该点是否在平面前面，所以我们要做的就是遍历每个点并确保平面方程在平截头体的每一侧都为正数。
  // 结果（无论是正数还是负数）是该点在平面前的距离。

  // 遍历视锥体的所有边
  for (int i = 0; i < 6; i++)
  {
    // 计算平面方程并检查该点是否在视锥体的一侧后面
    if (m_frustum[i][A] * x + m_frustum[i][B] * y + m_frustum[i][C] * z + m_frustum[i][D] <= 0)
    {
      // 点在一边后面，所以它不在视锥体中
      return false;
    }
  }

  //点在视锥体体内（在视锥体所有边的前面）
  return true;
}


///////////////////////////////// 判断球是否在视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	通过球的中心点和半径来确定球是否在视锥体内部
/////
///////////////////////////////// 判断球是否在视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool GeRendering::Data::Frustum::SphereInFrustum(float x, float y, float z, float radius) const
{
  //与上述判断点是否在视锥体内的判断方法相似，只要判断球上的点是否在视锥体内即可

  // 遍历视锥体的所有边
  for (int i = 0; i < 6; i++)
  {
    // 判断是否球心离平面的距离是否超过球的半径
    if (m_frustum[i][A] * x + m_frustum[i][B] * y + m_frustum[i][C] * z + m_frustum[i][D] <= -radius)
    {
      // 距离大于半径，因此球体位于视锥体之外
      return false;
    }
  }

  // 球在视锥体内
  return true;
}


///////////////////////////////// 立方体是否在视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	这通过它的中心和 1/2 的长度确定一个立方体是在我们的视锥体内，还是边缘
/////
///////////////////////////////// 立方体是否在视锥体 \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool GeRendering::Data::Frustum::CubeInFrustum(float x, float y, float z, float size) const
{
  // 我们得到了立方体的中心和一半的长度。 把它想象成一个半径。
  // 然后我们检查立方体中的每个点，看看它是否在平截头体内。
  // 如果在一侧前面发现一个点，那么我们跳到下一侧。
  // 如果我们到达一个前面没有点的平面，那么它将返回 false。

  for (int i = 0; i < 6; i++)
  {
    if (m_frustum[i][A] * (x - size) + m_frustum[i][B] * (y - size) + m_frustum[i][C] * (z - size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x + size) + m_frustum[i][B] * (y - size) + m_frustum[i][C] * (z - size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x - size) + m_frustum[i][B] * (y + size) + m_frustum[i][C] * (z - size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x + size) + m_frustum[i][B] * (y + size) + m_frustum[i][C] * (z - size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x - size) + m_frustum[i][B] * (y - size) + m_frustum[i][C] * (z + size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x + size) + m_frustum[i][B] * (y - size) + m_frustum[i][C] * (z + size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x - size) + m_frustum[i][B] * (y + size) + m_frustum[i][C] * (z + size) + m_frustum[i][D] > 0)
      continue;
    if (m_frustum[i][A] * (x + size) + m_frustum[i][B] * (y + size) + m_frustum[i][C] * (z + size) + m_frustum[i][D] > 0)
      continue;

    // 如果所有点都不在视锥体内，则返回false
    return false;
  }

  return true;
}

bool GeRendering::Data::Frustum::BoundingSphereInFrustum(const GeRendering::Geometry::BoundingSphere& p_boundingSphere, const GeMaths::FTransform& p_transform) const
{
  const auto& position = p_transform.GetWorldPosition();
  const auto& rotation = p_transform.GetWorldRotation();
  const auto& scale = p_transform.GetWorldScale();

  float maxScale = std::max(std::max(std::max(scale.x, scale.y), scale.z), 0.0f);
  float scaledRadius = p_boundingSphere.radius * maxScale;
  auto sphereOffset = GeMaths::FQuaternion::RotatePoint(p_boundingSphere.position, rotation) * maxScale;

  GeMaths::FVector3 worldCenter = position + sphereOffset;

  return SphereInFrustum(worldCenter.x, worldCenter.y, worldCenter.z, scaledRadius);
}

std::array<float, 4> GeRendering::Data::Frustum::GetNearPlane() const
{
  return { m_frustum[FRONT][0], m_frustum[FRONT][1], m_frustum[FRONT][2], m_frustum[FRONT][3] };
}

std::array<float, 4> GeRendering::Data::Frustum::GetFarPlane() const
{
  return { m_frustum[BACK][0], m_frustum[BACK][1], m_frustum[BACK][2], m_frustum[BACK][3] };
}
