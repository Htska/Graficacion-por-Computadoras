#include "Core/WindowGL.h"

void WindowGL::InitGLFW()
{
    if (!glfwInit())
    {
        std::cerr << "FAILED TO INITIALIZE GLFW\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "GLFW STARTED\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_glfwMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_glfwMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);

    if (!m_window)
    {
        std::cerr << "FAILED TO CREATE WINDOW\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);
    std::cout << "WINDOW CREATED\n";

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void WindowGL::InitGLEW()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "FAILED TO INITIALIZE GLEW\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "GLEW STARTED" << std::endl;

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // optional background
}

void WindowGL::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}