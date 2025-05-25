#pragma once
#include <vector>
#include "Common.h"
#include "Window.h"

class Application
{
    friend int main();

public:
    Application();

protected:
    virtual void Init();
    virtual void Load();
    virtual void Unload();

    virtual void UpdateFrame(float deltaTime);
    virtual void RenderFrame(float deltaTime);

private:
    void Loop();

protected:
    Window* m_window;
};

Application* CreateApplication();
#define CREATE_APPLICATION(T)		\
Application* CreateApplication()    \
{									\
	return new T();                 \
}