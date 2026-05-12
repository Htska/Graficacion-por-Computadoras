#include "Core/Application.h"

Application::Application()
{

    // Create window
    m_window = std::make_unique<WindowGL>();

    // Create main scene
    m_scene = std::make_unique<Scene>(m_window.get());
}

Application::~Application(){

}

void Application::run()
{
    m_scene->render();
}
