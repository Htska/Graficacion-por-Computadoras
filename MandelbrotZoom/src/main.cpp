#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

// Vertex Shader source code (GLSL 4.10)
const char* vertexShaderSource = R"(
    #version 410 core
    layout (location = 0) in vec3 aPos;
    uniform float atime;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment Shader source code (GLSL 4.10)
const char* fragmentShaderSource = R"(
    #version 410 core
    out vec4 FragColor;
    uniform float atime;
    uniform float select;
    uniform vec2 displacement;
    uniform float zoom;

    float PI = 3.141592;

    
    // c es el pixel que estamos evaluando y z simpre será 0
    // zn = z*z + c
    // z0 = 0.0
    int mandelbrot(vec2 c, float max_iter){
    
        int i = 0;
        
        vec2 z = vec2(0.0);

        while( length(z) <= 2.0 && (i < max_iter))
        {
        
          float a = z.x * z.x - z.y * z.y ;
          float b = 2.0 * z.x * z.y;
        
          z = vec2(a,b) + c;
          i++;
        }
        return i;    
    }


    void main()
    {   
        // Conjunto de MandelBrot
        //1. (0,0) x (800,800) a (-2,-2) x (2,2)

        float max_iterations = atime;

        // Checar en su compu si dejar 1600 u 800
        float x = gl_FragCoord.x/800;
        float y = gl_FragCoord.y/800;

        float x1 = (x + displacement.x) * zoom;
        float y1 = (y + displacement.y) * zoom;
         
        float color = mandelbrot(vec2(x1,y1), max_iterations);
        

        if(color < max_iterations)
        {
            color = color/max_iterations;
            if (select == 1.0){
                FragColor = vec4(color,color,color,1.0);
                return;
            }                  
            FragColor = vec4(color,0.0,0.0,1.0);
        }else       
            FragColor = vec4(0.0,0.0,0.0,1.0);

    }
)";


std::vector<float> crearCuadrado(){

    
    std::vector<float> vertices;
    // v0
    vertices.push_back(1.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
    // v1
    vertices.push_back(1.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);
    // v2
    vertices.push_back(-1.0f); vertices.push_back(1.0f); vertices.push_back(0.0f);
    // v3
    vertices.push_back(-1.0f); vertices.push_back(-1.0f); vertices.push_back(0.0f);

    return vertices;
}

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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Mandelbrot", NULL, NULL);
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

    std::vector<float> vertices = crearCuadrado();
    GLuint VBO, VAO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO
    glBindVertexArray(0);

    float ptime = 0.0f;
    float time = 0.0f;
    //int fps;
    // Render loop
    bool pressed = false;
    float displacementx = -0.5f;
    float displacementy = -0.5f;
    float zoom = 4.0f;
    while (!glfwWindowShouldClose(window))
    {
        float ctime = glfwGetTime();
        if((ctime - ptime) > 0.2f){
            ptime = ctime;
            time = time + 1;
        }
        float select = 0.0;
        
        // Input
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        
        if(glfwGetKey(window,GLFW_KEY_1) == GLFW_PRESS){
            select = 1.0;
        }

        if(glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS){
            time = 0.0f;
            displacementx = -0.5f;
            displacementy = -0.5f;
            zoom = 4.0f;
        }


        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS && !pressed)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            displacementx = (((float)xpos) / 800.0f)-1.0f;
            displacementy = -(((float)ypos) / 800.0f);
            std::cout<<"x: "<<xpos<< ", y: "<< ypos<< std::endl;
            std::cout<<"x: "<<displacementx<< ", y: "<< displacementy<< std::endl;
            zoom -= zoom >= 0.25f? 0.25f: zoom>= 0.10?0.1f:0.01f;
            std::cout<<"Zoom: "<<zoom<<std::endl;
            pressed = true;
            time = 0.0f;
        } else if (state == GLFW_RELEASE)
        {
            pressed = false;
        }

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw the triangle
        glUseProgram(shaderProgram);

        // para animar cambiar 100 a time
        GLuint uniformTime = glGetUniformLocation(shaderProgram, "atime");
        glUniform1f(uniformTime,100.0f);

        GLuint selection = glGetUniformLocation(shaderProgram,"select");
        glUniform1f(selection,select);

        GLuint dis = glGetUniformLocation(shaderProgram,"displacement");
        glUniform2f(dis,displacementx,displacementy);

        GLuint zoo = glGetUniformLocation(shaderProgram,"zoom");
        glUniform1f(zoo,zoom);

       // glBindVertexArray(VAOcolor);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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