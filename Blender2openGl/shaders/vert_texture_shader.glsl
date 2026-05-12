#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal; // Referencia a las normal 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tc;
out vec3 FragPos;   // posicion del fragmento 
out vec3 Normal;    

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal; // matriz normal
    tc = aTexCoord;
}