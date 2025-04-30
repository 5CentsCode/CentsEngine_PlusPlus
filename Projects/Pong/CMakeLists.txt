set(ProjectName Pong)
set(SourceFiles  "src/Pong.cpp" "src/Pong.h")

add_executable(${ProjectName} WIN32 ${SourceFiles})
target_link_libraries(${ProjectName} PUBLIC CentsEngine)

string(REPLACE "${CMAKE_SOURCE_DIR}/" "" RelativeFolder "${CMAKE_CURRENT_SOURCE_DIR}")
string(REPLACE "${ProjectName}" "" RelativeFolder "${RelativeFolder}")
set_target_properties(${ProjectName} PROPERTIES FOLDER "${RelativeFolder}")

set(LinkSource "${CMAKE_CURRENT_SOURCE_DIR}/content")
set(LinkDestination "${CMAKE_BINARY_DIR}/content")
add_custom_command( 
    TARGET ${ProjectName} 
    POST_BUILD COMMAND ${CMAKE_COMMAND} 
        -E create_symlink ${LinkSource} ${LinkDestination})