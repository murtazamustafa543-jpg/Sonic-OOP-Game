#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"player.h"


using namespace std;
class knuckles :public character {
public:
    Animation* kanimate;
    int once;
    Texture left; Texture right; Texture leftrun; Texture rightrun; Texture Jump; Texture roll; Texture hit; Texture punch; Texture  invincible_left;  Texture  invincible_right;  Texture pushleft;  Texture  pushright;  Texture hang; Sprite h;  Texture  damage;
    knuckles(int level) :character(level) {
        once = 1;
        player_x = 60;
        Pposition_x = 60;
        velocitylX = 12;
        velocityrX = 12;
        max_speed = 12;
        kanimate = new Animation(45, 40, 8, 0.15);
        leftrun.loadFromFile("Data/krun1.png");
        Jump.loadFromFile("Data/oj.png");
        punch.loadFromFile("Data/0punch.png");
        texture.loadFromFile("Data/left.png");
        playersprite.setTexture(texture);
        pushleft.loadFromFile("Data/kpush.png");
        hang.loadFromFile("Data/kd.png");
        h.setTexture(hang);
    }
    void normalAbility(char** lvl) {

        if (j != 2) {
            int row_top = (int)(player_y + hit_box_factor_y) / 64;
            int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
            int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;


            int max_rows = 13;

            if (row_top >= 0 && row_bottom < max_rows) {
                char tileTopRight = lvl[row_top][col_right];
                char tileBottomRight = lvl[row_bottom][col_right];

                if (tileTopRight == 'b' && tileBottomRight == 'b') {
                    if (j == 3) {

                        j = 8;
                    }

                    lvl[row_top][col_right] = '\0';
                    lvl[row_bottom][col_right] = '\0';

                }
                else if (tileBottomRight == 'b') {
                    if (j == 3) {

                        j = 8;
                    }
                    lvl[row_bottom][col_right] = '\0';
                }
                else if (tileTopRight == 'b') {
                    if (j == 3) {

                        j = 8;
                    }
                    lvl[row_top][col_right] = '\0';
                }

            }

            row_top = (int)(player_y + hit_box_factor_y) / 64;
            row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
            int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;
            if (row_top >= 0 && row_bottom < max_rows && col_left >= 0) {
                char tileTopLeft = lvl[row_top][col_left];
                char tileBottomLeft = lvl[row_bottom][col_left];

                if (tileTopLeft == 'b' && tileBottomLeft == 'b') {
                    if (j == 1) {

                        j = 7;
                    }
                    lvl[row_top][col_left] = '\0';
                    lvl[row_bottom][col_left] = '\0';
                }
                else if (tileBottomLeft == 'b') {
                    if (j == 1) {

                        j = 7;
                    }
                    lvl[row_bottom][col_left] = '\0';
                }
                else if (tileTopLeft == 'b') {
                    if (j == 1) {

                        j = 7;
                    }
                    lvl[row_top][col_left] = '\0';
                }

            }

        }

    }
    void specialAbility(char** lvl) {
        if (poweractivated == 1) {

            if (powerClock.getElapsedTime().asMilliseconds() <= 15000) {


                invincible = 1;
            }
            else {

                powerClock.restart();
                invincible = 0;
                poweractivated = 0;
            }

        }
    };
    void run(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) {

        runc(lvl, window, collecties, o);
        specialAbility(lvl);
        normalAbility(lvl);

        if (j == 2) {

            kanimate->setex(Jump);
            kanimate->setframes(49, 40, 8, 0.15);
            x = 2;

            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 1) {
            if (x != 1) {
                kanimate->setframes(50, 40, 7, 0.15);
                kanimate->setex(leftrun);
                x = 1;
            }
            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);

        }
        else if (j == 3) {

            if (x != 3) {
                kanimate->setframes(50, 40, 7, 0.15);
                kanimate->setex(leftrun);
                x = 3;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);

            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
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
                kanimate->setframes(49, 42, 9, 0.15);
                kanimate->setex(pushleft);
                x = 5;
            }
            kanimate->setPosition(player_x, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 6) {
            if (x != 6) {
                kanimate->setframes(49, 42, 9, 0.15);
                kanimate->setex(pushleft);
                x = 6;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 7) {
            if (x != 7) {
                kanimate->setex(punch);
                kanimate->setframes(45, 41, 8, 0.1);
                x = 7;
            }
            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds();
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 8) {
            if (x != 8) {
                kanimate->setex(punch);
                kanimate->setframes(45, 41, 8, 0.1);
                x = 8;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 9) {
            h.setPosition(player_x, player_y);
            window.draw(h);
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
                Pposition_x += 7;
                if (onGround && j != 6 && j != 7 && j != 8) {

                    j = 3;
                }

                p = 3;
            }
            else {
                Pposition_x -= 7;
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

            j = 9;
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

            kanimate->setex(Jump);
            kanimate->setframes(49, 40, 8, 0.15);
            x = 2;

            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 1) {
            if (x != 1) {
                kanimate->setframes(50, 40, 7, 0.15);
                kanimate->setex(leftrun);
                x = 1;
            }
            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);

        }
        else if (j == 3) {

            if (x != 3) {
                kanimate->setframes(50, 40, 7, 0.15);
                kanimate->setex(leftrun);
                x = 3;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds();
            kanimate->animate(deltaTime);

            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
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
                kanimate->setframes(49, 42, 9, 0.15);
                kanimate->setex(pushleft);
                x = 5;
            }
            kanimate->setPosition(player_x, player_y - 5, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 6) {
            if (x != 6) {
                kanimate->setframes(49, 42, 9, 0.15);
                kanimate->setex(pushleft);
                x = 6;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 7) {
            if (x != 7) {
                kanimate->setex(punch);
                kanimate->setframes(45, 41, 8, 0.1);
                x = 7;
            }
            kanimate->setPosition(player_x, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 8) {
            if (x != 8) {
                kanimate->setex(punch);
                kanimate->setframes(45, 41, 8, 0.1);
                x = 8;
            }
            kanimate->setPosition(player_x + 64, player_y, 0);
            float deltaTime = player.restart().asSeconds(); 
            kanimate->animate(deltaTime);
            kanimate->setScale(-1 * scale_x, scale_y);
            kanimate->draw(window);
        }
        else if (j == 9) {
            h.setTexture(hang);
            h.setPosition(player_x, player_y);
            h.setScale(scale_x, scale_y);
            window.draw(h);
        }

    }
};