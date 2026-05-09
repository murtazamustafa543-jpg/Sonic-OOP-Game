#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;
class walls {

private:
    Texture wallTex1;
    Texture wallTex2;
    Texture wallTex3;
    int lev = 0;


public:
    char** lvl;
    Sprite wallSprite1;
    Sprite wallSprite2;
    Sprite wallSprite3;
    int height_wall = 14;
    int width_wall = 200;

    float brick_pos_x;
    float brick_pos_y;
    walls(int level)
    {
        lev = level;
        if (level == 1) {
            wallTex1.loadFromFile("Data/brick1.png");
            wallSprite1.setTexture(wallTex1);

            wallTex2.loadFromFile("Data/brick2.png");
            wallSprite2.setTexture(wallTex2);

            wallTex3.loadFromFile("Data/brick3.png");
            wallSprite3.setTexture(wallTex3);
            lvl = NULL;

            brick_pos_x = 0;
            brick_pos_y = 0;
            if (level == 1) {
                width_wall = 200;

            }
            lvl = new char* [height_wall];
            for (int i = 0; i < height_wall; i++)
            {

                lvl[i] = new char[width_wall] {'\0'};
            }
        }

        else if (level == 2) {
            wallTex1.loadFromFile("Data/ice1.png");
            wallSprite1.setTexture(wallTex1);
            wallSprite1.setScale(0.23, 0.24);


            wallTex2.loadFromFile("Data/ice2.png");
            wallSprite2.setTexture(wallTex2);
            wallSprite2.setScale(0.47, 0.47);

            wallTex3.loadFromFile("Data/ice3.png");
            wallSprite3.setTexture(wallTex3);
            wallSprite3.setScale(0.6, 0.65);
            lvl = NULL;




            if (level == 2) {
                width_wall = 250;

            }

            lvl = new char* [height_wall];
            for (int i = 0; i < height_wall; i++)
            {

                lvl[i] = new char[width_wall] {'\0'};
            }
        }
        else if (level == 3) {



            wallTex2.loadFromFile("Data/lvl3_brick1.png");
            wallSprite2.setTexture(wallTex2);
            wallSprite2.setScale(0.09, 0.15);


            wallTex1.loadFromFile("Data/lvl3_brick2.jpg");
            wallSprite1.setTexture(wallTex1);
            wallSprite1.setScale(0.0525, 0.0525);

            wallTex3.loadFromFile("Data/lvl3_brick3.png");
            wallSprite3.setTexture(wallTex3);
            wallSprite3.setScale(0.085, 0.11);
            lvl = NULL;

            brick_pos_x = 0;
            brick_pos_y = 0;

            if (level == 3) {
                width_wall = 300;

            }


            lvl = new char* [height_wall];
            for (int i = 0; i < height_wall; i++)
            {

                lvl[i] = new char[width_wall] {'\0'};
            }

        }
        else if (level == 4) {
            wallTex2.loadFromFile("Data/lvl3_brick1.png");
            wallSprite2.setTexture(wallTex2);
            wallSprite2.setScale(0.09, 0.15);
            lvl = NULL;





            width_wall = 19;

            lvl = new char* [height_wall];
            for (int i = 0; i < height_wall; i++)
            {

                lvl[i] = new char[width_wall] {'\0'};
            }
        }


    }






    void display_level(RenderWindow& window, float& cam_offset)
    {
        if (lev == 4) {
            cam_offset = 0;
        }
        for (int i = 0; i < height_wall; i++) {
            for (int j = 0; j < width_wall; j++) {

                brick_pos_x = j * 64 - cam_offset;
                brick_pos_y = i * 64;

                if (lvl[i][j] == 'w')
                {
                    wallSprite1.setPosition(brick_pos_x, brick_pos_y);
                    window.draw(wallSprite1);
                }
                if (lvl[i][j] == 'q')
                {
                    wallSprite2.setPosition(brick_pos_x, brick_pos_y);
                    wallSprite2.setColor(Color::White);
                    window.draw(wallSprite2);
                }
                if (lvl[i][j] == 'b')
                {
                    wallSprite3.setPosition(brick_pos_x, brick_pos_y);
                    window.draw(wallSprite3);
                }
            }
        }
    }

    ~walls()
    {
        for (int i = 0; i < height_wall; i++) {
            delete[] lvl[i];
        }
        delete[] lvl;


    }
};
class Spike {
private:
    Texture spikeTexture;
    Sprite spikesprite;
    int spikenum = 0;

public:

    float** spikearray = nullptr;

    Spike(int numberofspikes) {
        spikenum = numberofspikes;
        spikearray = new float* [numberofspikes];
        for (int x = 0; x < numberofspikes; x++) {
            spikearray[x] = new float[2];
        }


        spikeTexture.loadFromFile("Data/spike.png");
        spikesprite.setTexture(spikeTexture);
        spikesprite.setScale(1, 1);



    }

    void drawspike(RenderWindow& window, float& cam_offset) {

        for (int i = 0; i < spikenum; i++) {


            spikesprite.setPosition(spikearray[i][0] - cam_offset, spikearray[i][1]);

            window.draw(spikesprite);
        }


    }

};
class Crystal {
private:
    Texture crystalTexture;
    Sprite crystalsprite;
    int crystalnum = 0;

public:

    float** crystalarray = nullptr;

    Crystal(int numberofcrystals) {
        crystalnum = numberofcrystals;
        crystalarray = new float* [numberofcrystals];
        for (int x = 0; x < numberofcrystals; x++) {
            crystalarray[x] = new float[2];
        }

        crystalTexture.loadFromFile("Data/crystal.png");
        crystalsprite.setTexture(crystalTexture);

        crystalsprite.setScale(1.1, 1.3);
    }

    void drawcrystal(RenderWindow& window, float& cam_offset) {

        for (int i = 0; i < crystalnum; i++) {


            crystalsprite.setPosition(crystalarray[i][0] - cam_offset, crystalarray[i][1]);

            window.draw(crystalsprite);
        }

    }

};

class Obstacle {
private:

    int Obsnum = 0;;
    int level = 0;

public:
    Spike* spikes;
    walls* wall;
    Crystal* crystal;
    int numberofspikes;
    int numberofcrystal;
    Obstacle(int& Level)
    {
        level = Level;
        if (level == 1) {
            numberofcrystal = 3;
            numberofspikes = 5;
            spikes = new Spike(numberofspikes);
            wall = new walls(level);
            crystal = new Crystal(numberofcrystal);

        }
        else if (level == 2) {
            numberofcrystal = 5;
            numberofspikes = 8;
            spikes = new Spike(numberofspikes);
            wall = new walls(level);
            crystal = new Crystal(numberofcrystal);

        }
        else if (level == 3) {
            numberofcrystal = 5;
            numberofspikes = 20;
            spikes = new Spike(numberofspikes);
            wall = new walls(level);
            crystal = new Crystal(numberofcrystal);
        }
        else if (level == 4) {
            wall = new walls(level);
        }
    }
    void define_spike() {
        if (level == 1)
        {
            spikes->spikearray[0][0] = 320;

            spikes->spikearray[0][1] = 9 * 64;
            spikes->spikearray[1][0] = 1600;
            spikes->spikearray[1][1] = 5 * 64;
            spikes->spikearray[2][0] = 3648;
            spikes->spikearray[2][1] = 9 * 64;
            spikes->spikearray[3][0] = 9152;
            spikes->spikearray[3][1] = 9 * 64;

            spikes->spikearray[4][0] = 6400;
            spikes->spikearray[4][1] = 5 * 64;





        }
        else if (level == 2)
        {
            spikes->spikearray[0][0] = 25 * 64;

            spikes->spikearray[0][1] = 9 * 64;
            spikes->spikearray[1][0] = 69 * 64;
            spikes->spikearray[1][1] = 12 * 64;
            spikes->spikearray[2][0] = 3648;
            spikes->spikearray[2][1] = 9 * 64;
            spikes->spikearray[3][0] = 8960;
            spikes->spikearray[3][1] = 9 * 64;

            spikes->spikearray[4][0] = 6400;
            spikes->spikearray[4][1] = 7 * 64;
            spikes->spikearray[5][0] = 174 * 64;
            spikes->spikearray[5][1] = 11 * 64;
            spikes->spikearray[6][0] = 204 * 64;
            spikes->spikearray[6][1] = 4 * 64;
            spikes->spikearray[7][0] = 238 * 64;
            spikes->spikearray[7][1] = 11 * 64;
        }
        else if (level == 3)
        {
            spikes->spikearray[0][0] = 16 * 64;

            spikes->spikearray[0][1] = 4 * 64;
            spikes->spikearray[1][0] = 41 * 64;
            spikes->spikearray[1][1] = 5 * 64;
            spikes->spikearray[2][0] = 73 * 64;
            spikes->spikearray[2][1] = 12 * 64;
            spikes->spikearray[3][0] = 77 * 64;
            spikes->spikearray[3][1] = 12 * 64;

            spikes->spikearray[4][0] = 110 * 64;
            spikes->spikearray[4][1] = 3 * 64;
            spikes->spikearray[5][0] = 110 * 64;
            spikes->spikearray[5][1] = 3 * 64;
            spikes->spikearray[6][0] = 118 * 64;
            spikes->spikearray[6][1] = 5 * 64;
            spikes->spikearray[7][0] = 155 * 64;
            spikes->spikearray[7][1] = 12 * 64;
            spikes->spikearray[8][0] = 194 * 64;
            spikes->spikearray[8][1] = 4 * 64;
            spikes->spikearray[9][0] = 225 * 64;
            spikes->spikearray[9][1] = 4 * 64;
            spikes->spikearray[10][0] = 282 * 64;
            spikes->spikearray[10][1] = 10 * 64;
            spikes->spikearray[11][0] = 284 * 64;
            spikes->spikearray[11][1] = 9 * 64;
            spikes->spikearray[12][0] = 286 * 64;
            spikes->spikearray[12][1] = 8 * 64;
            spikes->spikearray[13][0] = 288 * 64;
            spikes->spikearray[13][1] = 7 * 64;
            spikes->spikearray[14][0] = 280 * 64;
            spikes->spikearray[14][1] = 12 * 64;
            spikes->spikearray[15][0] = 275 * 64;
            spikes->spikearray[15][1] = 12 * 64;
            spikes->spikearray[16][0] = 292 * 64;
            spikes->spikearray[16][1] = 7 * 64;
            spikes->spikearray[17][0] = 294 * 64;
            spikes->spikearray[17][1] = 8 * 64;
            spikes->spikearray[18][0] = 296 * 64;
            spikes->spikearray[18][1] = 9 * 64;
            spikes->spikearray[19][0] = 298 * 64;
            spikes->spikearray[19][1] = 10 * 64;
        }

    }
    void define_crystal() {
        if (level == 1)
        {
            crystal->crystalarray[0][0] = 37 * 64;
            crystal->crystalarray[0][1] = 9 * 64 - 20;

            crystal->crystalarray[1][0] = 84 * 64;
            crystal->crystalarray[1][1] = 5 * 64 - 20;

            crystal->crystalarray[2][0] = 175 * 64;
            crystal->crystalarray[2][1] = 9 * 64 - 20;
        }
        else if (level == 2) {
            crystal->crystalarray[0][0] = 35 * 64;
            crystal->crystalarray[0][1] = 12 * 64 - 20;

            crystal->crystalarray[1][0] = 84 * 64;
            crystal->crystalarray[1][1] = 4 * 64 - 20;

            crystal->crystalarray[2][0] = 113 * 64;
            crystal->crystalarray[2][1] = 12 * 64 - 20;
            crystal->crystalarray[3][0] = 224 * 64;
            crystal->crystalarray[3][1] = 4 * 64 - 20;
            crystal->crystalarray[4][0] = 188 * 64;
            crystal->crystalarray[4][1] = 4 * 64 - 20;

        }
        else if (level == 3) {

            crystal->crystalarray[0][0] = 57 * 64;
            crystal->crystalarray[0][1] = 5 * 64 - 20;

            crystal->crystalarray[1][0] = 124 * 64;
            crystal->crystalarray[1][1] = 7 * 64 - 20;

            crystal->crystalarray[2][0] = 252 * 64;
            crystal->crystalarray[2][1] = 12 * 64 - 20;
            crystal->crystalarray[3][0] = 166 * 64;
            crystal->crystalarray[3][1] = 12 * 64 - 20;
            crystal->crystalarray[4][0] = 222 * 64;
            crystal->crystalarray[4][1] = 4 * 64 - 20;
        }
    }

    void draw_brick()
    {
        if (level == 1) {
            for (int i = 0; i < wall->height_wall; i++)
            {
                wall->lvl[i][0] = 'q';
            }

            for (int i = 0; i < wall->width_wall; i++)
            {
                int brick_generation = rand() % 10 + 1;
                /*if (brick_generation < 2)
                {
                    wall->lvl[1][i] = 'q';
                }*/

                wall->lvl[0][i] = 'q';
                if ((i >= 43 && i <= 47))
                {
                    wall->lvl[7][i] = 'q';
                }
            }

            for (int i = 0; i < wall->width_wall; i++)
            {
                if (i == 11 || i == 12 || i == 44 || i == 45 || i == 46 || i == 110 || i == 111 || i == 170 || i == 171)
                {
                    wall->lvl[10][i] = 's';
                    continue;
                }

                if (i >= 21 && i <= 30)
                {
                    wall->lvl[9][i] = 'b';
                    wall->lvl[8][i] = 'b';
                }

                if (i >= 68 && i <= 109)
                {
                    wall->lvl[8][i] = 'q';
                    int brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                        wall->lvl[9][i] = 'w';
                    else
                        wall->lvl[9][i] = 'b';
                }

                if (i >= 80 && i <= 109)
                {
                    wall->lvl[6][i] = 'q';
                    int brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                        wall->lvl[7][i] = 'w';
                    else
                        wall->lvl[7][i] = 'b';

                    brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                        wall->lvl[8][i] = 'w';
                    else
                        wall->lvl[8][i] = 'b';

                    brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                        wall->lvl[9][i] = 'w';
                    else
                        wall->lvl[9][i] = 'b';
                }

                wall->lvl[6][80] = 'q';
                wall->lvl[7][80] = 'q';
                wall->lvl[8][80] = 'q';
                wall->lvl[9][68] = 'q';

                if ((i >= 114 && i <= 116))
                {
                    wall->lvl[7][i] = 'q';
                }
                if (i >= 120 && i <= 122) {
                    wall->lvl[6][i] = 'q';
                }
                if (i >= 127 && i <= 129) {
                    wall->lvl[5][i] = 'q';
                }
                if (i >= 177 && i <= 193)
                {
                    wall->lvl[10][i] = 'q';
                }

                if (i >= 179 && i <= 191)
                {
                    wall->lvl[9][i] = 'q';
                }

                if (i >= 181 && i <= 189)
                {
                    wall->lvl[8][i] = 'q';
                }

                if (i >= 183 && i <= 187)
                {
                    wall->lvl[7][i] = 'q';
                }

                if (i == 185)
                {
                    wall->lvl[6][i] = 'q';
                }

                if (i == 151 || i == 152 || i == 155 || i == 156 || i == 159 || i == 160 || i == 163 || i == 164)
                {
                    wall->lvl[8][i] = 'b';
                    wall->lvl[9][i] = 'b';
                }

                if (i >= 23 && i <= 28)
                {
                    int brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                    {
                        wall->lvl[6][i] = 'b';
                    }
                    else
                    {
                        wall->lvl[6][i] = 'w';
                    }

                    brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                    {
                        wall->lvl[7][i] = 'b';
                    }
                    else
                    {
                        wall->lvl[7][i] = 'q';
                    }
                }

                wall->lvl[10][i] = 'q';  // Space

                if (i >= 69 && i <= 109)
                {
                    int brick_generation = rand() % 10 + 1;
                    if (brick_generation < 5)
                    {
                        wall->lvl[10][i] = 'b';
                    }
                    else
                    {
                        wall->lvl[10][i] = 'w';
                    }
                }

                int brick_generation = rand() % 10 + 1;
                if (brick_generation < 5)
                {
                    wall->lvl[13][i] = 'b';
                }
                else
                {
                    wall->lvl[13][i] = 'w';
                }

                brick_generation = rand() % 10 + 1;
                if (brick_generation < 5)
                {
                    wall->lvl[12][i] = 'b';
                }
                else
                {
                    wall->lvl[12][i] = 'w';
                }

                brick_generation = rand() % 10 + 1;
                if (brick_generation < 5)
                {
                    wall->lvl[11][i] = 'b';
                }
                else
                {
                    wall->lvl[11][i] = 'w';
                }
            }
        }
        else if (level == 2)
        {
            for (int i = 0; i < wall->height_wall; i++)
            {
                wall->lvl[i][0] = 'w';
                

            }

            for (int i = 0; i < wall->width_wall; i++)
            {

                if (i > 0 && i < 117)
                {
                    if (i > 0 && i < 10)
                    {
                        wall->lvl[4][i] = 'q';
                        wall->lvl[5][i] = 'w';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'b';
                        wall->lvl[12][i] = 'b';
                        wall->lvl[13][i] = 'b';
                    }

                    if (i >= 10 && i < 16)
                    {
                        wall->lvl[4][i] = 'q';
                        wall->lvl[5][i] = 'w';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'b';
                        wall->lvl[12][i] = 'b';

                    }


                    if (i >= 16 && i < 22)
                    {

                        wall->lvl[7][i] = 'q';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'b';
                        wall->lvl[12][i] = 'b';
                    }

                    if (i >= 22 && i < 28)
                    {
                        wall->lvl[10][i] = 'q';
                        wall->lvl[11][i] = 'b';
                        wall->lvl[12][i] = 'b';



                    }

                    if (i > 40 && i < 60)
                    {
                        wall->lvl[10][i] = 'q';

                        if (i > 42 && i < 58)
                        {
                            wall->lvl[7][i] = 'q';
                            if (i > 44 && i < 56)
                            {
                                wall->lvl[4][i] = 'q';


                            }
                        }

                    }

                    if (i > 75 && i < 78)
                    {
                        wall->lvl[12][i] = 'w';
                        wall->lvl[11][i] = 'q';
                    }

                    if (i >= 78 && i < 81)
                    {
                        wall->lvl[9][i] = 'q';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                    }

                    if (i >= 81 && i < 84)
                    {
                        wall->lvl[7][i] = 'q';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                    }

                    if (i >= 84 && i < 87)
                    {
                        wall->lvl[5][i] = 'q';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                    }

                    if (i >= 87 && i < 90)
                    {
                        wall->lvl[3][i] = 'q';
                        wall->lvl[4][i] = 'w';
                        wall->lvl[5][i] = 'w';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                    }

                    if (i > 90 && i < 94)
                    {
                        wall->lvl[4][i] = 'q';
                    }

                    if (i > 94 && i < 98)
                    {
                        wall->lvl[6][i] = 'q';
                    }

                    if (i > 98 && i < 102)
                    {
                        wall->lvl[8][i] = 'q';
                    }

                    if (i > 102 && i < 106)
                    {
                        wall->lvl[10][i] = 'q';
                    }


                    wall->lvl[13][i] = 'w';
                }



                if (i > 117 && i < 152)
                {
                    if ((i > 119 && i < 125) || (i > 128 && i < 134) || (i > 136 && i < 142) || (i > 144 && i < 150))
                    {
                        wall->lvl[10][i] = 'q';
                        wall->lvl[11][i] = 'w';
                    }
                }
                else if (i >= 152 && i < 250)
                {
                    if (i > 154 && i < 158)
                    {
                        wall->lvl[9][i] = 'q';
                    }
                    else if ((i > 159 && i < 163) || (i > 246 && i < 250))
                    {
                        wall->lvl[8][i] = 'q';
                        if (i > 246 && i < 250)
                        {
                            
                            wall->lvl[8][i] = 'q';
                            wall->lvl[9][i] = 'w';
                            wall->lvl[10][i] = 'w';
                            wall->lvl[11][i] = 'w';
                            wall->lvl[12][i] = 'w';
                        }
                    }

                    else if ((i > 164 && i < 168) || (i > 241 && i < 245))
                    {
                        wall->lvl[7][i] = 'q';
                    }

                    else if ((i > 169 && i < 173) || (i > 236 && i < 240))
                    {
                        wall->lvl[6][i] = 'q';
                    }

                    else if ((i > 174 && i < 178) || (i > 231 && i < 235))
                    {
                        wall->lvl[5][i] = 'q';
                    }

                    else if (i > 179 && i < 226)
                    {
                        if (i == 184 || i == 185 || i == 190 || i == 191 || i == 196 || i == 197 || i == 202 || i == 203 || i == 208 || i == 209 || i == 214 || i == 215 || i == 220 || i == 221 || i == 226 || i == 227)
                        {
                            continue;
                        }
                        wall->lvl[5][i] = 'q';
                        wall->lvl[6][i] = 'b';
                        wall->lvl[7][i] = 'b';
                        wall->lvl[8][i] = 'b';
                        wall->lvl[9][i] = 'b';

                    }
                    if (i == 228 || i == 229 || i == 230)
                    {
                        wall->lvl[5][i] = 'q';
                        wall->lvl[6][i] = 'b';
                        wall->lvl[7][i] = 'b';
                        wall->lvl[8][i] = 'b';
                        wall->lvl[9][i] = 'b';
                        
                    }
                    if (i > 183 && i < 224)
                    {
                        continue;
                    }
                    else 
                    {
                        wall->lvl[12][i] = 'w';
                        wall->lvl[13][i] = 'w';
                    }
                }



            }
            }
        else if (level == 3) {

            for (int i = 0; i < wall->width_wall; i++)
            {


                if (i > 0 && i < 70)
                {
                    if (i > 0 && i < 5)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[10][i] = (b1 < 5) ? 'b' : 'q';
                        wall->lvl[11][i] = 'w';
                        b1 = rand() % 10 + 1;
                        wall->lvl[12][i] = (b1 < 5) ? 'b' : 'q';
                    }

                    if (i > 7 && i < 12)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[7][i] = (b1 < 5) ? 'b' : 'q';
                        wall->lvl[8][i] = 'w';
                        b1 = rand() % 10 + 1;
                        wall->lvl[9][i] = (b1 < 5) ? 'b' : 'q';
                    }

                    if (i > 14 && i < 19)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                        wall->lvl[6][i] = 'w';
                        b1 = rand() % 10 + 1;
                        wall->lvl[7][i] = (b1 < 5) ? 'b' : 'q';
                    }

                    if (i > 21 && i < 26)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                        wall->lvl[13][i] = 'w';
                    }

                    if (i > 21 && i < 50)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[6][i] = (b1 < 5) ? 'b' : 'q';

                        b1 = rand() % 10 + 1;
                        wall->lvl[8][i] = (b1 < 5) ? 'b' : 'q';
                        //wall->lvl[10][i] = 'q';
                    }

                    if (i > 53 && i < 65)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[6][i] = (b1 < 5) ? 'b' : 'q';

                        b1 = rand() % 10 + 1;
                        wall->lvl[8][i] = (b1 < 5) ? 'b' : 'q';
                        //wall->lvl[10][i] = 'q';
                    }

                    if (i > 64 && i < 69)
                    {
                        int b1 = rand() % 10 + 1;
                        wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                        wall->lvl[6][i] = 'w';
                        wall->lvl[7][i] = 'w';
                        wall->lvl[8][i] = 'w';
                        wall->lvl[9][i] = 'w';
                        wall->lvl[10][i] = 'w';
                        wall->lvl[11][i] = 'w';
                        wall->lvl[12][i] = 'w';
                        wall->lvl[13][i] = 'w';
                    }

                    if (i >= 21 && i <= 69)
                    {
                        wall->lvl[13][i] = 'q';
                    }






                }

                if (i > 72 && i < 78)
                {
                    wall->lvl[13][i] = 'q';
                }

                if (i > 80 && i < 85)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[12][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[13][i] = 'w';


                }

                if (i > 87 && i < 92)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[10][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[11][i] = 'w';

                }

                if (i > 94 && i < 99)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[8][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[9][i] = 'w';


                }

                if (i > 101 && i < 106)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[6][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[7][i] = 'w';


                }

                if (i > 108 && i < 113)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[4][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[5][i] = 'w';


                }

                if (i > 114 && i < 119)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[6][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[7][i] = 'w';


                }

                if (i > 121 && i < 126)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[8][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[9][i] = 'w';


                }

                if (i > 128 && i < 133)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[10][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[11][i] = 'w';


                }

                if (i > 135 && i < 140)
                {

                    int b1 = rand() % 10 + 1;
                    wall->lvl[12][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[13][i] = 'w';
                }

                if (i > 142 && i < 180)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[13][i] = (b1 < 5) ? 'b' : 'q';
                }

                if ((i > 148 && i < 153) || (i > 271 && i < 276)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[10][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[11][i] = 'w';
                }

                if ((i > 154 && i < 158) || (i > 265 && i < 270)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[9][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[10][i] = 'w';
                }
                else if ((i > 159 && i < 163) || (i > 259 && i < 264)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[8][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[9][i] = 'w';
                }
                else if ((i > 164 && i < 168) || (i > 253 && i < 258)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[7][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[8][i] = 'w';
                }
                else if ((i > 169 && i < 173) || (i > 247 && i < 252)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[6][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[7][i] = 'w';
                }
                else if ((i > 174 && i < 178) || (i > 242 && i < 246)) {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                }

                if (i > 179 && i < 184)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                    wall->lvl[7][i] = 'w';
                    wall->lvl[8][i] = 'w';
                    wall->lvl[9][i] = 'w';
                    wall->lvl[10][i] = 'w';
                    wall->lvl[11][i] = 'w';
                    wall->lvl[12][i] = 'w';
                    wall->lvl[13][i] = 'w';
                }

                if (i > 186 && i < 191)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';

                }

                if (i > 193 && i < 198)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                    wall->lvl[7][i] = 'w';
                    wall->lvl[8][i] = 'w';

                }

                if (i > 200 && i < 205)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                }

                if (i > 207 && i < 212)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                    wall->lvl[7][i] = 'w';
                    wall->lvl[8][i] = 'w';

                }

                if (i > 214 && i < 219)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';

                }

                if (i > 221 && i < 226)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                    wall->lvl[7][i] = 'w';
                    wall->lvl[8][i] = 'w';

                }

                if (i > 228 && i < 233)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';

                }

                if (i > 235 && i < 240)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[5][i] = (b1 < 5) ? 'b' : 'q';
                    wall->lvl[6][i] = 'w';
                    wall->lvl[7][i] = 'w';
                    wall->lvl[8][i] = 'w';
                    wall->lvl[9][i] = 'w';
                    wall->lvl[10][i] = 'w';
                    wall->lvl[11][i] = 'w';
                    wall->lvl[12][i] = 'w';
                    wall->lvl[13][i] = 'w';

                }
                if(i >= 179 && i<=240 )
                {
                    wall->lvl[13][i] = 'q';
                }

                if (i > 239 && i < 300)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[13][i] = (b1 < 5) ? 'b' : 'q';
                }


                if (i > 280 && i < 300)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[11][i] = (b1 < 5) ? 'b' : 'w';
                }

                if (i > 282 && i < 298)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[10][i] = (b1 < 5) ? 'b' : 'w';
                }

                if (i > 284 && i < 296)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[9][i] = (b1 < 5) ? 'b' : 'w';
                }

                if (i > 286 && i < 294)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[8][i] = (b1 < 5) ? 'b' : 'w';
                }

                if (i > 288 && i < 292)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[7][i] = (b1 < 5) ? 'b' : 'w';
                }

                if (i == 290)
                {
                    int b1 = rand() % 10 + 1;
                    wall->lvl[6][i] = (b1 < 5) ? 'b' : 'w';
                }





                
            }




        }
        if (level == 4) {
            for (int i = 0; i < 19; i++)
            {
                wall->lvl[9][i] = 'q';
            }
        }

    }

    void run(RenderWindow& window, float& cam_offset) {
        define_spike();
        define_crystal();
        spikes->drawspike(window, cam_offset);
        wall->display_level(window, cam_offset);
        crystal->drawcrystal(window, cam_offset);
    }
};
