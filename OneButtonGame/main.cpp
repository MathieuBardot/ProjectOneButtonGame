#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>
#include <iostream>

#include "Player.h"
#include "Obstacle.h"

using namespace sf;

int main()
{
    //srand(time(NULL));
    RenderWindow window(VideoMode(800, 600), "One Button Game");
    window.setFramerateLimit(60);

    //Init text
    sf::Font font;
    font.loadFromFile("arial.ttf");

    //UI Init
    Text score;
    score.setFont(font);
    score.setCharacterSize(20);
    score.setFillColor(Color::White);
    score.setPosition(10.f, 10.f);

    Text gameOver;
    gameOver.setFont(font);
    gameOver.setCharacterSize(50);
    gameOver.setFillColor(Color::Red);
    gameOver.setPosition(100.f, (float)(window.getSize().x / 2));
    gameOver.setString("GAME OVER !");

    //Player Init
    Player player(window.getSize());
    int ShootTimer = 20;
    int scoring = 0;

    //Obstacle Init
    int obstacleSpawnTimer = 0;
    std::vector<Obstacle> obstacles;

    bool IsMoving1 = true;
    float move = 8.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (player.getHP() > 0)
        {

            //Player movement and collision with window
            if (IsMoving1 == true) {
                player.shape.move(move, 0.0f);
            }

            //Movement right and collision with right border 
            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) {
                move = -8;
            }
            //Movement left and collision with left border 
            else if (player.shape.getPosition().x <= player.shape.getGlobalBounds().width) {
                move = 8;
                scoring += 100;
            }

            //Stop movement

            else  if (Keyboard::isKeyPressed(Keyboard::Space)) {
                IsMoving1 = false;
            }
            else if (!Keyboard::isKeyPressed(Keyboard::Space)) {
                IsMoving1 = true;
            }

          

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
                    player.setHP(player.getHP() - 1);
                    break;
                }
            }
        }

        // UI Update
        score.setString("Your score :" + std::to_string(scoring));

        window.clear();
        window.draw(player.shape);

        for (size_t i = 0; i < obstacles.size(); i++)
        {
            window.draw(obstacles[i].shape);
        }

        // UI
        window.draw(score);

        if (player.getHP() <= 0)
        {
            window.draw(gameOver);
            window.draw(score);
        }

        window.display();
    }

    return 0;
}