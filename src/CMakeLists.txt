# Add the executable
add_executable(pong_game)

target_sources(pong_game PRIVATE 
    main.cpp 
)

target_link_libraries(pong_game
    glfw 
    # GLEW::GLEW 
    # glm::glm
)