#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D texture;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 color;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    float ambient = material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    float diffuse = material.diffuse * diff;

    // specular
    float spec = 0;
    if (diff > 0)
    {
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    }
    float specular = material.specular * spec;

    // final
    vec3 result = (ambient + diffuse) * texture(material.texture, TexCoords).rgb * light.color
    + specular * light.color;

    FragColor = vec4(result, 1.0);
}