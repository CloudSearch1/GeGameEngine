#pragma once

#include <string>
#include <chrono>


namespace GeUtils::Time
{
  //计算时间
	class Clock
	{
	public:
    //更新时钟
		void Update();

    //返回实际帧率（取决于delta时间）
		float GetFramerate();

    //返回实际增量时间（应用比例）
		float GetDeltaTime();

    //返回实际增量时间（未应用比例）
		float GetDeltaTimeUnscaled();

    //返回自时钟创建以来经过的时间
		float GetTimeSinceStart();

    //返回当前时间刻度
		float GetTimeScale();

    //将时间尺度乘以给定的系数
		void Scale(float p_coeff);

    //定义时间尺度
		void SetTimeScale(float p_timeScale);

	private:
		void Initialize();

		std::chrono::steady_clock::time_point	__START_TIME;
		std::chrono::steady_clock::time_point	__LAST_TIME;
		std::chrono::steady_clock::time_point	__CURRENT_TIME;
		std::chrono::duration<double>			    __ELAPSED;

		bool	__INITIALIZED = false;
		float	__TIME_SCALE = 1.0f;
		float	__DELTA_TIME = 0.0f;
		float	__TIME_SINCE_START = 0.0f;
	};
}
