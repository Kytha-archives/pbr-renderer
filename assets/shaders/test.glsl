#type vertex
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Binormal;
layout (location = 4) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
out vec2 TexCoord;

void main()
{
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    TexCoord = a_TexCoord;
}

#type fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_MetalnessTexture;
uniform sampler2D u_RoughnessTexture;

void main()
{
    FragColor = texture(u_AlbedoTexture, TexCoord);
} 
