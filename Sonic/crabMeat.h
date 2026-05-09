#pragma once
#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class CrabMeat : public Enemy 
{
private:
    float bullet_targetX = 0;
    float bullet_targetY = 0;


    float xRangeMin;
    float xRangeMax;

    Sprite bullet;
    Texture bulletTex;

    float bullet_x = -100;
    float bullet_y = -100;

    bool bulletActive = false;
    char** LVL;
    Clock shootClock; 
    int level;
    bool player_fall;

    bool jump_collision;

    bool bullet_collision;

    Animation* crabAnimate;
    bool right_check = true;



public:
    CrabMeat(float X, float Y,Texture& crabTex, const Texture& bTex, float start, float end, char** lvl, int stage)
        : Enemy(X, Y, 4, crabTex) // HP = 4
    {

        crabAnimate = new Animation(40, 41, 4, 0.15f);
        crabAnimate->setex(crabTex);
        crabAnimate->setPosition(enemy_x, enemy_y, 0);
        crabAnimate->setScale(2, 2);

        level = stage;

        bulletTex = bTex;
        bullet.setTexture(bulletTex);
        bullet.setScale(0.05, 0.05);
        bullet.setPosition(-100, -100);

        xRangeMin = start;
        xRangeMax = end;
        LVL = lvl;





    }

    bool bulletOnGround() 
    {
        

        int row = (int)(bullet_y + 10) / 64;
        int col = (int)(bullet_x + 10 / 2) / 64;

        char block = LVL[row][col];
        if (block == 'q' || block == 'w' || block == 'b')
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void movement(float player_x, float cam_offset, float deltaTime) 
    {
        if (right_check == true) 
        {
            enemy_x += 2;
            if (enemy_x >= xRangeMax) 
            {
                right_check = false;
            }
        }
        else 
        {
            enemy_x -= 2;
            if (enemy_x <= xRangeMin) {
                right_check = true;
            }
        }

        crabAnimate->setPosition(enemy_x, enemy_y, cam_offset);
        crabAnimate->animate(0.016f); 


        sprite.setPosition(enemy_x - cam_offset, enemy_y);

        
        if (shootClock.getElapsedTime().asSeconds() >= 5.0f && bulletActive == false)
        {
            shootClock.restart();
            bullet_x = enemy_x + 30;
            bullet_y = enemy_y + 20;

            if (right_check== true) 
            {
                bullet_targetX = 10;
            }
            else 
            {
                bullet_targetX = -10;
            }

            bullet_targetY = -10;

            bulletActive = true;
        }



        if (bulletActive == true) 
        {
            bullet_x = bullet_x +  bullet_targetX;
            
            
            bullet_targetY = bullet_targetY + 0.5;          
            bullet_y = bullet_y + bullet_targetY;         

            bullet.setPosition(bullet_x - cam_offset, bullet_y);

            if (bulletOnGround() == true )
            {
                bulletActive = false;
                bullet.setPosition(-100, -100);
            }


            bullet.setPosition(bullet_x - cam_offset, bullet_y);

            if (bulletOnGround()== true) 
            {
                bulletActive = false;
                bullet.setPosition(-100, -100);
            }
        }
    }

    void collision_check(Player* player, int& killed) 
    {
        
        enemy_t = enemy_y;
        enemy_b = enemy_y + 60;
        enemy_l = enemy_x;
        enemy_r = enemy_x + 60;

        player_t = player->player_y;
        player_b = player_t + player->Pheight;
        player_l = player->Pposition_x;
        player_r = player_l + player->Pwidth;

        if (player->velocityY > 0)
        {
            player_fall = true;
        }
        else
        {
            player_fall = false;
        }

        if (player_b >= enemy_t && player_b <= enemy_t + 30 && player_r >= enemy_l && player_l <= enemy_r && player_fall)
        {
            jump_collision = true;
        }
        else
        {
            jump_collision = false;
        }
        
        if (jump_collision == true ) 
        {
            hp = 0;
            killed++;
            loadSound();
            if (sound_played == false)
            {
                dead_S.play();
                sound_played = true;
            }
            player->points += 400;
        }


        

        if (bulletActive == true) 
        {
            float bullet_l = bullet_x;
            float bullet_t = bullet_y;
            float bullet_r = bullet_l + 10;
            float bullet_b = bullet_t + 10;

            if (player_r >= bullet_l && player_l <= bullet_r && player_b >= bullet_t && player_t <= bullet_b)
            {
                bullet_collision = true;
            }
            else
            {
                bullet_collision = false;
            }

           

            if (bullet_collision == true) 
            {
                player->hpleft -= 1; 
                player->invincible = 1;
                collision123 = 1;
                collision1234.restart();

                bulletActive = false;
                bullet_x = -100;
                bullet_y = -100;
                bullet.setPosition(bullet_x, bullet_y);
            }
        }
    }


    void draw(RenderWindow& window) 
    {

        crabAnimate->draw(window);
        if (bulletActive == true)
        {
            window.draw(bullet);
        }
    }

    ~CrabMeat() {
        delete crabAnimate;
    }

    
};

