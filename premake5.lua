workspace "Enigma"
	architecture "x86_64"
	startproject "Sandbox"
	configurations{"Debug", "Release", "Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Enigma/vendor/GLFW/include"
IncludeDir["Glad"] = "Enigma/vendor/Glad/include"
IncludeDir["ImGui"] = "Enigma/vendor/ImGui"
IncludeDir["glm"] = "Enigma/vendor/glm"
IncludeDir["stb_image"] = "Enigma/vendor/stb_image"

group "Dependencies"
	include "Enigma/vendor/GLFW"
	include "Enigma/vendor/Glad"
	include "Enigma/vendor/ImGui"

group ""

project "Enigma"
	location "Enigma"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "engmpch.h"
	pchsource "Enigma/src/engmpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/*.hpp",
		"%{prj.name}/vendor/glm/glm/*.inl",
		"%{prj.name}/vendor/sdb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ENGM_BUILD_DLL",
			"ENGM_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ENGM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ENGM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ENGM_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Enigma/vendor/spdlog/include",
		"Enigma/src",
		"Enigma/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Enigma"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"ENGM_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ENGM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ENGM_DIST"
		runtime "Release"
		optimize "on"

