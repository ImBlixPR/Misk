workspace "Misk"
	
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "Misk"
	
	location "Misk"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin/" .. outputdir .. "/%{prj.name}")

	pchheader "mkpch.h"
	pchsource "Misk/src/mkpch.cpp"


	files
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOW",
			"MK_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		optimize "On"

		project "Misk"
	
	location "Misk"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}


	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOWS",
			"MK_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}

	filter "configurations:Debug"
		defines "MK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
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
		"Misk/src"
	}

	links
	{
		"Misk"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MK_PLATFORM_WINDOW"
		}


	filter "configurations:Debug"
		defines "MK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MK_DIST"
		optimize "On"
