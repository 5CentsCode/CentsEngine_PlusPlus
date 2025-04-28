#pragma once
class Application
{
    friend int WinMain();

public:

    Application();

protected:

    virtual void Init();
    virtual void Load();
    virtual void UnLoad();

    virtual void UpdateFrame();
    virtual void RenderFrame();

private:

    void Loop();
};

Application* CreateApplication();
#define CREATE_APPLICATION(T)		\
Application* CreateApplication()    \
{									\
	return new T();                 \
}