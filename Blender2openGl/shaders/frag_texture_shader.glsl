#version 410 core
in vec2 tc;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D samp;

uniform vec3 lightColor;   
uniform vec3 lightPos; // world space     

uniform vec3 viewPos; // For the Specular 


out vec4 FragColor;

void main()
{
    
    vec3 objectColor = texture(samp, tc).rgb; // obtenemos el color de la textura 

    // Ambient light 
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor; // comunmente es blanco

    // Diffuse Light
    vec3 norm = normalize(Normal); // Target - Origin 
    vec3 lightDir = normalize(lightPos - FragPos); // vector hacia la luz
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular 

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 2);
    vec3 specular = specularStrength * spec * lightColor;

    
    // vec3 result = (ambient + diffuse) * objectColor;
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}