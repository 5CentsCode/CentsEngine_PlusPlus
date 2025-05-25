#include "Input.h"
#include <GLFW/glfw3.h>

Input::KeyboardState Input::Keyboard;
Input::MouseState Input::Mouse;

bool Input::IsKeyPressed(KeyCode key)
{
    return Keyboard.PreviousKeyState[(int32)key] == InputState::Release &&
        Keyboard.CurrentKeyState[(int32)key] != InputState::Release;
}

bool Input::IsKeyDown(KeyCode key)
{
    return Keyboard.CurrentKeyState[(int32)key] != InputState::Release;
}

bool Input::IsKeyReleased(KeyCode key)
{
    return Keyboard.PreviousKeyState[(int32)key] != InputState::Release &&
        Keyboard.CurrentKeyState[(int32)key] == InputState::Release;
}

bool Input::IsKeyUp(KeyCode key)
{
    return Keyboard.CurrentKeyState[(int32)key] == InputState::Release;
}

KeyCode Input::GetKeyPressed(void)
{
    KeyCode key = Keyboard.KeyPressQueue.front();
    Keyboard.KeyPressQueue.pop();
    return key;
}

KeyCode Input::GetCharPressed(void)
{
    KeyCode key = Keyboard.CharPressQueue.front();
    Keyboard.CharPressQueue.pop();
    return key;
}

bool Input::IsMouseButtonPressed(MouseCode button)
{
    return Mouse.CurrentButtonState[(int)button] != InputState::Release &&
        Mouse.PreviousButtonState[(int)button] == InputState::Release;
}

bool Input::IsMouseButtonDown(MouseCode button)
{
    return Mouse.CurrentButtonState[(int)button] != InputState::Release;
}

bool Input::IsMouseButtonReleased(MouseCode button)
{
    return Mouse.CurrentButtonState[(int)button] == InputState::Release &&
        Mouse.PreviousButtonState[(int)button] != InputState::Release;
}

bool Input::IsMouseButtonUp(MouseCode button)
{
    return Mouse.CurrentButtonState[(int)button] == InputState::Release;;
}

glm::vec2 Input::GetMousePosition(void)
{
    return Mouse.CurrentPosition;
}

glm::vec2 Input::GetMouseDelta(void)
{
    return Mouse.CurrentPosition - Mouse.PreviousPosition;
}

glm::vec2 Input::GetScrollWheelMove(void)
{
    return Mouse.CurrentWheelMove;
}

glm::vec2 Input::GetScrollWheelDelta(void)
{
    return Mouse.CurrentWheelMove - Mouse.PreviousWheelMove;
}

void Input::PollInputEvents(void)
{
    Keyboard.KeyPressQueue = {};
    Keyboard.CharPressQueue = {};

    memcpy(&Keyboard.PreviousKeyState, &Keyboard.CurrentKeyState, sizeof(Keyboard.CurrentKeyState));
    memcpy(&Mouse.PreviousButtonState, &Mouse.CurrentButtonState, sizeof(Mouse.CurrentButtonState));

    Mouse.PreviousWheelMove = Mouse.CurrentWheelMove;
    Mouse.CurrentWheelMove = glm::vec2(0.0f);

    Mouse.PreviousPosition = Mouse.CurrentPosition;

    glfwPollEvents();
}

void Input::KeyCallback(GLFWwindow* glfwWindow, int32 key, int32 scancode, int32 action, int32 mods)
{
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(scancode);
    KeyCode keyCode = (KeyCode)key;
    if (keyCode == KeyCode::None)
    {
        return;
    }

    ModifierCode modCode = (ModifierCode)mods;
    Keyboard.CurrentKeyState[(int32)keyCode] = (InputState)action;

    // TODO: Don't cast ModifierCode to uint8
    if (keyCode == KeyCode::CapsLock && (uint8(modCode) & uint8(ModifierCode::CapsLock)) == uint8(ModifierCode::CapsLock) ||
        keyCode == KeyCode::NumLock && (uint8(modCode) & uint8(ModifierCode::NumLock)) == uint8(ModifierCode::NumLock))
    {
        Keyboard.CurrentKeyState[(int32)keyCode] = InputState::Press;
    }

    Keyboard.KeyPressQueue.emplace(keyCode);
}

void Input::CharCallback(GLFWwindow* glfwWindow, uint32 key)
{
    UNUSED_PARAM(glfwWindow);
    KeyCode keyCode = (KeyCode)key;
    Keyboard.CharPressQueue.emplace(keyCode);
}

void Input::MouseButtonCallback(GLFWwindow* glfwWindow, int32 button, int32 action, int32 mods)
{
    UNUSED_PARAM(glfwWindow);
    UNUSED_PARAM(mods);
    Mouse.CurrentButtonState[button] = (InputState)action;
}

void Input::MouseCursorPosCallback(GLFWwindow* glfwWindow, double x, double y)
{
    UNUSED_PARAM(glfwWindow);
    Mouse.CurrentPosition = glm::vec2((float)x, (float)y);
}

void Input::MouseScrollCallback(GLFWwindow* glfwWindow, double xOffset, double yOffset)
{
    UNUSED_PARAM(glfwWindow);
    Mouse.CurrentWheelMove = glm::vec2((float)xOffset, (float)yOffset);
}

void Input::CursorEnterCallback(GLFWwindow* glfwWindow, int32 enter)
{
    UNUSED_PARAM(glfwWindow);
    Mouse.OnScreen = enter;
}