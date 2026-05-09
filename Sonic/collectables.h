


#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"animations.h"

using namespace sf;
using namespace std;
class speacialability {
private:
    Texture abilityTexture;
    Sprite abilitysprite;
    int abilitynum = 0;
    Animation** abilityanimate;
    Clock frameClock;
    int time = 0;

public:

    float** abilityarray = nullptr;

    speacialability(int numberofability) {
        abilitynum = numberofability;
        abilityarray = new float* [numberofability];
        for (int x = 0; x < numberofability; x++) {
            abilityarray[x] = new float[2];
        }


        abilityTexture.loadFromFile("Data/ab.png");
        abilityanimate = new Animation * [numberofability];
        for (int i = 0; i < numberofability; i++) {
            abilityanimate[i] = new Animation(32, 16, 8, 0.2f); // frame size, count, speed
            abilityanimate[i]->setex(abilityTexture);
            abilityanimate[i]->setScale(2.f, 2.f); // scale up if needed
        }



    }

    void drawability(RenderWindow& window, float& cam_offset) {
        float deltaTime = frameClock.restart().asSeconds(); // Time since last frame
        for (int i = 0; i < abilitynum; i++) {
            abilityanimate[i]->animate(deltaTime);
            abilityanimate[i]->setPosition(abilityarray[i][0], abilityarray[i][1], cam_offset);
            abilityanimate[i]->draw(window);
        }

    }

};
class HP {
private:
    Texture hpTexture;
    Sprite hpsprite;
    int hpnum = 0;


public:

    float** hparray = nullptr;

    HP(int numberofhp) {
        hpnum = numberofhp;
        hparray = new float* [numberofhp];
        for (int x = 0; x < numberofhp; x++) {
            hparray[x] = new float[2];
        }


        hpTexture.loadFromFile("Data/hp.png");
        hpsprite.setTexture(hpTexture);
        hpsprite.setScale(2, 2);



    }

    void drawhp(RenderWindow& window, float& cam_offset) {
        for (int i = 0; i < hpnum; i++) {

            hpsprite.setPosition(hparray[i][0] - cam_offset, hparray[i][1]);

            window.draw(hpsprite);
        }

    }

};
class ring {
private:
    Clock frameClock;
    int time = 0;

public:
    float ring_x;
    float ring_y;
    Texture ringTexture;
    Sprite ringsprite;
    Animation* ringanimate;
    ring() {
        time = 0;
        ringTexture.loadFromFile("Data/ring.png");
        if (!ringTexture.loadFromFile("Data/ring.png")) {
            std::cout << "Failed to load ring texture!" << std::endl;
        }


        ringanimate = new Animation(16, 16, 4, 0.1f);
        ringanimate->setScale(3, 3);
    }
    void drawring(RenderWindow& window, float& cam_offset) {
        ringanimate->setex(ringTexture);
        float deltaTime = frameClock.restart().asSeconds(); 
        ringanimate->animate(deltaTime); 
        ringanimate->setPosition(ring_x, ring_y, cam_offset);
        ringanimate->draw(window);
    }

};

class collectables {
public:
    ring* Rings;
    int Obsnum = 0;;
    int level = 0;
    int numberofrings;
    int ringscollected = 0;
    int numberofability;
    int numberofhp;
    speacialability* ability;
    HP* hp;

public:
    collectables(int level) {
        this->level = level;
        if (level == 1) {
            numberofhp = 1;
            numberofability = 1;
            numberofrings = 20;
            Rings = new ring[numberofrings];
            ability = new speacialability(numberofability);
            hp = new HP(numberofhp);
        }
        else if (level == 2) {
            numberofhp = 3;
            numberofability = 1;
            numberofrings = 40;
            Rings = new ring[numberofrings];
            ability = new speacialability(numberofability);
            hp = new HP(numberofhp);
        }
        else if (level == 3) {
            numberofhp = 2;
            numberofability = 2;
            numberofrings = 60;
            Rings = new ring[numberofrings];
            ability = new speacialability(numberofability);
            hp = new HP(numberofhp);
        }
    };
    void define_rings() {
        if (level == 1) {
            Rings[0].ring_x = 9 * 64;
            Rings[0].ring_y = 9 * 64;
            Rings[1].ring_x = 10 * 64;
            Rings[1].ring_y = 9 * 64;
            Rings[2].ring_x = 15 * 64;
            Rings[2].ring_y = 7 * 64;
            Rings[3].ring_x = 16 * 64;
            Rings[3].ring_y = 7 * 64;
            Rings[4].ring_x = 17 * 64;
            Rings[4].ring_y = 7 * 64;
            Rings[5].ring_x = 44 * 64;
            Rings[5].ring_y = 6 * 64;
            Rings[6].ring_x = 45 * 64;
            Rings[6].ring_y = 6 * 64;
            Rings[7].ring_x = 46 * 64;
            Rings[7].ring_y = 6 * 64;
            Rings[8].ring_x = 71 * 64;
            Rings[8].ring_y = 7 * 64;
            Rings[9].ring_x = 72 * 64;
            Rings[9].ring_y = 7 * 64;
            Rings[10].ring_x = 73 * 64;
            Rings[10].ring_y = 7 * 64;
            Rings[11].ring_x = 127 * 64;
            Rings[11].ring_y = 4 * 64;
            Rings[12].ring_x = 128 * 64;
            Rings[12].ring_y = 4 * 64;
            Rings[13].ring_x = 129 * 64;
            Rings[13].ring_y = 4 * 64;
            Rings[14].ring_x = 155 * 64;
            Rings[14].ring_y = 9 * 64;
            Rings[15].ring_x = 156 * 64;
            Rings[15].ring_y = 9 * 64;
            Rings[16].ring_x = 163 * 64;
            Rings[16].ring_y = 9 * 64;
            Rings[17].ring_x = 164 * 64;
            Rings[17].ring_y = 9 * 64;
            Rings[18].ring_x = 179 * 64;
            Rings[18].ring_y = 4 * 64;
            Rings[19].ring_x = 185 * 64;
            Rings[19].ring_y = 4 * 64;
        }
        else if (level == 2) {
            Rings[0].ring_x = 22 * 64;
            Rings[0].ring_y = 6 * 64;
            Rings[1].ring_x = 23 * 64;
            Rings[1].ring_y = 6 * 64;
            Rings[2].ring_x = 24 * 64;
            Rings[2].ring_y = 6 * 64;
            Rings[3].ring_x = 25 * 64;
            Rings[3].ring_y = 6 * 64;
            Rings[4].ring_x = 26 * 64;
            Rings[4].ring_y = 6 * 64;
            Rings[5].ring_x = 23 * 64;
            Rings[5].ring_y = 5 * 64;
            Rings[6].ring_x = 24 * 64;
            Rings[6].ring_y = 5 * 64;
            Rings[7].ring_x = 25 * 64;
            Rings[7].ring_y = 5 * 64;
            Rings[8].ring_x = 24 * 64;
            Rings[8].ring_y = 4 * 64;
            Rings[9].ring_x = 50 * 64;
            Rings[9].ring_y = 3 * 64;
            Rings[10].ring_x = 51 * 64;
            Rings[10].ring_y = 3 * 64;
            Rings[11].ring_x = 52 * 64;
            Rings[11].ring_y = 3 * 64;
            Rings[12].ring_x = 51 * 64;
            Rings[12].ring_y = 2 * 64;
            Rings[13].ring_x = 108 * 64;
            Rings[13].ring_y = 9 * 64;
            Rings[14].ring_x = 108 * 64;
            Rings[14].ring_y = 8 * 64;
            Rings[15].ring_x = 108 * 64;
            Rings[15].ring_y = 7 * 64;
            Rings[16].ring_x = 108 * 64;
            Rings[16].ring_y = 6 * 64;
            Rings[17].ring_x = 108 * 64;
            Rings[17].ring_y = 5 * 64;
            Rings[18].ring_x = 129 * 64;
            Rings[18].ring_y = 4 * 64;
            Rings[19].ring_x = 130 * 64;
            Rings[19].ring_y = 4 * 64;
            Rings[20].ring_x = 131 * 64;
            Rings[20].ring_y = 4 * 64;
            Rings[21].ring_x = 132 * 64;
            Rings[21].ring_y = 4 * 64;
            Rings[22].ring_x = 133 * 64;
            Rings[22].ring_y = 4 * 64;
            Rings[23].ring_x = 131 * 64;
            Rings[23].ring_y = 5 * 64;
            Rings[24].ring_x = 131 * 64;
            Rings[24].ring_y = 6 * 64;
            Rings[25].ring_x = 131 * 64;
            Rings[25].ring_y = 7 * 64;
            Rings[26].ring_x = 131 * 64;
            Rings[26].ring_y = 8 * 64;
            Rings[27].ring_x = 155 * 64;
            Rings[27].ring_y = 8 * 64;
            Rings[28].ring_x = 156 * 64;
            Rings[28].ring_y = 8 * 64;
            Rings[29].ring_x = 156 * 64;
            Rings[29].ring_y = 7 * 64;
            Rings[30].ring_x = 157 * 64;
            Rings[30].ring_y = 8 * 64;
            Rings[31].ring_x = 180 * 64;
            Rings[31].ring_y = 10 * 64;
            Rings[32].ring_x = 180 * 64;
            Rings[32].ring_y = 11 * 64;
            Rings[33].ring_x = 232 * 64;
            Rings[33].ring_y = 4 * 64;
            Rings[34].ring_x = 233 * 64;
            Rings[34].ring_y = 4 * 64;
            Rings[35].ring_x = 234 * 64;
            Rings[35].ring_y = 4 * 64;
            Rings[36].ring_x = 237 * 64;
            Rings[36].ring_y = 5 * 64;
            Rings[37].ring_x = 238 * 64;
            Rings[37].ring_y = 5 * 64;
            Rings[38].ring_x = 239 * 64;
            Rings[38].ring_y = 5 * 64;
            Rings[39].ring_x = 238 * 64;
            Rings[39].ring_y = 4 * 64;

        }
        else if (level == 3) {
            Rings[0].ring_x = 30 * 64;
            Rings[0].ring_y = 4 * 64;
            Rings[1].ring_x = 31 * 64;
            Rings[1].ring_y = 4 * 64;
            Rings[2].ring_x = 32 * 64;
            Rings[2].ring_y = 4 * 64;
            Rings[3].ring_x = 33 * 64;
            Rings[3].ring_y = 4 * 64;
            Rings[4].ring_x = 34 * 64;
            Rings[4].ring_y = 4 * 64;
            Rings[5].ring_x = 31 * 64;
            Rings[5].ring_y = 3 * 64;
            Rings[6].ring_x = 32 * 64;
            Rings[6].ring_y = 3 * 64;
            Rings[7].ring_x = 33 * 64;
            Rings[7].ring_y = 3 * 64;
            Rings[8].ring_x = 32 * 64;
            Rings[8].ring_y = 2 * 64;
            Rings[9].ring_x = 50 * 64;
            Rings[9].ring_y = 3 * 64;
            Rings[10].ring_x = 51 * 64;
            Rings[10].ring_y = 3 * 64;
            Rings[11].ring_x = 52 * 64;
            Rings[11].ring_y = 3 * 64;
            Rings[12].ring_x = 51 * 64;
            Rings[12].ring_y = 2 * 64;
            Rings[13].ring_x = 73 * 64;
            Rings[13].ring_y = 5 * 64;
            Rings[14].ring_x = 74 * 64;
            Rings[14].ring_y = 5 * 64;
            Rings[15].ring_x = 75 * 64;
            Rings[15].ring_y = 5 * 64;
            Rings[16].ring_x = 76 * 64;
            Rings[16].ring_y = 5 * 64;
            Rings[17].ring_x = 77 * 64;
            Rings[17].ring_y = 5 * 64;
            Rings[18].ring_x = 74 * 64;
            Rings[18].ring_y = 4 * 64;
            Rings[19].ring_x = 75 * 64;
            Rings[19].ring_y = 4 * 64;
            Rings[20].ring_x = 76 * 64;
            Rings[20].ring_y = 4 * 64;
            Rings[21].ring_x = 75 * 64;
            Rings[21].ring_y = 3 * 64;
            Rings[22].ring_x = 74 * 64;
            Rings[22].ring_y = 6 * 64;
            Rings[23].ring_x = 75 * 64;
            Rings[23].ring_y = 6 * 64;
            Rings[24].ring_x = 76 * 64;
            Rings[24].ring_y = 6 * 64;
            Rings[25].ring_x = 75 * 64;
            Rings[25].ring_y = 7 * 64;
            Rings[26].ring_x = 115 * 64;
            Rings[26].ring_y = 5 * 64;
            Rings[27].ring_x = 116 * 64;
            Rings[27].ring_y = 5 * 64;
            Rings[28].ring_x = 117 * 64;
            Rings[28].ring_y = 5 * 64;
            Rings[29].ring_x = 118 * 64;
            Rings[29].ring_y = 5 * 64;
            Rings[30].ring_x = 130 * 64;
            Rings[30].ring_y = 8 * 64;
            Rings[31].ring_x = 131 * 64;
            Rings[31].ring_y = 8 * 64;
            Rings[32].ring_x = 130 * 64;
            Rings[32].ring_y = 7 * 64;
            Rings[33].ring_x = 131 * 64;
            Rings[33].ring_y = 7 * 64;
            Rings[34].ring_x = 175 * 64;
            Rings[34].ring_y = 2 * 64;
            Rings[35].ring_x = 176 * 64;
            Rings[35].ring_y = 2 * 64;
            Rings[36].ring_x = 177 * 64;
            Rings[36].ring_y = 2 * 64;
            Rings[37].ring_x = 187 * 64;
            Rings[37].ring_y = 3 * 64;
            Rings[38].ring_x = 188 * 64;
            Rings[38].ring_y = 3 * 64;
            Rings[39].ring_x = 189 * 64;
            Rings[39].ring_y = 3 * 64;
            Rings[40].ring_x = 190 * 64;
            Rings[40].ring_y = 3 * 64;
            Rings[41].ring_x = 215 * 64;
            Rings[41].ring_y = 3 * 64;
            Rings[42].ring_x = 216 * 64;
            Rings[42].ring_y = 3 * 64;
            Rings[43].ring_x = 217 * 64;
            Rings[43].ring_y = 3 * 64;
            Rings[44].ring_x = 218 * 64;
            Rings[44].ring_y = 3 * 64;
            Rings[45].ring_x = 229 * 64;
            Rings[45].ring_y = 3 * 64;
            Rings[46].ring_x = 230 * 64;
            Rings[46].ring_y = 3 * 64;
            Rings[47].ring_x = 231 * 64;
            Rings[47].ring_y = 3 * 64;
            Rings[48].ring_x = 232 * 64;
            Rings[48].ring_y = 3 * 64;
            Rings[49].ring_x = 243 * 64;
            Rings[49].ring_y = 3 * 64;
            Rings[50].ring_x = 244 * 64;
            Rings[50].ring_y = 3 * 64;
            Rings[51].ring_x = 245 * 64;
            Rings[51].ring_y = 3 * 64;
            Rings[52].ring_x = 249 * 64;
            Rings[52].ring_y = 4 * 64;
            Rings[53].ring_x = 249 * 64;
            Rings[53].ring_y = 5 * 64;
            Rings[54].ring_x = 250 * 64;
            Rings[54].ring_y = 5 * 64;
            Rings[55].ring_x = 250 * 64;
            Rings[55].ring_y = 4 * 64;
            Rings[56].ring_x = 255 * 64;
            Rings[56].ring_y = 6 * 64;
            Rings[57].ring_x = 256 * 64;
            Rings[57].ring_y = 6 * 64;
            Rings[58].ring_x = 255 * 64;
            Rings[58].ring_y = 5 * 64;
            Rings[59].ring_x = 256 * 64;
            Rings[59].ring_y = 5 * 64;

        }
    }
    void defineability() {
        if (level == 1) {
            ability->abilityarray[0][0] = 139 * 64;
            ability->abilityarray[0][1] = (9 * 64) - 20;
        }
        else if (level == 2) {
            ability->abilityarray[0][0] = 178 * 64;
            ability->abilityarray[0][1] = (11 * 64) - 20;
        }
    }
    void definehp() {
        if (level == 1) {
            hp->hparray[0][0] = 73 * 64;
            hp->hparray[0][1] = (5 * 64) - 20;
        }
        else if (level == 2) {
            hp->hparray[0][0] = 72 * 64;
            hp->hparray[0][1] = (11 * 64) - 20;
            hp->hparray[1][0] = 236 * 64;
            hp->hparray[1][1] = (11 * 64) - 20;
            hp->hparray[2][0] = 10 * 64;
            hp->hparray[2][1] = (12 * 64) - 20;
        }
    }
    void run(RenderWindow& window, float& cam_offset) {
        for (int i = 0; i < numberofrings; i++) {

            Rings[i].drawring(window, cam_offset);
        }
        ability->drawability(window, cam_offset);
        hp->drawhp(window, cam_offset);
    }
};


