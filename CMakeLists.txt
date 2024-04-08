cmake_minimum_required(VERSION 3.5)

project(guiapp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
set(CMAKE_BUILD_TYPE "Release")

if(UNIX)
    message("OS Linux")
else()
    message("OS Windows")
endif()

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW
)

set(IMGUI_SRC
        dependencies/imgui/imgui.h
        dependencies/imgui/imgui.cpp
        dependencies/imgui/imconfig.h
        dependencies/imgui/imgui_demo.cpp
        dependencies/imgui/imgui_draw.cpp
        dependencies/imgui/imgui_internal.h
        dependencies/imgui/imgui_tables.cpp
        dependencies/imgui/imgui_widgets.cpp
        dependencies/imgui/imstb_rectpack.h
        dependencies/imgui/imstb_textedit.h
        dependencies/imgui/imstb_truetype.h
        )
set(GLFW_SRC
        dependencies/imgui/backends/imgui_impl_glfw.cpp
        dependencies/imgui/backends/imgui_impl_glfw.h
        dependencies/imgui/backends/imgui_impl_opengl3.cpp
        dependencies/imgui/backends/imgui_impl_opengl3.h
        dependencies/imgui/backends/imgui_impl_opengl3_loader.h
    )
set(GUI_WRAPPER_SRC
        guiwrapper/guiwrapper.h
        guiwrapper/guiwrapper.cpp
        dependencies/stb_image.h
        guiwrapper/modules.h
    )

add_executable(guiapp main.cpp ${IMGUI_SRC} ${GLFW_SRC} ${GUI_WRAPPER_SRC})


message("Set path to lib...")
if(UNIX)
    set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/static/amd64)
else()
    set(LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/static/x86-64)
endif()

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW
)

message("Copy lib... ")

if(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(guiapp PRIVATE
        ${LIBRARY_PATH}/libimgui.a
        ${LIBRARY_PATH}/libglfw3.a
        OpenGL::GL
    )

else()
    target_link_libraries(guiapp PRIVATE
        ${LIBRARY_PATH}/glfw3dll.lib
        ${LIBRARY_PATH}/imgui.lib
        ${LIBRARY_PATH}/OpenGL32.lib
    )

    add_custom_command(
       TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/static/x86-64/glfw3.dll
       $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(
       TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/static/x86-64/libgcc_s_seh-1.dll
       $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(
       TARGET ${PROJECT_NAME} POST_BUILD
       COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_CURRENT_SOURCE_DIR}/lib/windows/static/x86-64/libstdc++-6.dll
       $<TARGET_FILE_DIR:${PROJECT_NAME}>)

endif()

add_custom_command(
   TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
   ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.png
   $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/icon.png)

add_custom_command(
   TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
   ${CMAKE_CURRENT_SOURCE_DIR}/resources/roboto.ttf
   $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/roboto.ttf)









