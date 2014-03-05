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

out vec3 def_norm;
out vec4 def_diffuse;
out vec4 def_ambient;
out vec4 def_specular;
out vec3 def_shininess;

void main()
{
    def_norm = normalize(DataIn.norm);
    def_diffuse = diffuse;
    def_ambient = ambient;
    def_specular = specular;
    def_shininess.r = shininess;
    //def_pos = DataIn.eyePos;
    //def_norm = DataIn.norm;
    //def_diffuse = diffuse;
    //def_ambient = ambient;
    //def_specular = specular;
}