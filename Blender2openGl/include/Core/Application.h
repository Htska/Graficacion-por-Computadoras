#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Core/WindowGL.h"
#include "Core/Scene.h"

class Application
{
private:
    /**
     * El objetivo es que una aplicacion tenga una sola ventana y las escenas vean
     * a la ventana como observadoras. El duenio de la ventana es la aplicacion.
     */
    std::unique_ptr<WindowGL> m_window;
    /**
     * Una aplicacion va a ser duenia de varias scenas.
     *
     */
    std::unique_ptr<Scene> m_scene;

public:
    Application();
    ~Application();

    void run();
};

#endif