#include "Window.h"
#include "Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window()
{
    if (glfwInit() == false)
    {
        printf("Failed to initialize GLAD");
        exit(-1);
    }

    glfwDefaultWindowHints();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    int32 width = 800;
    int32 height = 600;

    m_window = glfwCreateWindow(width, height, "Window", nullptr, nullptr);
    glfwSetWindowUserPointer(m_window, this);

    CenterOnMonitor(0);

    glfwSetWindowPosCallback(m_window, PositionCallback);
    glfwSetWindowSizeCallback(m_window, SizeCallback);
    glfwSetWindowMaximizeCallback(m_window, MaximizeCallback);
    glfwSetWindowIconifyCallback(m_window, MinimizeCallback);
    glfwSetWindowFocusCallback(m_window, FocusCallback);
    glfwSetDropCallback(m_window, DropCallback);

    // Set input callback events
    glfwSetKeyCallback(m_window, Input::KeyCallback);
    glfwSetCharCallback(m_window, Input::CharCallback);
    glfwSetMouseButtonCallback(m_window, Input::MouseButtonCallback);
    glfwSetCursorPosCallback(m_window, Input::MouseCursorPosCallback);
    glfwSetScrollCallback(m_window, Input::MouseScrollCallback);
    glfwSetCursorEnterCallback(m_window, Input::CursorEnterCallback);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        Close();
        glfwDestroyWindow(m_window);
        glfwTerminate();
        exit(-2);
    }

    glfwShowWindow(m_window);

    glViewport(0, 0, width, height);
}

Window::~Window()
{
    Close();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_window);
}

bool Window::ShouldClose() const
{
    bool shouldClose = glfwWindowShouldClose(m_window);
    return shouldClose;
}

bool Window::IsMinimized() const
{
    bool minimized = !IsMaximized();
    return minimized;
}

bool Window::IsMaximized() const
{
    bool maximized = glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) > 0;
    return maximized;
}

void Window::SetPosition(int32 x, int32 y)
{
    glfwSetWindowPos(m_window, x, y);
}

void Window::SetPosition(glm::ivec2 position)
{
    SetPosition(position.x, position.y);
}

void Window::SetWindowMonitor(uint8 monitor)
{
    int monitorCount = 0;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    if (monitor >= 0 && monitor <= monitorCount)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitor]);

        glfwSetWindowMonitor(m_window, monitors[monitor], 0, 0, mode->width, mode->height, mode->refreshRate);
    }
}

void Window::SetSize(int32 width, int32 height)
{
    glfwSetWindowSize(m_window, width, height);
    glViewport(0, 0, width, height);
}

void Window::SetSize(glm::ivec2 size)
{
    SetSize(size.x, size.y);
}

void Window::SetTitle(const char* title)
{
    glfwSetWindowTitle(m_window, title);
}

void Window::Close()
{
    glfwSetWindowShouldClose(m_window, true);
}

bool Window::IsFullScreen() const
{
    return glfwGetWindowMonitor(m_window) != NULL;
}

int Window::GetWidth() const
{
    return GetSize().x;
}

int Window::GetHeight() const
{
    return GetSize().y;
}

glm::ivec2 Window::GetSize() const
{
    glm::ivec2 size = glm::ivec2(0);
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}

glm::ivec2 Window::GetPosition() const
{
    glm::ivec2 position = glm::ivec2(0);
    glfwGetWindowPos(m_window, &position.x, &position.y);
    return position;
}

void Window::CenterOnMonitor(uint8 monitorId)
{
    int32 count;
    glm::ivec2 monitorPosition;
    glm::ivec2 windowSize = GetSize();

    GLFWmonitor** monitors = glfwGetMonitors(&count);
    GLFWmonitor* monitor = monitors[monitorId];

    glfwGetMonitorPos(monitor, &monitorPosition.x, &monitorPosition.y);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
    glm::ivec2 videoSize = glm::ivec2(videoMode->width, videoMode->height);

    glm::ivec2 position = monitorPosition + (videoSize - windowSize) / 2;
    SetPosition(position);
}

void Window::PositionCallback(GLFWwindow* glfwWindow, int32 x, int32 y)
{
    UNUSED_PARAM(x);
    UNUSED_PARAM(y);

    Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    glm::vec2 windowSize = window->GetSize();
    if (window != NULL)
    {
        if (window->IsFullScreen() == false)
        {
            // window->SetPosition(x, y);
        }
    }
}

void Window::SizeCallback(GLFWwindow* glfwWindow, int32 width, int32 height)
{
    Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    if (window != NULL)
    {
        if (window->IsFullScreen() == false)
        {
            glViewport(0, 0, width, height);
        }
    }
}

void Window::MaximizeCallback(GLFWwindow* glfwWindow, int32 maximized)
{
    // Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(maximized);
}

void Window::MinimizeCallback(GLFWwindow* glfwWindow, int32 minimized)
{
    // Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(minimized);
}

void Window::FocusCallback(GLFWwindow* glfwWindow, int32 focused)
{
    // Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(focused);
}

void Window::DropCallback(GLFWwindow* glfwWindow, int32 count, const char** paths)
{
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(count);
    UNUSED_PARAM(paths);
}
