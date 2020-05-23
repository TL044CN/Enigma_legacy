workspace "Enigma"
	architecture "x64"
	configurations{"Debug", "Release", "Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Enigma/vendor/GLFW/include"
IncludeDir["Glad"] = "Enigma/vendor/Glad/include"
IncludeDir["ImGui"] = "Enigma/vendor/ImGui"

include "Enigma/vendor/GLFW"
include "Enigma/vendor/Glad"
include "Enigma/vendor/ImGui"

project "Enigma"
	location "Enigma"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
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

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/"..outputdir.."/Sandbox")
		}

	filter "configurations:Debug"
		defines "ENGM_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "ENGM_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "ENGM_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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

