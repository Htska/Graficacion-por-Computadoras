#version 410 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 normal;

out vec3 v_position;
out vec3 v_normal;
out vec2 tc;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    v_position = vec3(view*model*vec4(position,1.0));
    v_normal = vec3(view*model*vec4(normal,0));
    tc = aTexCoord;
    gl_Position = projection * view * model * vec4(position, 1.0);
}