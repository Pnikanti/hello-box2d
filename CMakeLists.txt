cmake_minimum_required (VERSION 3.8)
project (hello-box2d VERSION 0.1)

set(SOURCES
	 ${PROJECT_SOURCE_DIR}/src/context.cpp
	 ${PROJECT_SOURCE_DIR}/src/physics.cpp
	 ${PROJECT_SOURCE_DIR}/src/graphics.cpp
	 ${PROJECT_SOURCE_DIR}/src/entity.cpp
	 ${PROJECT_SOURCE_DIR}/src/shader.cpp
	 ${PROJECT_SOURCE_DIR}/src/camera.cpp
	 ${PROJECT_SOURCE_DIR}/src/app.cpp
	 ${PROJECT_SOURCE_DIR}/src/log.cpp
	 ${PROJECT_SOURCE_DIR}/src/gui.cpp
)

set(IMGUI_SOURCES
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui.cpp
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui_impl_glfw.cpp
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui_impl_opengl3.cpp
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui_tables.cpp
	${PROJECT_SOURCE_DIR}/dependencies/imgui/lib/imgui_widgets.cpp
)

find_package(OpenGL REQUIRED)

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
add_executable (${PROJECT_NAME} ${SOURCES} ${IMGUI_SOURCES} ${BOX2D_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
add_definitions(-DGLEW_STATIC)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${OPENGL_INCLUDE_DIRS}
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/glfw/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/glew/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/glm/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/spdlog/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/imgui/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/box2d/include
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC ${OPENGL_LIBRARIES}
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/glfw/lib/glfw3.lib
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/glew/lib/glew32s.lib
	PUBLIC ${PROJECT_SOURCE_DIR}/dependencies/box2d/lib/box2d.lib
)