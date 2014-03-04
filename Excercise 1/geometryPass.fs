#version 150

in Data {
    vec3 norm;
    vec4 eyePos;
} DataIn;

uniform mat4 view;

layout (std140) uniform Material {
    vec4 ambient; 
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

layout (location = 0) out vec3 def_pos; // "go to GL_COLOR_ATTACHMENT0"
layout (location = 1) out vec3 def_norm; // "go to GL_COLOR_ATTACHMENT1"
layout (location = 2) out vec3 def_diffuse; // "go to GL_COLOR_ATTACHMENT2"
layout (location = 3) out vec3 def_ambient; // "go to GL_COLOR_ATTACHMENT3"
layout (location = 4) out vec3 def_specular; // "go to GL_COLOR_ATTACHMENT4"
layout (location = 5) out vec3 def_texcoord; // "go to GL_COLOR_ATTACHMENT5"

void main()
{
    def_pos = DataIn.eyePos;
    def_norm = DataIn.norm;
    def_diffuse = diffuse;
    def_ambient = ambient;
    def_specular = specular;
}