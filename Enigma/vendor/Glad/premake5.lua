project "Glad"
	kind "StaticLib"
	language "C"
	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files {
		"include/glad/glad.h",
		"src/glad.c",
		"include/KHR/khrplatform.h"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	filter { "system:windows", "configurations:Dist" }
		buildoptions "/MT"

