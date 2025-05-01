#include "Application.h"
#include <windows.h>
#include <filesystem>
#include "DebugConsole.h"

int main()
{
#ifdef _DEBUG
    DebugConsole::CreateNewConsole(1024);
#endif // _DEBUG

    std::filesystem::path cwd = std::filesystem::current_path();
    printf("%s\n", cwd.string().c_str());

    Application* app = CreateApplication();
    app->Init();
    app->Load();
    app->Loop();
    app->UnLoad();

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