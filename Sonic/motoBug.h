#pragma once
#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Motobug : public Enemy 
{
private:
    int x_min_boarder;
    int x_max_boarder;
    int speed = 2;
    
    bool player_fall;
    bool normal_collision;
    bool jump_collision;
    int level;
    bool right = true;
    bool animate_check;

    Animation* bugAnimate;

public:
    Motobug(float X, float Y,  Texture& TEXTURE, int min_boarder, int max_boarder, int stage)
        : Enemy(X, Y, 1, TEXTURE)
    {
        bugAnimate = new Animation(40, 30, 3, 0.2f);
        bugAnimate->setex(TEXTURE);
        bugAnimate->setPosition(enemy_x, enemy_y, 0);
        bugAnimate->setScale(2, 2);

        sprite.setTexture(TEXTURE);                        
        sprite.setTextureRect(IntRect(0, 0 , 40, 30));       
        sprite.setScale(2, 2);                   


        x_min_boarder = min_boarder;
        x_max_boarder = max_boarder;


        level = stage;

    }

    void movement(float player_x, float cam_offset)
    {
        bool inRange;
        if (player_x >= x_min_boarder && player_x <= x_max_boarder)
        {
            inRange = true;
            animate_check = true;
            if (player_x > enemy_x)
            {
                enemy_x = enemy_x + speed;
                right = true;
                
                if (player_x - enemy_x < 1)
                {
                    animate_check = false;
                    right = false;
                }
            }
            else if (player_x < enemy_x)
            {
                enemy_x = enemy_x - speed;
                right = false;
                if (enemy_x-player_x < 1)
                {
                    animate_check = false;
                }
            }

            bugAnimate->setPosition(enemy_x, enemy_y, cam_offset);
            bugAnimate->animate(0.021333f);
            
        }
        else
        {
            animate_check = false;
            inRange = false;
            
        }

        if (inRange== true)
        {
            sprite.setPosition(enemy_x +40 - cam_offset, enemy_y);
        }
        else
        {
            sprite.setPosition(enemy_x - 30 - cam_offset, enemy_y);
        }


        if (right == true)
        {
            bugAnimate->setScale(2, 2);
            sprite.setScale(2, 2);
        }
        else
        {
            bugAnimate->setScale(-2, 2);
            sprite.setScale(-2, 2);
        }

    }

    void collision_check(Player* player, int& killed)
    {

        
        if (player->invincible == 0) {
            

            enemy_t = enemy_y;
            enemy_b = enemy_y + 80;
            enemy_l = enemy_x;
            enemy_r = enemy_x + 60;

            player_b = player->player_y + player->Pheight;
            player_t = player->player_y;
            player_l = player->Pposition_x;
            player_r = player->Pposition_x + player->Pwidth;


            if (player->velocityY > 0)
            {
                player_fall = true;
            }
            else
            {
                player_fall = false;
            }

            if (player_r >= enemy_l && player_l <= enemy_r && player_b >= enemy_t && player_t <= enemy_b)
            {
                normal_collision = true;
            }
            else
            {
                normal_collision = false;
            }

            if (player_fall == true && player_b >= enemy_t && player_b <= enemy_t + 30 && player_r >= enemy_l && player_l <= enemy_r)
            {
                jump_collision = true;
            }

            else
            {
                jump_collision = false;
            }

            if (jump_collision == true)
            {
                hp = 0;
                killed++;
                loadSound();
                if (sound_played == false)
                {
                    dead_S.play();
                    sound_played = true;
                }
                player->points += 200;
                    
            }

            if (normal_collision == true && jump_collision == false)
            {
                player->hpleft -= 1;
                player->invincible = 1;
                collision123 = 1;
                collision1234.restart();
            }

            
        }
    }

    

    void draw(RenderWindow& window) 
    {
        if(animate_check==true)
        {
            bugAnimate->draw(window);
        }
        else
        {
            window.draw(sprite);
        }
    }

    ~Motobug() {
        delete bugAnimate;
    }
};
