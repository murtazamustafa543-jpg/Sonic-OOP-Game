#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"collectables.h"

using namespace sf;
using namespace std;




class Player {
private:
public:
    int normalactive;
    int x = 0;
    int p = 0;
    Clock player;
    int points = 0;
    int collision;
    int pressed = 1;
    int hpleft;
    int invincible = 0;
    float velocityY;
    float jumpStrength, gravity, terminal_Velocity;
    float scale_x, scale_y;
    float cam_offset;
    Texture texture;
    float maxgravity;
    Sprite playersprite;
    Texture gifTexture;
    Sprite leftmovesprite;
    int poweractivated = 0;
    Clock powerClock;
    int character_switch = 1;
    float friction = 1;

    bool sound_played = false;
    
    SoundBuffer ring_SB;
    Sound ring_S;

    SoundBuffer spike_SB;
    Sound spike_S;

    SoundBuffer achieve_SB;
    Sound achieve_S;

public:
    int j = 4;
    float player_x, player_y;
    int raw_img_x, raw_img_y, Pheight, Pwidth;
    int hit_box_factor_x, hit_box_factor_y;
    bool onGround;
    float Pposition_x;
    float acceleration;
    float speed;
    float max_speed = 18;
    float velocityrX;
    float velocitylX;
    int screen_x;
    int Level;

    Player(int level) {
        Level = level;
        acceleration = 0.2;
        jumpStrength = -20.5;
        maxgravity = 1;
        if (level == 1) {
            acceleration = 0.2;
            gravity = maxgravity;
        }
        else if (level == 2) {
            acceleration = 0.4;
            gravity = maxgravity;
        }
        else if (level == 3) {
            maxgravity = 0.5;

            gravity = maxgravity;
            jumpStrength = -15.5;
        }
        else if (level == 4) {
            gravity = maxgravity;
        }
        hpleft = 5;
        j = 0;
        invincible = 0;
        cam_offset = 0;
        character_switch = 1;
        player_x = 150;
        player_y = 150;
        Pposition_x = 150;
        velocityY = 0;


        terminal_Velocity = 18;
        scale_x = 2;
        scale_y = 2;

        raw_img_x = 24;
        raw_img_y = 35;
        Pheight = raw_img_y * scale_y;
        Pwidth = raw_img_x * scale_x;
        velocityrX = 18;
        velocitylX = 18;
        hit_box_factor_x = 8 * scale_x;
        hit_box_factor_y = 5 * scale_y;
        poweractivated = 0;
        screen_x = 1200;

        onGround = false;

        

        /* gifTexture.loadFromFile("Data/0jog_left.png");*/

    }


    virtual void drawplayer(RenderWindow& window) {

        playersprite.setPosition(player_x, player_y);
        window.draw(playersprite);

    }

    void loadSound()
    {
        if (ring_SB.loadFromFile("Data/Ring.wav"))
        {
            ring_S.setBuffer(ring_SB);
        }

        if (spike_SB.loadFromFile("Data/Jump.wav"))
        {
            spike_S.setBuffer(spike_SB);
        }

        if (achieve_SB.loadFromFile("Data/Select.wav"))
        {
            achieve_S.setBuffer(achieve_SB);
        }
    }

    void runp(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) {
        /* drawplayerleft(window);*/
        /* drawplayer(window);*/
        ringplayer(collecties);
        playercollideability(collecties);
        playercollidespike(o);
        playercollidehp(collecties);
        playercollidecrystal(o);
        leveltriggers(o);
        collisionplayer();
    }







    void ringplayer(collectables& c) {
        for (int i = 0; i < c.numberofrings; i++) {
            float ring_screen_x = c.Rings[i].ring_x - cam_offset;
            if (player_x <= ring_screen_x + 16 && player_x >= ring_screen_x - 56 &&
                player_y <= c.Rings[i].ring_y + 40 && player_y >= c.Rings[i].ring_y - 40) {
                c.Rings[i].ring_x = 7000;
                c.Rings[i].ring_y = 7000;

                c.ringscollected++;

                loadSound();
                ring_S.play();
                
                points += 100;

                
            }
        }
    }
    void playercollideability(collectables& a) {
        for (int i = 0; i < a.numberofability; i++) {
            float ability_x = a.ability->abilityarray[i][0] - cam_offset;
            if (player_x <= ability_x + 32 && player_x >= ability_x - 64 &&
                player_y <= a.ability->abilityarray[i][1] + 40 && player_y >= a.ability->abilityarray[i][1] - 40) {
                a.ability->abilityarray[i][0] = 7000;
                a.ability->abilityarray[i][1] = 7000;
                loadSound();
                achieve_S.play();
                poweractivated = 1;
                powerClock.restart();

            }
        }

    }
    void playercollidehp(collectables& h) {
        for (int i = 0; i < h.numberofhp; i++) {
            float hp_x = h.hp->hparray[i][0] - cam_offset;
            if (player_x <= hp_x + 32 && player_x >= hp_x - 64 &&
                player_y <= h.hp->hparray[i][1] + 40 && player_y >= h.hp->hparray[i][1] - 40) {
                h.hp->hparray[i][0] = 7000;
                h.hp->hparray[i][1] = 7000;
                loadSound();
                achieve_S.play();
                hpleft++;


            }
        }
    }
    void playercollidespike(Obstacle& o) {
        if (invincible == 0) {
            int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;
            int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;
            for (int i = 0; i < o.numberofspikes; i++) {

                float spike_screen_x = o.spikes->spikearray[i][0] - cam_offset;
                float spike_x = spike_screen_x;
                float spike_y = o.spikes->spikearray[i][1];


                float player_bottom = player_y + 64;



                bool horizontalcollide = (player_x + 32 >= spike_x && player_x <= spike_x + 32);
                bool verticallycollide = (player_bottom >= spike_y && player_bottom <= spike_y + 10);
                bool falling = (velocityY > 0);

                if (horizontalcollide && verticallycollide && falling && pressed) {

                    velocityY = jumpStrength;
                    onGround = false;
                    gravity = maxgravity;
                    loadSound();
                    spike_S.play();
                    hpleft--;
                    collision = 1;
                    invincible = 1;
                    powerClock.restart();
                    if (player_x < spike_x) {
                        player_x -= 40;
                        Pposition_x -= 40;
                    }
                    else {
                        player_x += 40;
                        Pposition_x += 40;
                    }
                }
                else if (player_x <= spike_x + 32 && player_x + 32 >= spike_x && player_y + 64 >= spike_y && player_y <= spike_y + 64) {

                    velocityrX = max_speed;
                    velocitylX = max_speed;
                    if (player_x < spike_x) {
                        Pposition_x = ((col_right - 1) * 64 - hit_box_factor_x) + 20;//(col_right) * 64 - Pwidth - hit_box_factor_x - 1;
                        player_x = Pposition_x - cam_offset;
                        if (j != 2) {
                            j = 6;
                        }

                    }
                    else {
                        Pposition_x = (col_left + 1) * 64 - hit_box_factor_x;
                        player_x = Pposition_x - cam_offset;
                        if (j != 2) {
                            j = 5;
                        }
                    }
                }

            }


        }
    }

    void playercollidecrystal(Obstacle& o) {
        if (invincible == 0) {
            int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;
            int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;
            for (int i = 0; i < o.numberofcrystal; i++) {
                float crystal_screen_x = o.crystal->crystalarray[i][0] - cam_offset;
                if (player_x <= crystal_screen_x + 32 && player_x >= crystal_screen_x - 32 && player_y <= o.crystal->crystalarray[i][1] + 64 && player_y >= o.crystal->crystalarray[i][1] - 64) {
                    velocityrX = max_speed;
                    velocitylX = max_speed;

                    if (player_x < crystal_screen_x) {

                        Pposition_x = ((col_right - 1) * 64 - hit_box_factor_x) + 20;//(col_right) * 64 - Pwidth - hit_box_factor_x - 1;
                        player_x = Pposition_x - cam_offset;
                        if (j != 2) {
                            j = 6;
                        }
                    }
                    else if (player_x > crystal_screen_x) {

                        Pposition_x = ((col_left + 1) * 64 - hit_box_factor_x) + 30;
                        player_x = Pposition_x - cam_offset;
                        if (j != 2) {
                            j = 5;
                        }
                    }

                }
            }

        }
    }

    bool characterswitch() {
        static bool zpressed = false;

        if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (!zpressed) {  // Only trigger on key down
                zpressed = true;

                if (character_switch == 1) {
                    character_switch = 2;
                }
                else if (character_switch == 2) {
                    character_switch = 3;
                }
                else if (character_switch == 3) {
                    character_switch = 1;
                }
                return true;
            }
        }
        else {
            zpressed = false;  // Reset when key is released
        }

        return false;
    }


    void leveltriggers(Obstacle& o) {
        if (Level == 2) {

            if ((int)(Pposition_x + hit_box_factor_x + Pwidth / 2) / 64 == 124 && player_y > 9 * 64 - 64 && (int)(player_y + hit_box_factor_y + Pheight - 1) / 64 == 9) {
                o.wall->lvl[10][129] = '\0';
                o.wall->lvl[10][130] = '\0';
                o.wall->lvl[10][131] = '\0';

                o.wall->lvl[10][132] = '\0';
                o.wall->lvl[10][133] = '\0';
                o.wall->lvl[11][129] = '\0';
                o.wall->lvl[11][130] = '\0';
                o.wall->lvl[11][131] = '\0';
                o.wall->lvl[11][132] = '\0';
                o.wall->lvl[11][133] = '\0';
            }
            else if ((int)(Pposition_x + hit_box_factor_x + Pwidth / 2) / 64 == 33 && ((int)(player_y + hit_box_factor_y + Pheight - 1) / 64 == 12)) {
                o.wall->lvl[13][37] = '\0';
                o.wall->lvl[13][38] = '\0';
                o.wall->lvl[13][39] = '\0';
                o.wall->lvl[13][40] = '\0';
                o.wall->lvl[13][41] = '\0';
                o.wall->lvl[13][42] = '\0';
                for (int i = 37; i < 50; i++) {
                    o.wall->lvl[13][i] = '\0';
                }
                for (int i = 41;i < 55; i++) {
                    o.wall->lvl[10][i] = '\0';
                }

            }
        }
    }
    void collisionplayer() {
        if (collision == 1) {

            if (powerClock.getElapsedTime().asMilliseconds() <= 1000) {


            }
            else {

                powerClock.restart();
                invincible = 0;
                collision = 0;
            }
        }
    }

};

