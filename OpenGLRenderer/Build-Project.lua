project "OpenGLRenderer"
    kind "ConsoleApp"
    cppdialect "C++11"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    targetdir ("%{wks.location}/Binaries/" .. outputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. outputDir .. "/%{prj.name}")

    -- pchheader "pch.h"
    -- pchsource "Source/pch.cpp"

    defines
    {
        "GLEW_STATIC",
        "GLFW_INCLUDE_NONE",
    }

    files
    {
        "Source/**.h",
        "Source/**.cpp",
    }

    includedirs
    {
        "Source",
        "Vendor/GLFW/include",
        "Vendor/GLEW/include",
    }

    libdirs
    {
        "Vendor/GLFW/lib-vc2022",
        "Vendor/GLEW/lib/Release/x64",
    }

    links
    {
        "opengl32.lib",
        "glfw3.lib",
        "glew32s.lib",
    }

    filter "system:windows"
        systemversion "latest"
        defines { "PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "CONFIGURATION_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Development"
        defines { "CONFIGURATION_DEVELOPMENT" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Release"
        defines { "CONFIGURATION_RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"