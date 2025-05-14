set(ProjectName CentsEngine)
set(IncludeFiles
    include/Cents/Application.h
    include/Cents/Common.h
    include/Cents/DebugConsole.h
    include/Cents/Mesh.h
    include/Cents/Model.h
    include/Cents/Shader.h

    include/Cents/Component/Camera.h
    include/Cents/Component/Transform.h
)

set(SourceFiles
    src/Application.cpp
    src/DebugConsole.cpp
    src/Main.cpp
    src/Mesh.cpp
    src/Model.cpp
    src/Shader.cpp

    src/Component/Camera.cpp
    src/Component/Transform.cpp
)

add_library(${ProjectName} ${SourceFiles} ${IncludeFiles})
target_link_libraries(${ProjectName} PUBLIC glm)
target_link_libraries(${ProjectName} PRIVATE glad glfw tinyobjloader)

target_include_directories(${ProjectName} PUBLIC include/)
target_include_directories(${ProjectName} PRIVATE include/Cents/ src/)