cmake_minimum_required(VERSION 3.5)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

project(CentsEnginePlusPlus)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(VERSION 0.1.0)

set(CMAKE_C_STANDARD 17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")

# Prevent "warning D9025 : overriding '/W3' with '/W4'"
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
string(REGEX REPLACE "/W[1-3]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_subdirectory(ThirdParty/glad)
set_target_properties(glad PROPERTIES FOLDER ThirdParty/glad)

add_subdirectory(ThirdParty/glfw)
set_target_properties(glfw PROPERTIES FOLDER ThirdParty/GLFW3)
set_target_properties(uninstall PROPERTIES FOLDER ThirdParty/GLFW3)
set_target_properties(update_mappings PROPERTIES FOLDER ThirdParty/GLFW3)

add_subdirectory(ThirdParty/glm)
set_target_properties(glm PROPERTIES FOLDER ThirdParty/glm)

file(TOUCH ThirdParty/stb/_.cpp)
add_library(stb STATIC ThirdParty/stb/stb_image.h ThirdParty/stb/_.cpp)
target_include_directories(stb PUBLIC ThirdParty/stb/)
set_target_properties(stb PROPERTIES FOLDER ThirdParty/stb)

add_subdirectory(ThirdParty/tinyobjloader)
set_target_properties(tinyobjloader PROPERTIES FOLDER ThirdParty/TinyObjLoader)

add_subdirectory(CentsEngine)
add_subdirectory(Projects)