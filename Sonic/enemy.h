#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"Characters.h"
using namespace sf;

class Enemy {
protected:
    int collision123 = 0;
    Sprite sprite;
    float enemy_x;
    float enemy_y;
    int hp;
    Clock collision1234;

    float enemy_t = 0;
    float enemy_b = 0;
    float enemy_l = 0;
    float enemy_r = 0;

    float player_b=0;
    float player_t=0;
    float player_l=0;
    float player_r=0;

    SoundBuffer dead_SB;
    Sound dead_S;

    bool sound_played = false;

public:
    Enemy(float X, float Y, int HP, const Texture& tex)
    {
        enemy_x = X;
        enemy_y = Y;
        hp = HP;
        sprite.setTexture(tex);
        sprite.setPosition(enemy_x, enemy_y);
        sprite.setScale(0.5, 0.5);

    }

    virtual void draw(RenderWindow& window) = 0;
    virtual void collision_check(Player* player, int& killed) = 0;

    void loadSound()
    {
        if (dead_SB.loadFromFile("Data/Destroy.wav"))
        {
            dead_S.setBuffer(dead_SB);
        }
    }

    bool enemy_died()
    {
        if (hp <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    


    void collisionplayer(character* player) 
    {
        if (collision123 == 1) {

            if (collision1234.getElapsedTime().asMilliseconds() <= 1000) {


            }
            else {

                collision1234.restart();
                player->invincible = 0;
                collision123 = 0;
            }
        }
    }
};
