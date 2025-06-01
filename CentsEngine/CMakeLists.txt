set(ProjectName CentsEngine)
set(IncludeFiles
    include/Cents/Application.h
    include/Cents/Common.h
    include/Cents/Debug.h
    include/Cents/DebugConsole.h
    include/Cents/Input.h
    include/Cents/KeyCodes.h
    include/Cents/Mesh.h
    include/Cents/Model.h
    include/Cents/Plane.h
    include/Cents/Ray.h
    include/Cents/Shader.h
    include/Cents/Texture.h
    include/Cents/Window.h

    include/Cents/Component/Camera.h
    include/Cents/Component/Transform.h
)

set(SourceFiles
    src/Application.cpp
    src/Debug.cpp
    src/DebugConsole.cpp
    src/Input.cpp
    src/Main.cpp
    src/Mesh.cpp
    src/Model.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Window.cpp

    src/Component/Camera.cpp
    src/Component/Transform.cpp
)

add_library(${ProjectName} ${SourceFiles} ${IncludeFiles})
target_link_libraries(${ProjectName} PUBLIC glm stb)
target_link_libraries(${ProjectName} PRIVATE glad glfw tinyobjloader)

target_include_directories(${ProjectName} PUBLIC include/)
target_include_directories(${ProjectName} PRIVATE include/Cents/ src/)