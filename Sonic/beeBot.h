#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace sf;

class BeeBot : public Enemy {
private:

    float bullet_targetX = 0;
    float bullet_targetY = 0;


    float speed = 1.5;
    float shootTimer = 0;
    char** LVL;
    Clock shootClock;  
    int level = 0;

    Sprite bullet;
    Texture bulletTex;

    float bullet_x = -100;
    float bullet_y = -100;

    bool collision_player;
    bool player_fall;
    bool up_move;

    bool collision_bullet;

    Animation* beeAnimate;


public:
    bool bulletActive = false;

    BeeBot(float X, float Y, Texture& botTex, const Texture& bTex, char** lvl, int stage )
        : Enemy(X, Y, 5, botTex)
    {
        level = stage;
        LVL = lvl;

        sprite.setTextureRect(IntRect(0, 0, 30, 30));
        sprite.setScale(2.0f, 2.0f);

        bulletTex = bTex;
        bullet.setTexture(bulletTex);
        bullet.setScale(0.05f, 0.05f);
        bullet.setPosition(-100, -100); 

        beeAnimate = new Animation(47, 22, 4, 0.15f);
        beeAnimate->setex(botTex);
        beeAnimate->setPosition(enemy_x, enemy_y, 0);
        beeAnimate->setScale(1.25, 1.25);
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

    void movement(float deltaTime, float cam_offset) 
    {
        int initial_y;

        if (level == 2)
        {
            initial_y = 600;
        }
        else if (level == 3)
        {
            initial_y = 130;
        }
        float minY = initial_y - 30;
        float maxY = initial_y + 30;

        if (up_move== true)
        {
            enemy_y -= 1.5f;
        }
        else
        {
            enemy_y += 1.5f;
        }

        if (enemy_y <= minY)
        {
            up_move = false;
        }
        else if (enemy_y >= maxY)
        {
            up_move = true;
        }
        
        enemy_x += speed;

        if (level == 3)
        {
            if (enemy_x <= 12500 || enemy_x >= 13500) {
                speed *= -1;
            }
        }

        if (level == 2)
        {
            if (enemy_x <= 3880 || enemy_x >= 4780) {
                speed *= -1;
            }
        }

        if (speed>0) 
        {
            beeAnimate->setScale(-1.25f, 1.25f);
        }
        else
        {
            beeAnimate->setScale(1.25f, 1.25f);
        }

        beeAnimate->setPosition(enemy_x, enemy_y, cam_offset);
        beeAnimate->animate(0.016f);

        sprite.setPosition(enemy_x - cam_offset, enemy_y);

        if (shootClock.getElapsedTime().asSeconds() >= 5.0f && bulletActive == false) 
        {
            shootClock.restart();
            bullet_x = enemy_x + 30;
            bullet_y = enemy_y + 20;

            if (speed > 0) 
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
            bullet_x = bullet_x + bullet_targetX;


            bullet_targetY = bullet_targetY + 0.3;
            bullet_y = bullet_y + bullet_targetY;

            bullet.setPosition(bullet_x - cam_offset, bullet_y);

            if (bulletOnGround())
            {
                bulletActive = false;
                bullet_x = -100.0f;
                bullet_y = -100.0f;
                bullet.setPosition(bullet_x, bullet_y);  // No cam offset needed since it's hidden
            }
        }
    }



    void collision_check(Player* player, int& killed)
    {
        if (player->velocityY == 0 || player->velocityY == 1)
        {
            player_fall = false;
        }
        else
        {
            player_fall = true;
        }

        enemy_l = enemy_x;
        enemy_t = enemy_y;
        enemy_r = enemy_l + 60;
        enemy_b = enemy_t + 60;

        player_t = player->player_y;
        player_b = player_t + player->Pheight;
        player_l = player->Pposition_x;
        player_r = player_l + player->Pwidth;


        if (player_l < enemy_r && player_r > enemy_l && player_t < enemy_b && player_b > enemy_t)
        {
            collision_player = true;
        }
        else
        {
            collision_player = false;
        }

        if (collision_player == true && player_fall== true)
        {
            hp = 0;
            killed++;
            loadSound();
            if (sound_played == false)
            {
                dead_S.play();
                sound_played = true;
            }
            player->points += 500;
                
        }

        if (bulletActive == true) 
        {
            float bulletL = bullet_x;
            float bulletT = bullet_y;
            float bulletR = bulletL + 10;
            float bulletB = bulletT + 10;

            
            if (player_l < bulletR && player_r > bulletL && player_t < bulletB && player_b > bulletT)
            {
                collision_bullet = true;
            }
            else
            {
                collision_bullet = false;
            }

            if (collision_bullet == true)
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
        beeAnimate->draw(window);
        if (bulletActive)
        {
            window.draw(bullet);
        }
    }

    ~BeeBot() {
        delete beeAnimate;
    }

};
