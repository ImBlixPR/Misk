workspace "Misk"
	
	architecture "x64"
	startproject "SandBox"


	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

IncludeDir = {}
IncludeDir["GLFW"] = "Misk/vendor/GLFW/include"
IncludeDir["Glad"] = "Misk/vendor/Glad/include"
IncludeDir["imgui"] = "Misk/vendor/imgui"
IncludeDir["glm"] = "Misk/vendor/glm"

include "Misk/vendor/GLFW"
include "Misk/vendor/Glad"
include "Misk/vendor/imgui"

project "Misk"
	
	location "Misk"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mkpch.h"
	pchsource "Misk/src/mkpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS",
			"MK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"MK_ENABLE_ASSERTS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/SandBox/\"")
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		buildoptions "/MD"
		optimize "On"


project "SandBox"
	
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Misk/vendor/spdlog/include",
		"Misk/src",
		"Misk/vendor/imgui",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Misk",
		"imgui"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS",
			"MK_ENABLE_ASSERTS"
		}


	filter "configurations:Debug"
		defines "MK_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		buildoptions "/MD"
		optimize "On"
