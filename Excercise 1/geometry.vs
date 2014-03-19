#version 150

in vec3 position;
in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 m_normal;

out Data {
    out vec3 norm;
    out vec4 eyePos;
} DataOut;

void main()
{
    DataOut.norm = normalize(m_normal * normal);
    DataOut.eyePos = view * model * vec4(position, 1.0);
    
    gl_Position = proj * view * model * vec4(position, 1.0);
}