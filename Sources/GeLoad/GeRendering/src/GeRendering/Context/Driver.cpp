#include <GL/glew.h>

#include <string>

#include "GeRendering/Context/Driver.h"

GeRendering::Context::Driver::Driver(const Settings::DriverSettings& p_driverSettings)
{
	InitGlew();
	
	m_isActive = true;

	if (p_driverSettings.debugMode)
	{
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_BACK);
}

bool GeRendering::Context::Driver::IsActive() const
{
	return m_isActive;
}


void GeRendering::Context::Driver::InitGlew()
{
	const GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::string message = "Error Init GLEW: ";
		std::string glewError = reinterpret_cast<const char*>(glewGetErrorString(error));
    //to do -> add a Log out !
	}
}
