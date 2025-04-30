#include "Application.h"

int main()
{
    Application* app = CreateApplication();
    app->Init();
    app->Load();
    app->Loop();
    app->UnLoad();
}

#ifdef WIN32
int WinMain()
{
    main();
}
#endif