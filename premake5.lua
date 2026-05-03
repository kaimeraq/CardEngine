-- Premake script for Engine static library module.
workspace "Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Development",
		"Shipping"
	}

outputos = "%{iif(cfg.system == 'windows', 'Win', cfg.system)}"
outputarch = "%{iif(cfg.architecture == 'x86_64', '64', cfg.architecture)}"
outputdir = "%{cfg.buildcfg}-" .. outputos .. outputarch

project "Engine"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir)
	objdir	  ("int/" .. outputdir)

	pchheader "pch.h"
	pchsource "src/pch.cpp"
	forceincludes { "pch.h" }

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src"
	}

	filter "system:windows"
		cppdialect "C++23"
		staticruntime "On"
		systemversion "latest"
		characterset "Unicode"
        warnings "Extra"

		defines
		{
			"PLATFORM_WINDOWS",
			"NOMINMAX",
			"WIN32_LEAN_AND_MEAN"
		}
		
		buildoptions
		{
			"/Zc:__cplusplus", 
			"/permissive-", 
			"/sdl" 
		}

	filter "configurations:Debug"
		defines 
		{
			"CE_DEBUG",
			"_DEBUG"
		}

		symbols "On"
		optimize "Off"
		runtime "Debug"

	filter "configurations:Development"
		defines 
		{
			"CE_DEVEL",
			"NDEBUG"
		}

		symbols "On"
		editandcontinue "Off"
		optimize "Debug"
		linktimeoptimization "Fast"
		runtime "Release"

	filter "configurations:Shipping"
		defines 
		{
			"CE_SHIPPING",
			"NDEBUG"
		}

		symbols "On"
		optimize "Full"
		linktimeoptimization "On"
		runtime "Release"

	filter {}