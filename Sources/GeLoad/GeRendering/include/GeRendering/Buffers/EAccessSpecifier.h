#pragma once

namespace GeRendering::Buffers
{
  //定义缓冲区能够访问的规范
	enum class EAccessSpecifier
	{
		STREAM_DRAW		= 0x88E0,
		STREAM_READ		= 0x88E1,
		STREAM_COPY		= 0x88E2,

		DYNAMIC_DRAW	= 0x88E8,
		DYNAMIC_READ	= 0x88E9,
		DYNAMIC_COPY	= 0x88EA,

		STATIC_DRAW		= 0x88E4,
		STATIC_READ		= 0x88E5,
		STATIC_COPY		= 0x88E6
	};

  /*
    STREAM
    The data store contents will be modified once and used at most a few times.
    STATIC
    The data store contents will be modified once and used many times.
    DYNAMIC
    The data store contents will be modified repeatedly and used many times.
    
    The nature of access may be one of these:
    DRAW
    The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
    READ
    The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
    COPY
    The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
  */
}
