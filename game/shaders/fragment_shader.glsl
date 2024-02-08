#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// Texture sampler
uniform sampler2D texture1;

void main() {
    FragColor = texture(texture1, TexCoord); 
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0); for white
}
