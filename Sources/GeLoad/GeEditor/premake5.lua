project "GeEditor"
	language "C++"
	cppdialect "C++17"
	files 
	{ 
		"**.h", "**.inl","**.cpp", "**.rc" 
	}
	includedirs 
	{ 
	"include", 
	dependdir .. "glfw/include", 
	dependdir .. "stb_image/include", 
	dependdir .. "lua/include", 
	dependdir .. "bullet3/include", 
	dependdir .. "glew/include", 
	dependdir .. "irrklang/include",
	"%{wks.location}/GeAnalytics/include", 
	"%{wks.location}/GeAudio/include", 
	"%{wks.location}/GeCore/include",
	"%{wks.location}/GeDebug/include", 
	"%{wks.location}/GeMaths/include", 
	"%{wks.location}/GePhysics/include",
	"%{wks.location}/GeRendering/include", 
	"%{wks.location}/GeUtils/include", 
	"%{wks.location}/GeUI/include", 
	"%{wks.location}/GeWindow/include" 
	}

	libdirs 
	{ 
		dependdir .. "glfw/lib", 
		dependdir .. "bullet3/lib/%{cfg.buildcfg}", 
		dependdir .. "lua/lib", 
		dependdir .. "glew/lib", 
		dependdir .. "irrklang/lib", 
		dependdir .. "assimp/lib" 
	}
	links 
	{ 
		"assimp-vc142-mt", 
		"zlibstatic", 
		"Bullet3Collision", 
		"Bullet3Common", 
		"Bullet3Dynamics", 
		"Bullet3Geometry", 
		"BulletCollision", 
		"BulletDynamics", 
		"BulletSoftBody", 
		"LinearMath", 
		"glew32", 
		"glfw3dll", 
		"irrKlang", 
		"liblua53", 
		"opengl32",
	 	"GeAnalytics", 	
		"GeAudio",
		"GeCore", 
		"GeDebug", 
		"GeMaths", 
		"GePhysics", 
		"GeRendering", 
		"GeUtils", 
		"GeUI", 
		"GeWindow", 
		"GeGame"
	}

	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	characterset ("MBCS")
	debugdir "%{wks.location}/../../Build/%{cfg.buildcfg}"

	postbuildcommands {
		"for /f \"delims=|\" %%i in ('dir /B /S \"%{wks.location}..\\..\\Dependencies\\*.dll\"') do xcopy /Q /Y \"%%i\" \"%{wks.location}..\\..\\Bin\\%{cfg.buildcfg}\\%{prj.name}\"",

		"xcopy \"%{wks.location}\\..\\..\\Resources\\Engine\\*\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Data\\Engine\" /y /i /r /e /q",
		"xcopy \"%{wks.location}\\..\\..\\Resources\\Editor\\*\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Data\\Editor\" /y /i /r /e /q",
		"xcopy \"%{prj.location}\\Layout.ini\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\Config\\\" /y /i",

		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Debug\\%{prj.name}\\*.exe\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Debug\\%{prj.name}\\*.dll\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Release\\%{prj.name}\\*.exe\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",
		"xcopy /Y /I /Q /D \"%{wks.location}\\..\\..\\Bin\\Release\\%{prj.name}\\*.dll\" \"%{wks.location}\\..\\..\\Build\\%{cfg.buildcfg}\\\"",

		"xcopy \"%{wks.location}..\\..\\Bin\\Debug\\GeGame\\*.exe\" \"%{wks.location}..\\..\\Build\\%{cfg.buildcfg}\\Builder\\Development\" /y /i /c",
		"xcopy \"%{wks.location}..\\..\\Bin\\Release\\GeGame\\*.exe\" \"%{wks.location}..\\..\\Build\\%{cfg.buildcfg}\\Builder\\Shipping\" /y /i /c",

		"EXIT /B 0"
	}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"
		kind "ConsoleApp"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
		kind "WindowedApp"
