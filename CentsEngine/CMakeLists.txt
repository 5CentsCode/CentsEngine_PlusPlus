set(ProjectName CentsEngine)
set(SourceFiles CMakeLists.txt)

add_library(${ProjectName} ${SourceFiles})
target_link_libraries(${ProjectName} PUBLIC glm)
target_link_libraries(${ProjectName} PRIVATE glad glfw)