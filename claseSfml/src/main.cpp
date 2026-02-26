#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Vector2.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "My window");

    std::vector<sf::RectangleShape*> linea;

    /*
    Vector2 p0{200.f,300.f};
    Vector2 p1{350.f,400.f};
    Vector2 p2{50.f,400.f};
    Vector2 p4{200.f,100.f};
    */
   

   sf::RectangleShape rec{{50.f,50.f}};

   rec.setPosition({20.f,20.f});

   rec.setFillColor(sf::Color::Red);

   sf::RectangleShape rec2{{50.f,50.f}};

   rec2.setPosition({20.f,70.f});
   rec2.setFillColor(sf::Color::Blue);

   //sf::CircleShape circ{50.f};

   //circ.setPosition({20.f,20.f});

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scan::Enter)
				{
                    while(rec.getPosition().x < 1000.f){
                    rec.setPosition({rec.getPosition().x+.5f,rec.getPosition().y});
                    rec2.setPosition({rec2.getPosition().x+1.f,rec2.getPosition().y});
                    window.clear(sf::Color::Black);

                        // draw everything here...
                        //window.draw(circ);
                        /*for (sf::RectangleShape* punto : linea)
                        {
                            window.draw(*punto);
                        }*/
                    window.draw(rec);
                    window.draw(rec2);
                        //rec.setPosition({90.f,90.f});

                        // end the current frame
                    window.display();
                    std::cout << "x: "<<window.mapCoordsToPixel(rec.getPosition()).x<< " y: "<<window.mapCoordsToPixel(rec.getPosition()).y<<std::endl;
                    std::cout << "x1: "<<window.mapCoordsToPixel(rec2.getPosition()).x<< " y1: "<<window.mapCoordsToPixel(rec2.getPosition()).y<<std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    }
                }
            }
        }



        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        //window.draw(circ);
        /*for (sf::RectangleShape* punto : linea)
        {
            window.draw(*punto);
        }*/
       window.draw(rec);
       window.draw(rec2);



        //rec.setPosition({90.f,90.f});

        // end the current frame
        window.display();
    }
}