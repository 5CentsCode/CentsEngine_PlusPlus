#include "Application.h"

int WinMain()
{
    Application* app = CreateApplication();
    app->Init();
    app->Load();
    app->Loop();
    app->UnLoad();
}