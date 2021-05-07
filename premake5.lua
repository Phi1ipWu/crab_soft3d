-- premake5.lua
workspace "crab_soft3d"
   configurations { "Debug", "Release" }

project "crab_soft3d"
   kind "WindowedApp"
   language "C"
   targetdir "bin/%{cfg.buildcfg}"

   files { "**.h", "**.c" }

   filter "configurations:Debug"
      defines { "WIN32", "_DEBUG", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
      symbols "On"

   filter "configurations:Release"
      defines { "WIN32", "NDEBUG", "_WINDOWS", "_CRT_SECURE_NO_WARNINGS" }
      optimize "On"
