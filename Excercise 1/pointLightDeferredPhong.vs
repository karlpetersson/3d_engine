#version 150

in vec3 position;

out Data {
    out vec2 uv;
} DataOut;

void main()
{
    DataOut.uv = vec2(position.x+1.0, position.y+1.0)/2;
    gl_Position = vec4(position, 1.0);
}