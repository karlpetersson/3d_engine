#version 150

out vec4 outColor;

in Data {
    vec2 uv;
} DataIn;

uniform mat4 view;
uniform mat4 m_inverseView;
uniform mat4 m_inverseProjection;

uniform sampler2D tex_normal;
uniform sampler2D tex_diffuse;
uniform sampler2D tex_ambient;
uniform sampler2D tex_specular;
uniform sampler2D tex_shininess;
uniform sampler2D tex_depth;

layout (std140) uniform Light {
    vec4 l_pos;
    vec4 l_color;
};

void main()

{
    float depth = texture(tex_depth, DataIn.uv).x * 2.0 - 1.0;
    if(depth == 1.0) {
        discard;
    }
    
    vec3 viewSpacePos;
    viewSpacePos.xy = DataIn.uv * 2.0 - 1.0;
    viewSpacePos.z = depth;
    vec4 position = m_inverseProjection * vec4(viewSpacePos, 1.0);
    position.xyz /= position.w;
    
    vec3 normal = normalize(texture(tex_normal, DataIn.uv).xyz);
    vec3 l_dir = ((view * l_pos) - position).xyz;
    vec3 l_dirNormalized = normalize(l_dir);
    
    vec4 spec = vec4(0.0);
    
    // calcualate attenuation
    float att;
    float d = length(l_dir);
    float Kc = 1.0f;
    float Kl = 0.2f;
    float Kq = 0.05f;
    att = 1.0 / (Kc + (Kl*d) + (Kq*d*d));
    
    vec4 diffuse = texture(tex_diffuse, DataIn.uv);
    vec4 ambient = texture(tex_ambient, DataIn.uv);
    vec4 specular = texture(tex_specular, DataIn.uv);
    float shininess = texture(tex_shininess, DataIn.uv).x;
    
    vec4 test = texture(tex_normal, DataIn.uv);
    
    float intensity = max(dot(normal, l_dirNormalized), 0.0);
    
    if(intensity > 0.0f) {
        vec3 eye = normalize(-vec3(position));
        vec3 halfVector = normalize(l_dirNormalized + eye);
        float intensitySpecular = max(dot(halfVector, normal), 0.0);
        spec = specular * pow(intensitySpecular, shininess);
    }
    
    outColor = max(((diffuse * intensity * l_color) + spec) * att, ambient);
}