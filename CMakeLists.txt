
# cmake_minimum_required(VERSION 3.28.3)

# set(CMAKE_CXX_STANDARD 20 "${CMAKE_CXX_FLAGS}")

# project(MotorGame3D)


# set(SOURCES
# 	src/game.cpp
# 	src/Motor.cpp
# 	src/Vector.cpp
# 	src/Cubo.cpp
# 	src/Triangulo.cpp
# 	src/Malla.cpp
# )

# set(IMGUI_SOURCES
# 	src/imgui/imgui.cpp
#     src/imgui/imgui_draw.cpp
#     src/imgui/imgui_tables.cpp
#     src/imgui/imgui_widgets.cpp
#     src/imgui/imgui_demo.cpp 
# 	src/imgui/backends/imgui_impl_sdlrenderer3.cpp
# 	src/imgui/backends/imgui_impl_sdlgpu3.cpp
# )

# include(FindPkgConfig)

# pkg_search_module(SDL3 REQUIRED sdl3)
# add_library(imgui STATIC ${IMGUI_SOURCES})

# add_executable(${PROJECT_NAME} 
# 	${SOURCES}
# 	${IMGUI_SOURCES}
# )

# target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_INCLUDE_DIRS})
# target_include_directories(${PROJECT_NAME} PUBLIC 
# 	src/imgui/
# 	src/imgui/backends/
# )

# target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES} ${CONAN_LIBS} imgui)




# if(PSP)
# 	create_pbp_file(
# 		TARGET ${PROJECT_NAME}
# 		ICON_PATH NULL
# 		BACKGROUND_PATH NULL
# 		PREVIEW_PATH NULL
# 		TITLE ${PROJECT_NAME}
#         VERSION 01.00
# 	)
# endif()



cmake_minimum_required(VERSION 3.14)
project(MotorGame3D)

include(FindPkgConfig)

add_executable(${PROJECT_NAME} 
    src/game.cpp
	src/Motor.cpp
	src/Vector.cpp
	src/Cubo.cpp
	src/Triangulo.cpp
	src/Malla.cpp
	src/upng.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/backends/imgui_impl_sdl3.cpp
    src/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

pkg_search_module(SDL3 REQUIRED sdl3)

target_include_directories(${PROJECT_NAME} PRIVATE 
	${SDL3_INCLUDE_DIRS}
    src/imgui
    src/imgui/backends
)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_LIBRARIES})

if(PSP)
	create_pbp_file(
		TARGET ${PROJECT_NAME}
		ICON_PATH NULL
		BACKGROUND_PATH NULL
		PREVIEW_PATH NULL
		TITLE ${PROJECT_NAME}
        VERSION 01.00
	)
endif()
