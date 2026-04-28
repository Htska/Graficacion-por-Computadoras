#version 410 core
in vec3 v_position;
in vec3 v_normal;

uniform vec3 lightPos;
uniform vec3 La;
uniform vec3 Ld;
uniform vec3 Ls;

uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float shininess;

out vec4 color;

vec3 ambiental(){
    return ka*La;
}

vec3 diffuse(vec3 L, vec3 N){
    return kd*Ld*max(dot(N,L),0.0);
}

vec3 specular(vec3 L, vec3 N){
    vec3 R = normalize(2.0*N*(dot(N,L))-L);
    vec3 V = normalize(-v_position);

    return ks*Ls*pow(max(dot(R,V),0.0),shininess);
}

void main()
{
    color = vec4(1.0,1.0,0.0,1.0);
}