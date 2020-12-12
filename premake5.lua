workspace "KineticEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "KineticEngine/vendor/GLFW/include"
IncludeDir["GLAD"] = "KineticEngine/vendor/GLAD/include"
IncludeDir["ImGui"] = "KineticEngine/vendor/imgui"
IncludeDir["glm"] = "KineticEngine/vendor/glm"

include "KineticEngine/vendor/GLFW"
include "KineticEngine/vendor/GLAD"
include "KineticEngine/vendor/imgui"

project "KineticEngine"
	location "KineticEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"


	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "kepch.h"
	pchsource "KineticEngine/src/kepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"KE_PLATFORM_WINDOWS",
			"KE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"KineticEngine/vendor/spdlog/include",
		"KineticEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"KineticEngine/vendor"
	}

	links {
		"KineticEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"KE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "KE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KE_DIST"
		runtime "Release"
		optimize "on"