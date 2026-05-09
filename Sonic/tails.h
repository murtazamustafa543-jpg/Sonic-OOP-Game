#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"player.h"

using namespace sf;
using namespace std;
class Tail :public character {
public:
    Animation* tanimate;
    int flytime = 0;
    int once;


    Texture left; Texture right; Texture leftrun; Texture rightrun; Texture Jump; Texture roll; Texture hit; Texture  invincible_left;  Texture  invincible_right;  Texture pushleft;  Texture  pushright; Texture hang; Sprite h; Texture fly;  Texture  damage;
    Tail(int level) :character(level) {
        once = 1;
        player_x = 50;
        Pposition_x = 50;
        flytime = 7000;
        normalactive = 0;
        pressed = 0;
        velocitylX = 10;
        velocityrX = 10;
        max_speed = 10;
        tanimate = new Animation(40, 40, 8, 0.15);
        leftrun.loadFromFile("Data/tailrun.png");
        Jump.loadFromFile("Data/tj.png");
        fly.loadFromFile("Data/tfly.png");
        /* left.loadFromFile("Data/")*/
        texture.loadFromFile("Data/ts.png");
        playersprite.setTexture(texture);
        pushleft.loadFromFile("Data/tpush.png");
        hang.loadFromFile("Data/td.png");
        h.setTexture(hang);
        h.setScale(scale_x, scale_y);
    }


    void normalAbility(char**& lvl) {
        if (onGround) {
            pressed = true;  // Ready for next Z press
            gravity = maxgravity;
            if (j == 7) {
                j = 0;
            }
            else if (j == 8) {
                j = 4;
            }

        }
        int offset = player_y + velocityY;
        int row = (int)(offset + hit_box_factor_y + Pheight) / 64;
        int col_mid = (int)(Pposition_x + hit_box_factor_x + Pwidth / 2) / 64;
        if (row <= 0) {
            row++;
            player_y = row * 64;
            velocityY = 18;
        }
        else {
            if (lvl[row - 1][col_mid] == 'q' || lvl[row - 1][col_mid] == 'b' || lvl[row - 1][col_mid] == 'w') {
                player_y += 16;
            }

            if (Keyboard::isKeyPressed(Keyboard::Z) && (lvl[row - 1][col_mid] != 'q') && (lvl[row - 1][col_mid] != 'b') && (lvl[row - 1][col_mid] != 'w')) {
                if (pressed) {

                    powerClock.restart();
                    normalactive = 1;
                    pressed = 0;
                }

                if (normalactive && player_y > 65) {
                    player_y -= 16;
                    once = 1;
                    if (once == 1) {
                        gravity = 0.01;
                    }
                }

            }

            if (normalactive) {
                if (p == 1 || j == 0) {
                    j = 7;
                }
                else if (p == 3 || j == 4) {
                    j = 8;
                }
                if (powerClock.getElapsedTime().asMilliseconds() <= flytime) {


                    cout << "time:" << powerClock.getElapsedTime().asSeconds();
                }
                else {



                    normalactive = 0;


                }

            }




        }




    }


    void specialAbility() {
        if (poweractivated == 1) {

            flytime = 11000;
            if (powerClock.getElapsedTime().asMilliseconds() <= 12000) {



            }
            else {
                flytime = 7000;
                onGround = false;
                poweractivated = 0;
            }

        }
    };
    void run(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) {
        normalAbility(lvl);
        runc(lvl, window, collecties, o);
        specialAbility();

        if (j == 2) {

            tanimate->setex(Jump);
            tanimate->setframes(49, 40, 8, 0.15);
            x = 2;

            tanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 1) {
            if (x != 1) {
                tanimate->setframes(47.125, 35, 7, 0.15);
                tanimate->setex(leftrun);
                x = 1;
            }
            tanimate->setPosition(player_x, player_y + 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);

        }
        else if (j == 3) {

            if (x != 3) {
                tanimate->setframes(47.125, 35, 7, 0.15);
                tanimate->setex(leftrun);
                x = 3;
            }
            tanimate->setPosition(player_x + 64, player_y + 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);

            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 0) {
            playersprite.setScale(scale_x, scale_y);
            playersprite.setPosition(player_x, player_y);
            window.draw(playersprite);
        }
        else if (j == 4) {

            playersprite.setScale(-1 * scale_x, scale_y);
            playersprite.setPosition(player_x + 64, player_y);
            window.draw(playersprite);
        }
        else if (j == 5) {
            if (x != 5) {
                tanimate->setframes(49, 42, 9, 0.15);
                tanimate->setex(pushleft);
                x = 5;
            }
            tanimate->setPosition(player_x, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 6) {
            if (x != 6) {
                tanimate->setframes(49, 42, 9, 0.15);
                tanimate->setex(pushleft);
                x = 6;
            }
            tanimate->setPosition(player_x + 84, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 7) {
            if (x != 7) {
                tanimate->setex(fly);
                tanimate->setframes(43, 32, 4, 0.1);
                x = 7;
            }
            tanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 8) {
            if (x != 8) {
                tanimate->setex(fly);
                tanimate->setframes(43, 32, 4, 0.1);
                x = 8;
            }
            tanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }

    };
    void followPlayer(character* player) {
        float distance;
        float target_x = 0;
        if (player->Pposition_x - player->cam_offset < player_x) {
            target_x = player->Pposition_x;
        }
        else {
            target_x = player->Pposition_x;  // Stay slightly behind
        }
        distance = target_x - Pposition_x;

        if (distance > 20 || distance <= -20) {  // Only move if distance is significant
            if (distance > 0) {
                Pposition_x += 6;
                if (onGround && j != 6 && j != 7 && j != 8) {

                    j = 3;
                }

                p = 3;
            }
            else {
                Pposition_x -= 6;
                if (onGround && j != 2 && j != 5 && j != 7 && j != 8) {
                    j = 1;

                }

                p = 1;
            }

            // Sync logical position

        }
        else {
            if (j == 1 && onGround) {

                j = 0;
            }
            else if (j == 3 && onGround) {
                j = 4;
            }
        }
        player_x = Pposition_x - player->cam_offset;;


        if (distance > 2000 || distance < -2000) {
            player_y = 200;  // Set to your desired respawn Y
            if (player_x < player->player_x) {
                Pposition_x = player->Pposition_x + 100;
                player_x = Pposition_x;
            }
            else {

                Pposition_x = player->Pposition_x - 100;  // Set to your desired respawn X
                player_x = Pposition_x;
            }


            velocityY = 0;
            gravity = 0.2;
            onGround = false;

        }
        if (onGround) {
            gravity = maxgravity;
        }
    }
    void offrun(RenderWindow& window, character* p, char** lvl, Obstacle o) {
        offplayyergravity(p, lvl);

        playercollidecrystal(o, p);
        playercollidespike(o, p);
        jump();
        zjump();
        move(lvl, p);
        if (j == 2) {

            tanimate->setex(Jump);
            tanimate->setframes(49, 40, 8, 0.15);
            x = 2;

            tanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 1) {
            if (x != 1) {
                tanimate->setframes(47.125, 35, 7, 0.15);
                tanimate->setex(leftrun);
                x = 1;
            }
            tanimate->setPosition(player_x, player_y + 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);

        }
        else if (j == 3) {

            if (x != 3) {
                tanimate->setframes(47.125, 35, 7, 0.15);
                tanimate->setex(leftrun);
                x = 3;
            }
            tanimate->setPosition(player_x + 64, player_y + 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);

            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 0) {
            playersprite.setScale(scale_x, scale_y);
            playersprite.setPosition(player_x, player_y);
            window.draw(playersprite);
        }
        else if (j == 4) {

            playersprite.setScale(-1 * scale_x, scale_y);
            playersprite.setPosition(player_x + 64, player_y);
            window.draw(playersprite);
        }
        else if (j == 5) {
            if (x != 5) {
                tanimate->setframes(49, 42, 9, 0.15);
                tanimate->setex(pushleft);
                x = 5;
            }
            tanimate->setPosition(player_x, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 6) {
            if (x != 6) {
                tanimate->setframes(49, 42, 9, 0.15);
                tanimate->setex(pushleft);
                x = 6;
            }
            tanimate->setPosition(player_x + 84, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 7) {
            if (x != 7) {
                tanimate->setex(fly);
                tanimate->setframes(43, 32, 4, 0.1);
                x = 7;
            }
            tanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 8) {
            if (x != 8) {
                tanimate->setex(fly);
                tanimate->setframes(43, 32, 4, 0.1);
                x = 8;
            }
            tanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); // Time since last frame
            tanimate->animate(deltaTime);
            tanimate->setScale(-1 * scale_x, scale_y);
            tanimate->draw(window);
        }
        else if (j == 9) {
            h.setPosition(player_x, player_y);
            window.draw(h);
        }
    }
};
