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
out vec3 outSpecular;
out vec3 outAmbient;
out vec3 outNormal;
out vec3 outDiffuse;
out vec3 outShininess;

void main()
{
    outNormal = normalize(DataIn.norm);
    outDiffuse = diffuse.xyz;
    outAmbient = ambient.xyz;
    outSpecular = specular.xyz;
    outShininess.x = shininess;
}
