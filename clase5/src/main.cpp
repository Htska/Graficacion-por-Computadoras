#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Vector2.h"

int main()
{
   sf::ContextSettings settings;
   settings.antiAliasingLevel = 10;
   //Se crea la ventana
   sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Curva de Bezier",sf::Style::Default, sf::State::Windowed, settings);

   // Se les asigna el prigen en el centro a todos los círculos
   sf::CircleShape circ{6.25f};
   circ.setOrigin({6.25f,6.25f});

   sf::CircleShape circ1{6.25f};
   circ1.setOrigin({6.25f,6.25f});

   sf::CircleShape circ2{6.25f};
   circ2.setOrigin({6.25f,6.25f});


   Vector2 vec{0.f,0.f};
   Vector2 vec1{0.f,0.f};
   Vector2 vec2{0.f,0.f};

   // Los arreglos con vértices
   std::vector<sf::Vertex> linea1;
   std::vector<sf::Vertex> linea2;
   std::vector<sf::Vertex> curva;

   int clicks = 0;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            //VErificamos si ocurre un click
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (++clicks<=3)
                {
                    if (clicks == 1)
                    {
                        // Se coloca el circulo en la posición del click
                        circ.setPosition(window.mapPixelToCoords(mouseButtonPressed->position));
                        // Se asigna un vector con las coordenadas
                        vec.set(window.mapPixelToCoords(mouseButtonPressed->position).x,window.mapPixelToCoords(mouseButtonPressed->position).y);
                        sf::Vertex vert1{sf::Vector2f(vec.getX(),vec.getY())};
                        vert1.color = sf::Color::Red;
                        //Se agrega el vértice a la linea
                        linea1.push_back(vert1);
                    } else if (clicks == 2)
                    {
                        circ1.setPosition(window.mapPixelToCoords(mouseButtonPressed->position));
                        vec1.set(window.mapPixelToCoords(mouseButtonPressed->position).x,window.mapPixelToCoords(mouseButtonPressed->position).y);
                        sf::Vertex vert2{sf::Vector2f(vec1.getX(),vec1.getY())};
                        vert2.color = sf::Color::Red;
                        // Se agrega el punto a las nuevas lineas
                        linea1.push_back(vert2);
                        linea2.push_back(vert2);
                    } else
                    {
                        circ2.setPosition(window.mapPixelToCoords(mouseButtonPressed->position));
                        vec2.set(window.mapPixelToCoords(mouseButtonPressed->position).x,window.mapPixelToCoords(mouseButtonPressed->position).y);
                        sf::Vertex vert3{sf::Vector2f(vec2.getX(),vec2.getY())};
                        vert3.color = sf::Color::Red;
                        linea2.push_back(vert3);
                        // Se calculan los puntos para crear la curva de Bezier
                        for (int i = 1; i <=1000; i++)
                        {
                            float t = ((float)i)/((float)1000);
                            Vector2 l0 = vec.lerp(vec1,t);
                            Vector2 l1 = vec1.lerp(vec2,t);
                            Vector2 B = l0.lerp(l1,t);
                            // Se crea el vértice(punto)
                            sf::Vertex punto{sf::Vector2f(B.getX(),B.getY())};
                            punto.color = sf::Color::Cyan;
                            // Se agrega a la curva
                            curva.push_back(punto);
                            // Se dibuja cada iteración para crear la animación.
                            window.clear(sf::Color::Black);
                            // Hay que dibujar los circulos y lineas para no perderlas
                            window.draw(linea2.data(), linea2.size(), sf::PrimitiveType::Lines);
                            window.draw(linea1.data(), linea1.size(), sf::PrimitiveType::Lines);
                            window.draw(curva.data(), curva.size(), sf::PrimitiveType::Points);
                            //std::cout << curva.size()<<"\n"<<std::endl;
                            window.draw(circ2);
                            window.draw(circ1);
                            window.draw(circ);
                            window.display();
                            std::this_thread::sleep_for(std::chrono::milliseconds(2));
                        }
                    }
                }
            } 
            // AL recibir ENTER se limpia todo
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scan::Enter)
                {
                    clicks = 0;
                    linea1.clear();
                    linea2.clear();
                    curva.clear();
                }
            } 
        }

        window.clear(sf::Color::Black);
        // DEpendiendo del numero de clicks se dibuja:
        // 1 click-> un circulo
        // 2 clicks-> dos circulos y una linea
        // 3 clicks -> todo
        switch (clicks)
        {
        case 3:
            window.draw(linea2.data(), linea2.size(), sf::PrimitiveType::Lines);
            window.draw(curva.data(), curva.size(), sf::PrimitiveType::Points);
            window.draw(circ2);
        case 2:
            window.draw(linea1.data(), linea1.size(), sf::PrimitiveType::Lines);
            window.draw(circ1);
        case 1:
            window.draw(circ);
        case 0:
            break;
        default:
            window.draw(linea1.data(), linea1.size(), sf::PrimitiveType::Lines);
            window.draw(linea2.data(), linea2.size(), sf::PrimitiveType::Lines);
            window.draw(curva.data(), curva.size(), sf::PrimitiveType::Points);
            window.draw(circ2);
            window.draw(circ1);
            window.draw(circ);
        }
        window.display();
    }
}