#version 330 core

#define MAX_DIRECTION_LIGHT 5
#define MAX_POINT_LIGHT 5
#define MAX_SPOT_LIGHT 5

out vec4 FragColor;

// Texture
in vec2 TexCoord;
uniform sampler2D texture1;

// Light
struct LightData
{
    vec3 lightPos;
    vec3 viewPos;
    vec4 ambientColor;
    vec4 diffuseColor;
    vec4 specularColor;
};

struct DirectionLightData
{
    LightData lightData;
    vec3 direction;
};

struct PointLightData
{
    LightData lightData;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLightData
{
    LightData lightData;
    vec3 direction;
    float cutOff;
    float outerCutOff;
};

uniform float nbDirectionLight;
uniform float nbPointLight;
uniform float nbSpotLight;

uniform DirectionLightData directionLights[MAX_DIRECTION_LIGHT];
uniform PointLightData pointLights[MAX_POINT_LIGHT];
uniform SpotLightData spotLights[MAX_SPOT_LIGHT];

in vec3 Normal;
in vec3 FragPos;

vec4 DirectionLight(DirectionLightData p_data)
{
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-p_data.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 viewDir = normalize(p_data.lightData.viewPos - FragPos);
    vec3 reflectDir = reflect(lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return p_data.lightData.ambientColor + (diff * p_data.lightData.diffuseColor) + (spec * p_data.lightData.specularColor); 
}

vec4 PointLight(PointLightData p_data)
{
    float distance = length(p_data.lightData.lightPos - FragPos);
    float attenuation = 1.0 / (p_data.constant + p_data.linear * distance + p_data.quadratic * (distance * distance));

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(p_data.lightData.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // Specular
    vec3 viewDir = normalize(p_data.lightData.viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    return p_data.lightData.ambientColor * attenuation + (diff * p_data.lightData.diffuseColor * attenuation) + (spec * p_data.lightData.specularColor * attenuation); 
}

vec4 SpotLight(SpotLightData p_data)
{

    // Diffuse
    vec3 lightDir = normalize(p_data.lightData.lightPos - FragPos);
    float theta = dot(lightDir, normalize(-p_data.direction));
    if(theta > p_data.cutOff)
    {
        float epsilon = p_data.cutOff - p_data.outerCutOff;
        float intensity = clamp((theta - p_data.outerCutOff) / epsilon, 0.0, 1.0);

        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, lightDir), 0.0);

        // Specular
        vec3 viewDir = normalize(p_data.lightData.viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

        return p_data.lightData.ambientColor + (diff * p_data.lightData.diffuseColor * intensity) + (spec * p_data.lightData.specularColor * intensity); 
    }
    else
    {
        return p_data.lightData.ambientColor;
    }
}

vec4 LightCalc()
{
    vec4 result;
    for(int i = 0; i < nbDirectionLight; i++)
    {
        result += DirectionLight(directionLights[i]);
    }

    for(int i = 0; i < nbPointLight; i++)
    {
        result += PointLight(pointLights[i]);
    }

    for(int i = 0; i < nbSpotLight; i++)
    {
        result += SpotLight(spotLights[i]);
    }

    return result;
}

void main()
{
    vec4 text = texture(texture1, TexCoord);
    vec4 light = LightCalc();
    
    FragColor = text * light;
}
