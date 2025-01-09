-- premake5.lua
workspace "Renderer_Implementation"
   architecture "x86"
   configurations { "Debug", "Release", "Dist" }
   startproject "Display"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"



group "Renderer"
	include "Renderer/Build-Core.lua"
group "Display"
   include "Display/Build-App.lua"