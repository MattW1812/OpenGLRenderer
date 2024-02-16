workspace "OpenGLRenderer"
   architecture "x64"
   configurations { "Debug", "Development", "Release" }
   startproject "OpenGLRenderer"

outputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "OpenGLRenderer/Build-Project.lua"