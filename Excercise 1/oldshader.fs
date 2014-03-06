#version 150

out vec4 outColor;

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

layout (std140) uniform Light {
    vec4 l_pos;
    vec4 l_color;
};

void main()
{
    vec4 lightCameraSpace = view * l_pos;
    vec3 normalizedNorm = normalize(DataIn.norm);
    vec3 eye = normalize(vec3(-DataIn.eyePos));
    vec3 l_dir = vec3(lightCameraSpace - DataIn.eyePos);
    vec3 l_dirNormalized = normalize(l_dir);
    
    float intensity = max(dot(normalizedNorm, l_dirNormalized), 0.0);
    
    vec4 spec = vec4(0.0);
    
    // calcualate attenuation
    float att;
    float d = length(l_dir);
    float Kc = 1.0f;
    float Kl = 0.1f;
    float Kq = 0.02f;
    att = 1.0 / (Kc + (Kl*d) + (Kq*d*d));
    
    if(intensity > 0.0) {
        vec3 halfVector = normalize(l_dirNormalized + eye);
        float intensitySpecular = max(dot(halfVector, normalizedNorm), 0.0);
        spec = specular * pow(intensitySpecular, shininess);
    }
    
    outColor = max(((diffuse * intensity * l_color) + spec) * att, ambient);
}