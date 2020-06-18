#include "stdafx.h"
#include "TestAppDelegate.h"

#define MYAPPLICATION_NAME L"Test"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ParticleSystem::SetTexturesPath("textures/Particles");

	Core::fileSystem.SetWriteDirectory("./write_directory");
	
    std::string base_path = "base_p";
 
    Core::fileSystem.MountDirectory(base_path);

    Log::log.AddSink(new Log::DebugOutputLogSink());
	Log::log.AddSink(new Log::HtmlFileLogSink("log.htm", true));

	Core::Application::APPLICATION_NAME = MYAPPLICATION_NAME;
	Core::RunApplicationWithDelegate(new TestAppDelegate());

	return 0;
}
