#version 410 core
in vec3 v_position;
in mat3 TBN;
in vec2 tc;
uniform sampler2D samp;
uniform sampler2D normalMap;

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
    vec3 v_normal = texture(normalMap, tc).rgb;
    v_normal = v_normal * 2.0 - 1.0;   
    v_normal = normalize(TBN * v_normal); 
    vec3 L = normalize(lightPos-v_position);
    vec3 N = normalize(v_normal);
    vec3 ambient = ambiental();
    vec3 dif = diffuse(L,N);
    vec3 spec = specular(L,N);
    vec3 objectColor = texture(samp,tc).rgb;
    //color = vec4(objectColor,1.0);
    color = vec4((ambient+dif+spec)*objectColor,1.0);
}