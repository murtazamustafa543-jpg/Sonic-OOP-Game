#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"player.h"
#include"Characters.h"
using namespace sf;
using namespace std;
class Sonic :public character {
public:

    Animation* sonicanimate;
    int once;
    Texture left; Texture right; Texture leftrun; Texture rightrun; Texture Jump; Texture roll; Texture hit; Texture  invincible_left;  Texture  invincible_right;  Texture pushleft;  Texture  pushright;   Texture hang; Sprite h;  Texture  damage;
    Sonic(int level) :character(level) {

        once = 1;
        leftrun.loadFromFile("Data/0jog_left.png");
        Jump.loadFromFile("Data/0upL.png");
        Jump.loadFromFile("Data/0upL.png");

        texture.loadFromFile("Data/0left_still.png");
        playersprite.setTexture(texture);
        playersprite.setScale(scale_x, scale_y);
        pushleft.loadFromFile("Data/0pushL.png");
        velocitylX = 18;
        velocityrX = 18;
        max_speed = 18;
        sonicanimate = new Animation(40, 40, 8, 0.15);
        hang.loadFromFile("Data/sd.png");
        h.setTexture(hang);
        h.setScale(scale_x, scale_y);
        rightrun.loadFromFile("Data/sp.png");
    }
    void specialAbility() {
        if (poweractivated == 1) {
            if (once == 1) {
                max_speed = 22;
                velocitylX = 22;
                velocityrX = 22;

                once = 0;

            }
            if (onGround) {
                if (p == 1 || j == 0 && j != 2) {
                    j = 7;
                }
                else if (p == 3 || j == 4 && j != 2) {
                    j = 8;
                }
            }
            if (powerClock.getElapsedTime().asMilliseconds() <= 4000) {



            }
            else {
                if (p == 1) {
                    j = 0;
                    sonicanimate->setframes(40, 40, 8, 0.15);
                }
                else if (p == 3) {
                    j = 4;
                    sonicanimate->setframes(40, 40, 8, 0.15);
                }

                once = 1;
                powerClock.restart();
                max_speed = 18;
                velocitylX = 18;
                velocityrX = 18;
                poweractivated = 0;
            }

        }
    };
    void run(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) {
        runc(lvl, window, collecties, o);
        specialAbility();
        if (j == 2) {

            sonicanimate->setex(Jump);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 1) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);

        }
        else if (j == 3) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);
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
            sonicanimate->setex(pushleft);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 6) {
            sonicanimate->setex(pushleft);
            sonicanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 7) {
            if (x != 7) {
                sonicanimate->setex(rightrun);
                sonicanimate->setframes(61, 59, 4, 0.15f);
                x = 7;
            }
            sonicanimate->setPosition(player_x, player_y - 32, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 8) {
            if (x != 8) {
                sonicanimate->setex(rightrun);
                sonicanimate->setframes(61, 59, 4, 0.15f);
                x = 8;
            }
            sonicanimate->setPosition(player_x + 64, player_y - 32, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);

        }


    };
    void followPlayer(character* player) {

        float target_x = 0;
        if (player->Pposition_x - player->cam_offset < player_x) {
            target_x = player->Pposition_x;
        }
        else {
            target_x = player->Pposition_x; 
        }
        float distance = target_x - Pposition_x;

        if (distance > 20 || distance <= -20) {  
            if (distance > 0) {
                Pposition_x += 8;
                if (onGround && j != 6 && j != 7 && j != 8) {

                    j = 3;
                }

                p = 3;
            }
            else {
                Pposition_x -= 8;
                if (onGround && j != 2 && j != 5 && j != 7 && j != 8) {
                    j = 1;

                }

                p = 1;
            }

            

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
            player_y = 200;  
            if (player_x < player->player_x) {
                Pposition_x = player->Pposition_x + 100;
                player_x = Pposition_x;
            }
            else {

                Pposition_x = player->Pposition_x - 100;  
                player_x = Pposition_x;
            }


            velocityY = 0;
            onGround = false;
            gravity = 0.2;
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

            sonicanimate->setex(Jump);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 1) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);

        }
        else if (j == 3) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);
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
            sonicanimate->setex(pushleft);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 6) {
            sonicanimate->setex(pushleft);
            sonicanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 9) {
            h.setPosition(player_x, player_y);
            window.draw(h);
        }

    }
    void lvl4run(RenderWindow& window, char**& lvl) {

        lvl4player_gravity(lvl);
        lvl4moveLeft(window, lvl);
        lvl4moveright(lvl);
        jump();
        if (j == 2) {

            sonicanimate->setex(Jump);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);
        }
        else if (j == 1) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(scale_x, scale_y);
            sonicanimate->draw(window);

        }
        else if (j == 3) {
            sonicanimate->setex(leftrun);
            sonicanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            sonicanimate->animate(deltaTime);
            sonicanimate->setScale(-1 * scale_x, scale_y);
            sonicanimate->draw(window);
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



    }
};