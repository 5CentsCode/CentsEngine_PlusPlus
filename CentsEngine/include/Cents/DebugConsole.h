#pragma once
#include "Common.h"

class DebugConsole
{
public:

    static bool CreateNewConsole(int16 bufferSize);
    static bool ReleaseConsole();

    static bool RedirectConsoleIO();
    static void AdjustConsoleBuffer(int16 bufferSize);
    static bool AttachParentConsole(int16 bufferSize);
};