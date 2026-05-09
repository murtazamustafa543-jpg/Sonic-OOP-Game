#pragma once
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class EggStinger : public Enemy
{
private:
    float speed_x = 5;
    float speed_y = 5;

    int speed = 5;

    bool player_collision;
    bool player_fall;

    float block_x;
    float block_y;
    float spike_x;
    float spike_y;
    Clock time;
    int level;

    Texture btex;
    Texture stex;

    Sprite spike;
    Sprite base;

    Texture stinger_Ltex;

    Sprite stinger_LSprite;

    float target_x;
    float target_y;
    bool going_down;
    bool going_up;
    int col;
    int target_col;
    bool spike_check;
    bool base_check;

    float spike_L;
    float spike_R;
    float spike_T;
    float spike_B;

    bool spike_collision;
    bool spike_collided;

    bool enemy_collision;
    bool enemy_collided;

    Clock Collision_clock;
    bool ground_spike_collision;

    bool sprite_left;
    bool sprite_right;
    bool sprite_normal;

    Animation* spikeAnimate;

    
    
public:
    EggStinger(Texture& blockTex, Texture& spikeTex, Texture& enemyTex, char** LVL, float enemy_x, float enemy_y, int stage, Texture& stingerL, Texture& spikeAnimateTex) : Enemy(enemy_x, enemy_y, 15, enemyTex)
    {
        speed_x = 5;
        speed_y = 5;

        level = stage;

        btex = blockTex;
        stex = spikeTex;

        stinger_Ltex = stingerL;

        base.setTexture(btex);
        base.setPosition(-100, -100);
        base.setScale(0.09, 0.15);

        spike.setTexture(stex);
        spike.setPosition(-100, -100);
        spike.setScale(1, 1);

        stinger_LSprite.setTexture(stinger_Ltex);
        stinger_LSprite.setPosition(-100, -100);
        stinger_LSprite.setScale(1, 1);

        sprite.setScale(1, 1);

        target_x = enemy_x;
        target_y = enemy_y;
        going_down = false;
        going_up = false;
        target_col = 0;

        

        spikeAnimate = new Animation(222/3, 77, 3, 0.2);
        spikeAnimate->setex(spikeAnimateTex);
        spikeAnimate->setPosition(enemy_x, enemy_y, 0);
        spikeAnimate->setScale(1.25, 1.25);


    }

    void movement(Player* player, char**& lvl)
    {
        col = (player->player_x / 60.7);

        if (going_down == false && going_up == false && time.getElapsedTime().asSeconds() < 10)
        {
            enemy_x += speed;
            if (enemy_x < 50 || enemy_x > 1300)
            {
                speed *= -1;
            }
        }

        if (speed < 0)
        {
            sprite_left = true;
            sprite_normal = false;
            stinger_LSprite.setScale(1, 1);
        }
        if (speed > 0)
        {
            sprite_right = true;
            sprite_normal = false;
            stinger_LSprite.setScale(-1, 1);
        }

        if (going_down == false && going_up == false && time.getElapsedTime().asSeconds() >= 10) 
        {
            target_x = player->player_x;
            target_y = player->player_y;
            target_col = col;
            going_down = true;

            time.restart();
        }

        if (going_down == true)
        {
            int diff = enemy_x - target_x;
            if (diff > 2)
            {
                enemy_x -= speed_x;
                sprite_left = true;
                sprite_normal = false;
                stinger_LSprite.setScale(1, 1);
            }
            else if (diff < -2)
            {
                enemy_x += speed_x;
                sprite_right = true;
                sprite_normal = false;
                stinger_LSprite.setScale(-1, 1);
            }
            else 
            {
                enemy_x = target_x; 
                spike_check = true;
                if (enemy_y < 450) 
                {
                    sprite_normal = true;
                    sprite_left = false;
                    sprite_right = false;
                    enemy_y += speed_y;
                }
            }


            if (enemy_y >= 450)
            {
                
                base_check = true;
                lvl[9][target_col] = '\0';
                base.setPosition(enemy_x, enemy_y + 50);
                spike_check = false;
                going_down = false;
                going_up = true;

            }
        }

        else if (going_up == true) 
        {
            sprite_normal = true;
            sprite_left = false;
            sprite_right = false;
            if (enemy_y > 100) 
            {
                enemy_y -= speed_y;
            }
            else 
            {
                base_check = false;
                going_up = false;
                time.restart();
            }
        }
        enemy_l = enemy_x - 70;
        enemy_t = enemy_y;
        spike_L = enemy_x - 10;
        spike_T = enemy_y + 150;

        spikeAnimate->setScale(1, 1);
        spikeAnimate->setPosition(enemy_x-2, enemy_y +160, 0);
        spikeAnimate->animate(0.021333f);

        stinger_LSprite.setPosition(enemy_x - 70, enemy_y);
        sprite.setPosition(enemy_x - 70, enemy_y);
        spike.setPosition(enemy_x - 10, enemy_y + 150);
        base.setPosition(enemy_x + 5, enemy_y + 170);
    }

    void collision_check(Player* player, int& killed) 
    {
        player_l = player->player_x;
        player_r = player->player_x + player->Pwidth;
        player_t = player->player_y;
        player_b = player->player_y + player->Pheight;

        spike_R = spike_L + 81;
        spike_B = spike_T + 91;

        enemy_r = enemy_l + 170;
        enemy_b = enemy_t + 165;

        bool player_fall;
        if (player->j != 2)
        {
            player_fall = false;
            spike_collided = true;
            enemy_collided = true;
        }
        else
        {
            player_fall = true;
        }


        
        if ((player_r < spike_L || player_l > spike_R || player_b < spike_T || player_t > spike_B))
        {
            spike_collision = false;

        }
        else
        {
            spike_collision = true;
        }

        if (player_fall== true && spike_collision == true && spike_collided == true && spike_check== true)
        {
            player->hpleft -= 1;
            spike_collided = false;  
        }

        if ((player_r < enemy_l || player_l > enemy_r || player_b < enemy_t || player_t > enemy_b))
        {
            enemy_collision = false;

        }
        else
        {
            enemy_collision = true;
        }

        if (player_fall== true && enemy_collision == true && enemy_collided == true)
        {
            loadSound();
            dead_S.play();
            hp--;
            if (hp == 0)
            {
                player->points += 2000;
            }
            enemy_collided = false;
        }

        if (player_fall == false && spike_collision == true && ground_spike_collision == false)
        {

            player->hpleft -= 1;
            ground_spike_collision = true;
            Collision_clock.restart();
        }

        if (ground_spike_collision && Collision_clock.getElapsedTime().asMilliseconds() >= 500)
        {
            ground_spike_collision = false;
        }


    }



    void drawHP(RenderWindow& window, Font& font)
    {
        Text hpText;
        hpText.setFont(font);
        hpText.setCharacterSize(20);
        hpText.setFillColor(Color::White);
        hpText.setString("EggStinger lives " + to_string(hp));
        hpText.setPosition(50, 20);
        window.draw(hpText);
    }



    void draw(RenderWindow& window)
    {
        if (spike_check == true)
        {
            //window.draw(spike);
            spikeAnimate->draw(window);
        }

        if (base_check == true)
        {
            window.draw(base);
        }
        if(sprite_normal == true)
        {
            window.draw(sprite);
        }
        else
        {
            window.draw(stinger_LSprite);
        }

    }




};

