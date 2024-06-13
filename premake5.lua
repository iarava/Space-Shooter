workspace "SpaceShooter"
    architecture "x86_64"
    configurations { "Debug", "Release" }
    startproject "SpaceShooter"

-- Platforms
platforms { "x86", "x64" }

-- Output directories
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- directories
projectdir = "./SpaceShooter/"
dependenciesdir = projectdir .. "vendor/"

project "SpaceShooter"
    location "SpaceShooter"
    kind "ConsoleApp"
    language "C++"
    characterset "MBCS"
    targetname "SpaceShooter"
    targetdir ("%{prj.location}/builds/" .. outputdir)
    objdir ("%{prj.location}/builds/" .. outputdir)

    conformancemode "yes"

    files { 
        "%{prj.location}/src/**.hpp", 
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/src/Data/**.bmp" 
    }
    externalincludedirs { "%{prj.location}/vendor/SDL2/include" }

    filter "system:windows"
        systemversion "10.0.17134.0"
        staticruntime "Off"  -- Use dynamic runtime linking

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"

    filter "platforms:x86"
        architecture "x86"        
        debugenvs { "PATH=%PATH%", "%{prj.location}/vendor/SDL2/lib/x86" }
        libdirs { "%{prj.location}/vendor/SDL2/lib/x86" }
        syslibdirs { "%{prj.location}/vendor/SDL2/lib/x86" }
        links { "SDL2", "SDL2main" }

    filter "platforms:x64"
        architecture "x86_64"
        debugenvs { "PATH=%PATH%", "%{prj.location}/vendor/SDL2/lib/x64" }
        libdirs { "%{prj.location}/vendor/SDL2/lib/x64" }
        syslibdirs { "%{prj.location}/vendor/SDL2/lib/x64" }
        links { "SDL2", "SDL2main" }

    -- Post-build commands to copy SDL2 DLLs
    filter { "platforms:x86", "configurations:Debug" }
        postbuildcommands {
            '{COPY} "%{wks.location}/SpaceShooter/vendor/SDL2/lib/x86/SDL2.dll" "%{cfg.targetdir}"',
            '{COPY} "%{prj.location}/src/Data/*.bmp" "%{cfg.targetdir}/Data"'
        }

    filter { "platforms:x86", "configurations:Release" }
        postbuildcommands {
            '{COPY} "%{wks.location}/SpaceShooter/vendor/SDL2/lib/x86/SDL2.dll" "%{cfg.targetdir}"',
            '{COPY} "%{prj.location}/src/Data/*.bmp" "%{cfg.targetdir}/Data"'
        }

    filter { "platforms:x64", "configurations:Debug" }
        postbuildcommands {
            '{COPY} "%{wks.location}/SpaceShooter/vendor/SDL2/lib/x64/SDL2.dll" "%{cfg.targetdir}"',
            '{COPY} "%{prj.location}/src/Data/*.bmp" "%{cfg.targetdir}/Data"'
        }

    filter { "platforms:x64", "configurations:Release" }
        postbuildcommands {
            '{COPY} "%{wks.location}/SpaceShooter/vendor/SDL2/lib/x64/SDL2.dll" "%{cfg.targetdir}"',
            '{COPY} "%{prj.location}/src/Data/*.bmp" "%{cfg.targetdir}/Data"'
        }
