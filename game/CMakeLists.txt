# Add the executable
add_executable(pong_game)

target_include_directories(pong_game PRIVATE ${GAME_DIR}/include)

target_sources(pong_game PRIVATE 
    src/SpdlogConfig.cpp 
    src/Game.cpp
    src/WindowManager.cpp
    src/InputHandler.cpp
    src/main.cpp 
)

target_link_libraries(pong_game
    glfw 
    # GLEW::GLEW 
    # glm::glm
    spdlog::spdlog
)