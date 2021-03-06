#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Binormal;
layout (location = 4) in vec2 a_TexCoord;
// TO DO: Upload model matrix to transform models

uniform mat4 u_ViewProjection;
out vec2 TexCoord;

void main()
{
    // Calculate final gl (screen) position
    // TO DO: Include model matrix in calculation
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);

    // Pass TexCoords down the pipeline. Will be needed in fragment shader
    TexCoord = a_TexCoord;
}

#type fragment
#version 330 core
out vec4 FragColor;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  


in vec2 TexCoord;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_MetalnessTexture;
uniform sampler2D u_RoughnessTexture;

uniform DirLight dirLight;
uniform vec3 u_View;

void main()
{
    // ambient
    vec3 ambient = dirLight.ambient * vec3(texture(u_AlbedoTexture, TexCoord));

    // Transform normals from rgb encoding to world vectors
    vec3 norm = texture(u_NormalTexture, TexCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);

    // Calculate diffuse light based on light direction and fragment normal
    vec3 direction = normalize(-dirLight.direction);
    float diff = max(dot(norm, direction), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(u_AlbedoTexture, TexCoord));

    // Superimpose lighting components
    vec3 result = diffuse + ambient;
    FragColor = vec4(result, 1.0);
}

