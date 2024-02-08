#version 330 core
layout (location = 0) in vec2 aPos; 
layout (location = 1) in vec2 aTexCoord; 

out vec2 TexCoord; // Pass texture coordinate to fragment shader

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0); // Convert vec2 position to vec4
    TexCoord = aTexCoord;
}
