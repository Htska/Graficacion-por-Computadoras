#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

// Vertex Shader source code (GLSL 4.10)
const char* vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    out vec3 vertexColor;
    out vec3 pos;

    void main()
    {
        gl_Position = vec4(aPos,1.0);
        vertexColor = aColor;
        pos = aPos;
    }
)";

// Fragment Shader source code (GLSL 4.10)
const char* fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    in vec3 vertexColor;
    in vec3 pos;
    uniform float choose;

    void main()
    {
        if(pos.r <= 0.25 && pos.r >= -0.25 && pos.g <= 0.25 && pos.g >= -0.25 && (choose == 1.0 || choose == 3.0))
        {
            FragColor = vec4(1.0,0.0,0.0, 1.0);
        } else if(pos.x*pos.x + (pos.y+0.7)*(pos.y+0.7)<= 0.09 && (choose == 2.0 || choose == 3.0))
        {
            FragColor = vec4(0.0,0.0,1.0,1.0);
        }else {
            FragColor = vec4(vertexColor, 1.0);
        }
    }
)";

/*void circle(float radio, const int num_lados,float* vertices){
    //float vertices[(num_lados+2)*3];
    float colors[306];
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.0f;
    colors[0] = 0.17f;
    colors[1] = 0.19f;
    colors[2] = 0.63f;
    float doblePi = 2.0f * M_PI;
    int count = 3;
    for (int i = 1; i<(num_lados +2);i++)
    {
        colors[count] = 0.17f;
        vertices[count++] = radio*cos(i * doblePi / num_lados);
        colors[count] = 0.19f;
        vertices[count++] = radio*sin(i * doblePi / num_lados);
        colors[count] = 0.63f;
        vertices[count++] = 0.0f;
    }
}*/

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL version to 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Build and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Build and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders to a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers and configure vertex attributes
    /*float vertices[] = {
        -1.0f, -1.0f, 0.0f,//0.7f,  0.9f, 0.2f, //mitad vertices y mitad colores
         1.0f, -1.0f, 0.0f,//0.3f,  0.2f, 0.6f,
         0.0f,  1.0f, 0.0f//,0.5f,  0.5f, 0.3f
    };*/

    float vertices[] = {
        0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  -1.0f, 0.0f
         
        // 1.0f, -1.0f, 0.0f,
         //1.0f, 0.0f, 0.0f,
         //0.0f, -1.0f, 0.0f
    };
    //const int num_lados = 100;
    //float vertices[(num_lados +2)*3];
    //circle(0.9,100,vertices);
    /*float vertices[] = {
        0.0f,1.0f,0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f,0.0f,0.0f,
        0.0f,-1.0f,0.0f
    };*/

    float colors1[] = {
         0.f,  1.f, 1.f,
         0.f,  1.f, 1.f,         
         0.f,  1.f, 1.f
         /*1.0f, 1.0f, 0.0f,
         1.0f, 0.0f, 1.0f,
         0.0f, 1.0f, 1.0f*/
    };

    GLuint VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3));
    //glEnableVertexAttribArray(1);

    // Unbind the VAO
    //glBindVertexArray(0);


    GLuint VBOcolor;//, VAOcolor;
    
    //glGenVertexArrays(1, &VAOcolor);
    glGenBuffers(1, &VBOcolor);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //glBindVertexArray(VAOcolor);
    //glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOcolor);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors1), colors1, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindVertexArray(0);

    float choose = 0.0f;
    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Render
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);
        GLuint uniformTime = glGetUniformLocation(shaderProgram, "choose");
        glUniform1f(uniformTime,choose);
        //glBindVertexArray(VAOcolor);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
            choose = 1.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
            choose = 2.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
            choose = 3.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS){
            choose = 0.0f;
        }       
        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
