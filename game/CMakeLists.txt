add_library(pong_core
    src/Physics.cpp
    src/GameObject.cpp
    src/Ball.cpp
    src/Paddle.cpp
)

target_include_directories(pong_core PUBLIC include)
target_link_libraries(pong_core PUBLIC glm::glm)

add_executable(pong_game
    src/SpdlogConfig.cpp
    src/Game.cpp
    src/WindowManager.cpp
    src/InputHandler.cpp
    src/Renderer.cpp
    src/main.cpp
)

target_link_libraries(pong_game PRIVATE
    pong_core
    glfw
    GLEW::GLEW
    OpenGL::GL
    spdlog::spdlog
)

file(COPY shaders DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_definitions(pong_game PRIVATE
    PONG_SHADER_DIR="${CMAKE_CURRENT_BINARY_DIR}/shaders/"
)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pong_core PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(pong_game PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(pong_core PRIVATE /W4)
    target_compile_options(pong_game PRIVATE /W4)
endif()
