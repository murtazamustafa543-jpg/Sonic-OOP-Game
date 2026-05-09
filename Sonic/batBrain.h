#pragma once
#include "enemy.h"
#include <cmath>
#include "animations.h"

class BatBrain : public Enemy
{
private:
    
    bool player_collision;
    bool player_fall;
    bool hit_check;
    float target_pos_x;
    float target_pos_y;
    int level;
    bool left;
    float diff_x;
    float diff_y;
    Clock clock;
    bool player_movement;
    Animation* batAnimate;

public:
    
    BatBrain(float X, float Y, Texture& TEXTURE, int stage) : Enemy(X, Y, 3, TEXTURE)
    {
        level = stage;
        sprite.setPosition(X, Y);

        batAnimate = new Animation(0, 33, 9, 0.066f); 
        batAnimate->setex(TEXTURE);
        batAnimate->setPosition(enemy_x, enemy_y, 0);
        batAnimate->setScale(1.5, 1.5);

        int start_frame[9] = { 0, 30, 60, 95, 130, 165, 198, 234, 274 };   
        int frame_w[9] = { 30, 30, 33, 35, 35, 33, 36, 40, 55 };   

        batAnimate->setFrame_w(start_frame, frame_w);
    }

    void movement(float player_x, float player_y, float player_moving, int& player_hp, Player* player)
    {
        if (player_moving == 0)
        {
            player_movement = false;

        }
        else
        {
            player_movement = true;
        }

        if (player_moving > 0)
        {
            left = false;
        }
        else if (player_moving < 0)
        {
            left = true;
        }


        float time = clock.restart().asSeconds();

        if (player_movement==true)
        {
            if (left == false)
            {
                target_pos_x = player_x - 100;
            }
            else
            {
                target_pos_x = player_x + 100;
            }
            target_pos_y = player_y - 100;
        }

        else
        {
            target_pos_x = player_x;
            target_pos_y = player_y;
        }

        diff_x = target_pos_x - enemy_x;
        diff_y = target_pos_y - enemy_y;

        if (enemy_x-player_x>=0.5) 
        {
            batAnimate->setScale(2, 2);
        }
        else 
        {
            batAnimate->setScale(-2, 2); 
        }

        batAnimate->setPosition(enemy_x , enemy_y, 0);
        batAnimate->animate(time); 

        float d = sqrt(diff_x * diff_x + diff_y * diff_y);

        if (d > 1)
        {
            
            enemy_x +=  (diff_x / d);
            enemy_y +=  (diff_y / d);

            hit_check = false;
        }
        else
        {
            enemy_x = target_pos_x;
            enemy_y = target_pos_y;

            if (hit_check == false)
            {
                player_hp--;
                player->invincible = 1;
                collision123 = 1;
                collision1234.restart();
                hit_check = true;
            }
        }

       
    }


    void collision_check(Player* player, int& killed)
    {
        if (player->j != 2)
        {
            player_fall = false;
        }
        else
        {
            player_fall = true;
        }
        
        enemy_l = enemy_x;
        enemy_t = enemy_y;
        enemy_r = enemy_l + 20;
        enemy_b = enemy_t + 10;

        player_l = player->player_x;
        player_r = player->player_x + player->Pwidth;
        player_t = player->player_y;
        player_b = player->player_y + player->Pheight;

        if ((player_r < enemy_l || player_l > enemy_r || player_b < enemy_t || player_t > enemy_b))
        {
            player_collision = false;
        }
        else
        {
            player_collision = true;
        }

        if (player_collision == true && player_fall== true)
        {
            
            hp = 0;
            killed++;
            loadSound();
            if (sound_played == false)
            {
                dead_S.play();
                sound_played = true;
            }
            player->points += 300;
               
        }
    }

    void draw(RenderWindow& window)
    {
        batAnimate->draw(window);
    }

    ~BatBrain() {
        delete batAnimate;
    }

    
};