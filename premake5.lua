workspace "Enigma"
	architecture "x64"
	configurations{"Debug", "Release", "Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Enigma/vendor/GLFW/include"

include "Enigma/vendor/GLFW"

project "Enigma"
	location "Enigma"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "engmpch.h"
	pchsource "Enigma/src/engmpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"		
	}

	links{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ENGM_BUILD_DLL",
			"ENGM_PLATFORM_WINDOWS"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
		}

	filter "configurations:Debug"
		defines "ENGM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGM_DIST"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Enigma/vendor/spdlog/include",
		"Enigma/src"
	}

	links {
		"Enigma"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"ENGM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGM_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ENGM_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGM_DIST"
		optimize "On"
	
