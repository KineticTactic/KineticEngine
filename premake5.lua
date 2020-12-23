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
IncludeDir["stb_image"] = "KineticEngine/vendor/stb_image"
IncludeDir["entt"] = "KineticEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "KineticEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "KineticEngine/vendor/ImGuizmo"

group "Dependencies"
	include "KineticEngine/vendor/GLFW"
	include "KineticEngine/vendor/GLAD"
	include "KineticEngine/vendor/imgui"
	include "KineticEngine/vendor/yaml-cpp"

group ""

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
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp",
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

	filter "files:KineticEngine/vendor/ImGuizmo/ImGuizmo.cpp"
	flags { "NoPCH" }

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
		"KineticEngine/vendor",
		"%{IncludeDir.entt}"
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


project "Editor"
	location "Editor"
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
		"KineticEngine/vendor",
		"%{IncludeDir.entt}",
		"KineticEngine/vendor/ImGuizmo"
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