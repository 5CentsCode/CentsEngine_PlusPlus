#include "Application.h"
#include "Common.h"
#include <windows.h>
#include <filesystem>
#include "DebugConsole.h"

int main()
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

    DebugConsole::CreateNewConsole(1024);
#endif // _DEBUG

    Application* app = CreateApplication();
    app->Init();
    app->Load();
    app->Loop();
    app->UnLoad();

    delete app;

#ifdef _DEBUG
    DebugConsole::ReleaseConsole();
#endif // _DEBUG
}

#ifdef WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    UNUSED_PARAM(hInstance);
    UNUSED_PARAM(hPrevInstance);
    UNUSED_PARAM(lpCmdLine);
    UNUSED_PARAM(nShowCmd);

    main();
}
#endif