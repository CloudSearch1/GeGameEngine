workspace "GeEngine"
	configurations 
	{ 
		"Debug", "Release" 
	}
	platforms 
	{ 
		"x64" 
	}
	startproject "GeEditor"

outputdir = "%{wks.location}/../../Bin/"
objoutdir = "%{wks.location}/../../Bin-Int/"
dependdir = "%{wks.location}/../../Dependencies/"

include "GeAudio"
include "GeCore"
include "GeDebug"
include "GeAnalytics"
include "GeMaths"
include "GePhysics"
include "GeRendering"
include "GeUtils"
include "GeUI"
include "GeWindow"
include "GeEditor"
include "GeGame"