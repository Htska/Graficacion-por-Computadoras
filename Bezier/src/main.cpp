#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "Vector2.h"

int main()
{
    
    sf::RenderWindow window(sf::VideoMode({400, 400}), "My window");

    std::vector<sf::RectangleShape*> lines;

    Vector2 p0{200.f,300.f};
    Vector2 p1{350.f,400.f};
    Vector2 p2{50.f,400.f};
    Vector2 p4{200.f,100.f};

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if 
                (keyPressed->scancode == sf::Keyboard::Scan::Enter)
                {
                    for (int i =0; i<=1000; i++)
                    {
                        float t = ((float) i)/((float) 1000);
                        Vector2 l0 = p0.lerp(p1,t);
                        Vector2 l1 = p1.lerp(p4,t);
                        Vector2 B = l0.lerp(l1,t);

                        Vector2 l2 = p0.lerp(p2,t);
                        Vector2 l3 = p2.lerp(p4,t);
                        Vector2 B2 = l2.lerp(l3,t);
                        
                        sf::RectangleShape* rec1 = new sf::RectangleShape({1.f,1.f});
                        rec1->setPosition({B.getX(),B.getY()});

                        sf::RectangleShape* rec2 = new sf::RectangleShape({1.f,1.f});
                        rec2->setPosition({B2.getX(),B2.getY()});
                        lines.push_back(rec1);
                        lines.push_back(rec2);

                        window.clear(sf::Color::Black);

                        for(sf::RectangleShape* r : lines)
                        {
                            window.draw(*r);
                        }
                        window.display();
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));

                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    window.close();
                }
            }
            
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        //window.draw();

        // end the current frame
        window.display();
    }
}