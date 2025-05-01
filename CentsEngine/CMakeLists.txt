set(ProjectName CentsEngine)
set(IncludeFiles
    include/Cents/DebugConsole.h
    include/Cents/Application.h
    include/Cents/Common.h
    include/Cents/Shader.h
    include/Cents/Window.h)

set(SourceFiles
    src/Application.cpp
    src/DebugConsole.cpp
    src/Main.cpp
    src/Shader.cpp
    src/Window.cpp)

add_library(${ProjectName} ${SourceFiles} ${IncludeFiles})
target_link_libraries(${ProjectName} PUBLIC glm)
target_link_libraries(${ProjectName} PRIVATE glad glfw)

target_include_directories(${ProjectName} PUBLIC include/)
target_include_directories(${ProjectName} PRIVATE include/Cents/ src/)