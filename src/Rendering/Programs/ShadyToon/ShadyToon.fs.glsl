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

vec3 CalcShadyToon(vec3 lightPos, vec3 lightAmbient, vec3 lightDiff, vec3 lightColor, vec3 normal);
vec3 CalcDirLightAndShadows(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
float CalcShadow(vec4 fragPosLightSpace);

void main()
{
    vec3 norm = normalize(fs_in.Normal);
    vec3 viewDir = normalize(uViewPos - fs_in.FragPos);

    vec3 result = CalcDirLightAndShadows(dirLight, norm, viewDir);
    for (int i = 0; i < uPointLightsAmount; i++) {
        result += CalcPointLight(pointLights[i], norm, viewDir);
    }

    FragColor = vec4(result, 1.0);
}

vec3 CalcShadyToon(vec3 lightPos, vec3 lightAmbient, vec3 lightDiff, vec3 lightColor, vec3 normal) {
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float intensity = max(dot(normal, lightDir), 0.0);

    // Define the number of toon shading levels
    const int numLevels = 3;

    int toonLevel = int(intensity * float(numLevels));
    float levelStep = 1.0 / float(numLevels);
    float threshold = float(toonLevel) * levelStep;
    float quantizedIntensity = threshold * float(numLevels);

    vec3 shadedColor = quantizedIntensity * lightDiff * lightColor;
    shadedColor += lightAmbient * lightColor;

    return shadedColor;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 color = texture(uDiffuseTexture, fs_in.TexCoords).rgb;
    vec3 shadedColor = CalcShadyToon(light.position, light.ambient, light.diffuse, light.color, normal);
    shadedColor += light.ambient;

    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float intensity = max(dot(normal, lightDir), 0.0);

    float distance = length(light.position - fs_in.FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 result = color * intensity * attenuation * shadedColor;

    return result;
}

vec3 CalcDirLightAndShadows(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 shadedColor = CalcShadyToon(light.position, light.ambient, light.diffuse, light.color, normal);
    shadedColor += light.ambient;

    float shadow = CalcShadow(fs_in.FragPosLightSpace);

    vec3 lighting = (shadedColor + (1.0 - shadow) * shadedColor) * texture(uDiffuseTexture, fs_in.TexCoords).rgb;
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