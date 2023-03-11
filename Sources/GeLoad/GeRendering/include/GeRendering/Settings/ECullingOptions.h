#pragma once



namespace GeRendering::Settings
{
  //一些剔除选项
	enum class ECullingOptions
	{
		NONE				      = 0x0,
		FRUSTUM_PER_MODEL	= 0x1,
		FRUSTUM_PER_MESH	= 0x2
	};

	ECullingOptions operator~ (ECullingOptions a)                        { return (ECullingOptions)~(int)a; }
	ECullingOptions operator| (ECullingOptions a, ECullingOptions b)     { return (ECullingOptions)((int)a | (int)b); }
	ECullingOptions operator& (ECullingOptions a, ECullingOptions b)     { return (ECullingOptions)((int)a & (int)b); }
	ECullingOptions operator^ (ECullingOptions a, ECullingOptions b)     { return (ECullingOptions)((int)a ^ (int)b); }
	ECullingOptions& operator|= (ECullingOptions& a, ECullingOptions b)  { return (ECullingOptions&)((int&)a |= (int)b); }
	ECullingOptions& operator&= (ECullingOptions& a, ECullingOptions b)  { return (ECullingOptions&)((int&)a &= (int)b); }
	ECullingOptions& operator^= (ECullingOptions& a, ECullingOptions b)  { return (ECullingOptions&)((int&)a ^= (int)b); }
	bool IsFlagSet(ECullingOptions p_flag, ECullingOptions p_mask)       { return (int)p_flag & (int)p_mask; }
}
