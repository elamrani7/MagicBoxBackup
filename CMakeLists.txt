cmake_minimum_required(VERSION 3.10)
project(MagicBoxRogue)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW (avec CMake)
add_subdirectory(external/glfw)

# Include paths
include_directories(
    external/imgui
    external/imgui/backends
    external/glfw/include
)

# Fichiers ImGui à compiler manuellement
set(IMGUI_SOURCES
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

# Ton interface graphique
file(GLOB GUI_SOURCES "gui/main_gui.cpp")

add_executable(magicbox WIN32 ${GUI_SOURCES} ${IMGUI_SOURCES})

target_link_libraries(magicbox
    glfw
    opengl32
)
