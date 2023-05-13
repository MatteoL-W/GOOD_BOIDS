#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

struct DirLight {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 color;
};

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 color;

    float constant;
    float linear;
    float quadratic;

};

uniform sampler2D uDiffuseTexture;
uniform sampler2D uShadowMap;
uniform vec3 uViewPos;

#define MAX_POINT_LIGHTS 10
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int uPointLightsAmount;

mat3 CalcBlinnPhong(vec3 lightPos, vec3 lightAmbient, vec3 lightDiff, vec3 lightSpec, vec3 lightColor, vec3 normal, vec3 viewDir);
vec3 CalcDirLightAndShadows(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
float CalcShadow(vec4 fragPosLightSpace);

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(uViewPos - fs_in.FragPos);

    vec3 result = CalcDirLightAndShadows(dirLight, norm, viewDir);
    for (int i = 0; i < uPointLightsAmount; i++)
    result += CalcPointLight(pointLights[i], norm, viewDir);

    FragColor = vec4(result, 1.0);
}

mat3 CalcBlinnPhong(vec3 lightPos, vec3 lightAmbient, vec3 lightDiff, vec3 lightSpec, vec3 lightColor, vec3 normal, vec3 viewDir) {
    vec3 color = texture(uDiffuseTexture, fs_in.TexCoords).rgb;

    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 ambient = lightAmbient * color * lightColor;
    vec3 diffuse = lightDiff * diff * color * lightColor;
    vec3 specular = lightSpec * spec * color * lightColor;

    return mat3(ambient, diffuse, specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    mat3 blinnPhong = CalcBlinnPhong(light.position, light.ambient, light.diffuse, light.specular, light.color, normal, viewDir);

    // Calculate attenuation
    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Combine lighting values
    vec3 result = (blinnPhong[0] + attenuation * (blinnPhong[1] + blinnPhong[2]));

    return result;
}

vec3 CalcDirLightAndShadows(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 color = texture(uDiffuseTexture, fs_in.TexCoords).rgb;
    mat3 blinnPhong = CalcBlinnPhong(light.position, light.ambient, light.diffuse, light.specular, light.color, normal, viewDir);

    // Calculate shadow
    float shadow = CalcShadow(fs_in.FragPosLightSpace);
    vec3 lighting = (blinnPhong[0] + (1.0 - shadow) * (blinnPhong[1] + blinnPhong[2])) * color;

    return lighting;
}

float CalcShadow(vec4 fragPosLightSpace) {
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;

    // Get closest depth value from light's perspective
    float closestDepth = texture(uShadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(dirLight.position - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // Check whether current fragment is in shadow using Percentage-Closer Filtering (PCF)
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    // Set shadow to 0.0 if outside the far plane region
    if (projCoords.z > 1.0) shadow = 0.0;

    return shadow;
}