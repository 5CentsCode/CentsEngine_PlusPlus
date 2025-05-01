set(ProjectName Pong)
set(SourceFiles  "src/Pong.cpp" "src/Pong.h")

string(REPLACE "${CMAKE_SOURCE_DIR}/" "" RelativeToSourceDirectory "${CMAKE_CURRENT_SOURCE_DIR}")
set(BuildDirectory "${CMAKE_BINARY_DIR}/${RelativeToSourceDirectory}")

add_executable(${ProjectName} WIN32 ${SourceFiles})
target_link_libraries(${ProjectName} PUBLIC CentsEngine)

string(REPLACE "${ProjectName}" "" ProjectParentDirectory "${RelativeToSourceDirectory}")
set_target_properties(${ProjectName} PROPERTIES FOLDER "${ProjectParentDirectory}")

set(ReleaseDir $<$<CONFIG:Release>:Release>)
set(DebugDir $<$<CONFIG:Debug>:Debug>)
set(ConfigDir "${BuildDirectory}/${ReleaseDir}${DebugDir}/content")

add_custom_command( 
    TARGET ${ProjectName} 
    POST_BUILD COMMAND ${CMAKE_COMMAND} 
        -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/content" ${ConfigDir})

        add_custom_command( 
    TARGET ${ProjectName} 
    POST_BUILD COMMAND ${CMAKE_COMMAND} 
        -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/content" "${BuildDirectory}/content")