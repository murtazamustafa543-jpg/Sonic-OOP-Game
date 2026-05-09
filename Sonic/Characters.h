#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"player.h"
using namespace sf;
using namespace std;

class character :public Player {
public:
    float speed_character;

    Sprite charactersprite;
    Clock move1;
    int invincible_active;
    int moveback = 0;
public:

    virtual void run(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) = 0;
    character(int level) : Player(level) {
        speed_character = 18;

        invincible_active = 0;

    }
    void player_gravity(char** lvl) {

        float offset_y = player_y + velocityY;
        // << "character" << character_switch << endl;
        int row = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
        int col_left = (int)(Pposition_x + hit_box_factor_x) / 64;
        int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth) / 64;
        int col_mid = (int)(Pposition_x + hit_box_factor_x + Pwidth / 2) / 64;
        int max_rows = 13;
        if (row <= 0) {



            row++;
            player_y = row * 64 - 32;
            velocityY = 18;
        }
        else {
            if (row > max_rows) {
                if (row >= max_rows) {
                    
                    Level = 0;
                    onGround = false;
                }

            }
            else {
                char bottom_left = lvl[row][col_left];
                char bottom_right = lvl[row][col_right];
                char bottom_mid = lvl[row][col_mid];


                if ((bottom_mid == 'q') || (bottom_mid == 'w') || (bottom_mid == 'b')) {
                    onGround = true;
                    normalactive = 0;
                    if (onGround) {

                        gravity = maxgravity;
                        if (j == 7) {
                            j = 0;
                        }
                        else if (j == 8) {
                            j = 4;
                        }

                    }
                    gravity = maxgravity;
                    velocityY = 0;
                }

                else
                {

                    onGround = false;
                    player_y = offset_y;
                    velocityY += gravity;
                    if (velocityY > terminal_Velocity)
                        velocityY = terminal_Velocity;

                }
            }
        }

    }
    void moveLeft(RenderWindow& window, char** lvl) {
        int row_top = (int)(player_y + hit_box_factor_y) / 64;
        int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            int max_rows = 13;

            if (row_top >= 0 && row_bottom < max_rows && col_left >= 0) {
                char tileTopLeft = lvl[row_top][col_left];
                char tileBottomLeft = lvl[row_bottom][col_left];

                if (/*tileTopLeft != 'q'*/ /*&&*/ tileTopLeft != 'w' && tileBottomLeft != 'b' &&
                    tileBottomLeft != 'q' && tileBottomLeft != 'w' && tileBottomLeft != 'b') {

                    if (player_x > screen_x / 2 || Pposition_x <= 600) {
                        player_x -= velocitylX;
                        Pposition_x -= velocitylX;

                    }
                    else if (cam_offset > 0) {
                        cam_offset -= velocitylX;
                        Pposition_x -= velocitylX;
                    }
                }
                else {
                    if (j != 2 && onGround) {

                        j = 5;
                    }
                    Pposition_x = (col_left + 1) * 64 - hit_box_factor_x;
                    player_x = Pposition_x - cam_offset;
                    velocitylX = max_speed;

                }
            }

            velocitylX += acceleration;
            // << "vleft" << velocitylX << endl;
            if (onGround && j != 2 && j != 5 && j != 7 && j != 8) {
                j = 1;

            }

            p = 1;
        }
        else {
            if (j == 1 && onGround) {

                j = 0;
            }
            velocitylX = max_speed;


        }
    }



    void moveRight(char** lvl) {
        int row_top = (int)(player_y + hit_box_factor_y) / 64;
        int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            int max_rows = 13;

            if (row_top >= 0 && row_bottom < max_rows) {
                char tileTopRight = lvl[row_top][col_right];
                char tileBottomRight = lvl[row_bottom][col_right];

                if (/*tileTopRight != 'q' &&*/ tileTopRight != 'w' && tileTopRight != 'b' &&
                    tileBottomRight != 'q' && tileBottomRight != 'w' && tileBottomRight != 'b') {

                    if (player_x < screen_x / 2) {
                        player_x += velocityrX;
                        Pposition_x += velocityrX;
                    }
                    else {
                        cam_offset += velocityrX;
                        Pposition_x += velocityrX;
                    }
                }

                else {
                    if (j != 2 && onGround) {
                        j = 6;

                    }
                    Pposition_x = ((col_right - 1) * 64 - hit_box_factor_x) + 20;//(col_right) * 64 - Pwidth - hit_box_factor_x - 1;
                    player_x = Pposition_x - cam_offset;
                    velocityrX = max_speed;
                }
            }
            moveback += 5;
            velocityrX += acceleration;
            if (onGround && j != 6 && j != 7 && j != 8) {

                j = 3;
            }

            p = 3;
        }
        else {
            if (j == 3 && onGround) {

                j = 4;
            }


            velocityrX = max_speed;

        }


    }


    void jump() {


        if (Keyboard::isKeyPressed(Keyboard::Space) && onGround && player_y > 65) {
            j = 2;
            player.restart();
            velocityY = jumpStrength;
            onGround = false;
            gravity = maxgravity;


        }
        if (j == 2 && onGround) {
            if (p == 1) {
                j = 0;

            }
            else if (p == 3) {
                j = 4;

            }

        }


    }



    void runc(char** lvl, RenderWindow& window, collectables& collecties, Obstacle& o) {

        player_gravity(lvl);
        moveLeft(window, lvl);
        moveRight(lvl);
        /*drawplayer(window);*/
        jump();
        runp(lvl, window, collecties, o);

    }

    void move(char** lvl, character* player) {
        int row_top = (int)(player_y + hit_box_factor_y) / 64;
        int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;


        int max_rows = 13;

        if (row_top >= 0 && row_bottom < max_rows) {
            char tileTopRight = lvl[row_top][col_right];
            char tileBottomRight = lvl[row_bottom][col_right];

            if (/*tileTopRight != 'q' && */tileTopRight != 'w' && tileTopRight != 'b' &&
                tileBottomRight != 'q' && tileBottomRight != 'w' && tileBottomRight != 'b') {

            }
            else {
                if (j != 2 && onGround) {
                    j = 6;

                }


                Pposition_x = (col_right - 1) * 64 - hit_box_factor_x;
                player_x = Pposition_x - player->cam_offset;


                up();

            }
        }

        row_top = (int)(player_y + hit_box_factor_y) / 64;
        row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;
        if (row_top >= 0 && row_bottom < max_rows && col_left >= 0) {
            char tileTopLeft = lvl[row_top][col_left];
            char tileBottomLeft = lvl[row_bottom][col_left];

            if (/*tileTopLeft != 'q' && */tileTopLeft != 'w' && tileBottomLeft != 'b' &&
                tileBottomLeft != 'q' && tileBottomLeft != 'w' && tileBottomLeft != 'b') {


            }
            else {
                if (j != 2 && onGround) {

                    j = 5;
                }

                Pposition_x = (col_left + 1) * 64 - hit_box_factor_x;
                player_x = Pposition_x - player->cam_offset;

                up();
                /* Pposition_x -= 100;*/


            }
        }

    }
    void offplayyergravity(character* player, char** lvl) {
        float offset_y = player_y + velocityY;

        int row = (int)(offset_y + hit_box_factor_y + Pheight) / 64;
        int col_left = (int)(Pposition_x + hit_box_factor_x) / 64;
        int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth) / 64;
        int col_mid = (int)(Pposition_x + hit_box_factor_x + Pwidth / 2) / 64;
        int max_rows;
        if (Level == 1) {
            max_rows = 12;
        }
        else {
            max_rows = 13;
        }
        if (row <= 0) {

            velocityY = 0;
        }
        else {
            if (row > max_rows) {
                if (row >= max_rows || row < 0) {

                    player_y = 100;  // Set to your desired respawn Y
                    if (player_x < player->player_x) {
                        Pposition_x = player->Pposition_x + 100;
                        player_x = Pposition_x;
                    }
                    else {

                        Pposition_x = player->Pposition_x - 100;  // Set to your desired respawn X
                        player_x = Pposition_x;
                    }
                    velocityY = 0;
                    onGround = false;
                    j = 9;
                    gravity = 0.1;
                }




            }
            else {
                char bottom_left = lvl[row][col_left];
                char bottom_right = lvl[row][col_right];
                char bottom_mid = lvl[row][col_mid];



                if ((bottom_mid == 'q') || (bottom_mid == 'w') || (bottom_mid == 'b')) {
                    onGround = true;
                    gravity = maxgravity;
                    velocityY = 0;
                }
                else
                {
                    onGround = false;
                    player_y = offset_y;
                    velocityY += gravity;
                    if (velocityY > terminal_Velocity)
                        velocityY = terminal_Velocity;

                }
            }
        }
        if (onGround && j == 9) {
            if (p == 1) {
                j = 0;
            }
            else if (p == 3) {
                j = 4;
            }
        }
    }

    void playercollidespike(Obstacle o, Player* player) {
        for (int i = 0; i < o.numberofspikes; i++) {
            float spike_screen_x = o.spikes->spikearray[i][0] - player->cam_offset;
            if (player_x <= spike_screen_x + 32 && player_x >= spike_screen_x - 32 && player_y <= o.spikes->spikearray[i][1] + 32 && player_y >= o.spikes->spikearray[i][1] - 32) {
                velocityrX = max_speed;
                velocitylX = max_speed;

                if (player->player_x < spike_screen_x) {

                    player_x -= 40;
                    Pposition_x -= 40;
                    if (j != 2) {
                        j = 6;
                    }
                }
                else if (player->player_x > spike_screen_x) {

                    player_x += 40;
                    Pposition_x += 40;
                    if (j != 2) {
                        j = 5;
                    }
                }
                up();
            }
        }
    }
    void playercollidecrystal(Obstacle o, Player* player) {
        for (int i = 0; i < o.numberofcrystal; i++) {
            float crystal_screen_x = o.crystal->crystalarray[i][0] - player->cam_offset;
            if (player_x <= crystal_screen_x + 32 && player_x >= crystal_screen_x - 32 && player_y <= o.crystal->crystalarray[i][1] + 64 && player_y >= o.crystal->crystalarray[i][1] - 64) {
                velocityrX = max_speed;
                velocitylX = max_speed;
                if (player_x < crystal_screen_x) {

                    player_x -= 28;
                    Pposition_x -= 28;
                    if (j != 2) {
                        j = 6;
                    }
                }
                else if (player_x > crystal_screen_x) {


                    player_x += 20;
                    Pposition_x += 20;
                    if (j != 2) {
                        j = 5;
                    }
                }
                up();
            }
        }
    }
    void up() {
        if (onGround) {
            j = 2;
            velocityY = jumpStrength;
            onGround = false;
        }
        if (j == 2 && onGround) {
            if (p == 1) {
                j = 0;

            }
            else if (p == 3) {
                j = 4;

            }

        }
    }
    void zjump() {
        if (Keyboard::isKeyPressed(Keyboard::Z) && onGround && character_switch == 2) {
            velocityY = jumpStrength;
            j = 2;
            onGround = false;
        }
        if (j == 2 && onGround) {
            if (p == 1) {
                j = 0;

            }
            else if (p == 3) {
                j = 4;

            }

        }

    }
    void lvl4moveright(char** lvl) {
        int row_top = (int)(player_y + hit_box_factor_y) / 64;
        int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_right = (int)(Pposition_x + hit_box_factor_x + Pwidth + 0.1f) / 64;

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            int max_rows = 13;

            if (row_top >= 0 && row_bottom < max_rows) {

                char tileBottomRight = lvl[row_bottom][col_right];

                if (
                    tileBottomRight != 'q' && tileBottomRight != 'w' && tileBottomRight != 'b') {

                    if (player_x + velocityrX <= screen_x) {
                        player_x += velocityrX;

                    }
                    else {
                        player_x = screen_x - 64;
                    }

                }


            }


            if (onGround && j != 6 && j != 7 && j != 8) {

                j = 3;
            }

            p = 3;
        }
        else {
            if (j == 3 && onGround) {

                j = 4;
            }

        }


    }
    void lvl4moveLeft(RenderWindow& window, char** lvl) {
        int row_top = (int)(player_y + hit_box_factor_y) / 64;
        int row_bottom = (int)(player_y + hit_box_factor_y + Pheight - 1) / 64;
        int col_left = (int)(Pposition_x + hit_box_factor_x - 0.1f) / 64;

        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            int max_rows = 13;

            if (row_top >= 0 && row_bottom < max_rows && col_left >= 0) {

                char tileBottomLeft = lvl[row_bottom][col_left];

                if (
                    tileBottomLeft != 'q' && tileBottomLeft != 'w' && tileBottomLeft != 'b') {

                    if (player_x > 0) {
                        player_x -= velocitylX;

                    }
                    else {
                        player_x = 0;
                    }

                }

            }


            if (onGround && j != 6 && j != 7 && j != 8) {

                j = 1;
            }

            p = 1;
        }
        else {
            if (j == 1 && onGround) {

                j = 0;
            }


        }
    }
    void lvl4player_gravity(char** lvl) {

        float offset_y = player_y + velocityY;
        int row = (int)(offset_y + hit_box_factor_y + Pheight) / 64;

        int col_mid = (int)(player_x + hit_box_factor_x + Pwidth / 2) / 64;
        int max_rows = 13;
        if (row <= 0) {
            row++;
            player_y = row * 64;
            velocityY = 18;
        }
        else {
            if (row >= max_rows) {
                if (row >= max_rows) {
                    
                    Level = 0;
                    onGround = false;
                }

            }
            else {

                char bottom_mid = lvl[row][col_mid];

                if ((bottom_mid == 'q') || (bottom_mid == 'w') || (bottom_mid == 'b')) {
                    onGround = true;
                    gravity = maxgravity;
                    velocityY = 0;
                }

                else
                {
                    onGround = false;
                    player_y = offset_y;
                    velocityY += gravity;
                    if (velocityY > terminal_Velocity)
                        velocityY = terminal_Velocity;

                }
            }
        }

    }
    virtual void lvl4run(RenderWindow& window, char**& lvl) {

        lvl4player_gravity(lvl);
        lvl4moveLeft(window, lvl);
        lvl4moveright(lvl);
        jump();
    }
};



