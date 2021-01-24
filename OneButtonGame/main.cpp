#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>

#include "Player.h"
#include "Obstacle.h"

using namespace sf;

int main()
{
    //srand(time(NULL));
    RenderWindow window(VideoMode(800, 600), "One Button Game");
    window.setFramerateLimit(60);

    //Player Init
    Player player(window.getSize());
    int ShootTimer = 20;
    //int scoring = 0;

    //Obstacle Init
    int obstacleSpawnTimer = 0;
    std::vector<Obstacle> obstacles;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //Player movement and collision with window
        //Movement left and collision with left border 
        player.shape.move(-10.f, 0.0f);
        if (player.shape.getPosition().x <= player.shape.getGlobalBounds().width)
            player.shape.setPosition(0.f, player.shape.getPosition().y); 
        
        //Movement right and collision with right border 
        player.shape.move(10.f, 0.0f);
        if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) 
            player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
        
        //Stop movement
        if (Keyboard::isKeyPressed(Keyboard::Space))
            player.shape.setPosition(player.shape.getPosition().x , player.shape.getPosition().y);

        //Enemy
        if (obstacleSpawnTimer < 40)
            obstacleSpawnTimer++;

        if (obstacleSpawnTimer >= 40)
        {
            obstacles.push_back(Obstacle(window.getSize()));
            obstacleSpawnTimer = 0; //reset timer
        }

        for (size_t i = 0; i < obstacles.size(); i++)
        {
            //Movement
            obstacles[i].shape.move(0.f, 5.0f);

            //Enemy get out of the window
            if (obstacles[i].shape.getPosition().y <= 0 - obstacles[i].shape.getGlobalBounds().height)
            {
                obstacles.erase(obstacles.begin() + i);
                break;
            }

            //Enemy collision with Player
            if (obstacles[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
            {
                obstacles.erase(obstacles.begin() + i);
                player.setHP(player.getHP() - obstacles[i].getHP());
                break;
            }
        }

        window.clear();
        window.draw(player.shape);

        for (size_t i = 0; i < obstacles.size(); i++)
        {
            window.draw(obstacles[i].shape);
        }

        window.display();
    }

    return 0;
}