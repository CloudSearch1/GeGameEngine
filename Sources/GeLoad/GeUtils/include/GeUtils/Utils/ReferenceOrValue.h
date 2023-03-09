#pragma once

#include <variant>

namespace GeUtils::Utils
{
  //可以表示给定类型的引用或值的类
	template <typename T>
	class ReferenceOrValue
	{
	public:
    //使用引用构造 ReferenceOrValue 实例
		ReferenceOrValue(std::reference_wrapper<T> p_reference)
      : m_data{ &p_reference.get() }
		{
		}

    //用一个值构造 ReferenceOrValue 实例
		ReferenceOrValue(T p_value = T()) : m_data{ p_value }
		{
		}

    //使 ReferenceOrValue 成为引用
		void MakeReference(T& p_reference)
		{
			m_data = &p_reference;
		}

    //使 ReferenceOrValue 成为一个值
		void MakeValue(T p_value = T())
		{
			m_data = p_value;
		}

    //将 ReferenceOrValue 隐式转换为 T
		operator T&()
		{
			return Get();
		}
    
    //调用 ReferenceOrValue 实例的 setter 的赋值运算符
		ReferenceOrValue<T>& operator=(T p_value)
		{
			Set(p_value);
			return *this;
		}

    //返回值（来自引用或直接来自值）
		T& Get() const
		{
			if (auto pval = std::get_if<T>(&m_data))
				return *pval;
			else
				return *std::get<T*>(m_data);
		}

    //设置值（到引用或直接到值）
		void Set(T p_value)
		{
			if (auto pval = std::get_if<T>(&m_data))
				* pval = p_value;
			else
				*std::get<T*>(m_data) = p_value;
		}

	private:
		std::variant<T, T*> m_data;
	};
}
