project "GeCore"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	files 
	{
		"**.h", "**.inl", "**.cpp" 
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
	
		"%{wks.location}/GeDebug/include", 
		"%{wks.location}/GeAnalytics/include", 
		"%{wks.location}/GeAudio/include",
		"%{wks.location}/GeMaths/include", 
		"%{wks.location}/GePhysics/include",
	
		"%{wks.location}/GeRendering/include", 
		"%{wks.location}/GeUtils/include", 
		"%{wks.location}/GeUI/include", 
		"%{wks.location}/GeWindow/include" 
	}

	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	characterset ("MBCS")
	
	buildoptions { "/bigobj" }

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
