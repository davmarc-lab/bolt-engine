#version 420 core

#define MAX_LIGHTS 32

in vec2 texCoord;
in vec4 vertColor;

in VS_OUT {
    vec4 vertColor;
    vec2 texCoord;
    // vec3 normal;
} fs_out;

out vec4 fragColor;
in vec3 FragPos;
// uniform vec3 FragPos;
// TO REMOVE
uniform vec3 normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

layout(std140, binding = 1) uniform Lights {
    int a;
};

uniform Material material;
uniform vec3 viewPos;

struct Light {
    int type;
    float intensity;
    vec3 color;

    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutoff;
    float outerCutoff;

    bool isSmooth;
};

vec3 norm = vec3(0);
vec3 lightDir = vec3(0);
float diff = 0.f;
vec3 viewDir = vec3(0);
vec3 reflectDir = vec3(0);
float spec = 0.f;

vec3 directionalLight(Light light) {
    vec3 norm = normalize(normal);

    // ambient
    vec3 ambient = light.intensity * light.color * light.ambient * material.ambient;

    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.intensity * light.color * light.diffuse * diff * material.diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.intensity * light.color * light.specular * spec * material.specular;

    return (ambient + diffuse + specular);
}

vec3 pointLight(Light light) {
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.intensity * light.color * light.ambient * material.ambient;
    vec3 diffuse = light.intensity * light.color * light.diffuse * diff * material.diffuse;
    vec3 specular = light.intensity * light.color * light.specular * spec * material.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 spotLight(Light light) {
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient = light.intensity * light.color * light.ambient * material.ambient;
    vec3 diffuse = light.intensity * light.color * light.diffuse * diff * material.diffuse;
    vec3 specular = light.intensity * light.color * light.specular * spec * material.specular;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}

void main() {
    fragColor = fs_out.vertColor;
    // fragColor = vec4(a, 0, 0, 1);
}
