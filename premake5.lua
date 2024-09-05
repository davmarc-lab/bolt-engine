workspace("Bolt")
architecture("x64")

configurations({
	"Debug",
	"Release",
})

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project("Bolt")
location("Bolt")
kind("SharedLib")
language("C++")
cppdialect("C++17")

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
	"%{prj.name}/dependencies/glad/**.c",
	"%{prj.name}/dependencies/glm/**.iml",
	"%{prj.name}/dependencies/imgui/**.cpp",
})

includedirs({
	"%{prj.name}/dependencies/spdlog/include",
	"%{prj.name}/dependencies/glad/include",
	"%{prj.name}/dependencies/imgui",
	"%{prj.name}/dependencies/glm",
})

links({ "glm", "GL", "glfw", "X11", "Xrandr", "Xi", "dl" })

defines({
	"BT_BUILD_DLL",
	"BT_ENABLE_DEBUG",
})

postbuildcommands({
	("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Platform"),
})

project("Platform")
location("Platform")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")

targetdir("bin/" .. outputDir .. "/%{prj.name}")
objdir("bin-int/" .. outputDir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.hpp",
	"%{prj.name}/src/**.cpp",
})

includedirs({
	"Bolt/dependencies/include/spdlog",
	"Bolt/src",
})

links({
	"Bolt",
})
