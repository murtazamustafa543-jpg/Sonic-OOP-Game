#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "obstacles.h"
#include "collectables.h"
#include "player.h"
#include "batBrain.h"
#include"Characters.h"
#include"sonic.h"
#include"tails.h"
#include"knuckles.h"
#include "motoBug.h"
#include "crabMeat.h"
#include "beeBot.h"
#include "eggStinger.h"

using namespace sf;

class Level {
private:
    int timeduration;
    Clock leveltime;

public:

    int enemykilled = 0;
    int points = 0;;
    Clock clock_bee;
    Clock clock_crab;
    Font font;

    int height;
    int width;


    int nums;

    //const int 64 = 64;
    int level;
    int ringstocollect;

    Texture bulletTex;

    Texture level1bg;

    Texture batTex;

    Texture beeTex;

    Texture bugTex;

    Texture crabTex;

    Texture spike_eggTex;

    Texture stingerTex;

    Texture blockTex;

    Texture stingerLTex;

    Texture spikeAnimateTex;



    int hp;
    int once = 0;
    float Pprevious_x;
    Sonic* s;
    Tail* t;
    knuckles* k;
    character* player;
    Obstacle* obs;
    collectables* collecties;
    BatBrain* bat;
    Motobug* bug;
    BeeBot* bee;
    CrabMeat* crab;
    EggStinger* stinger;
    Text hpText;
    Text enemyText;
    Text duration;
    Text score;
    Sprite level1prite;
    int timer = 0;
    Level(int level) : height(14)
    {
        this->level = level;

        if (!font.loadFromFile("Data/ArchivoBlack-Regular.ttf")) {
            cout << "Error loading font!" << endl;
        }
        if (level == 1) {
            if (!level1bg.loadFromFile("Data/bg1.png")) {
                cout << "Error loading image!" << endl;
            }
            nums = 5;
            ringstocollect = 20;
            width = 200;
            timeduration = 90;

            t = new Tail(level);
            k = new knuckles(level);
        }
        else if (level == 2) {
            if (!level1bg.loadFromFile("Data/bg2.png")) {
                cout << "Error loading image!" << endl;
            }
            nums = 5;
            ringstocollect = 40;
            width = 250;
            timeduration = 150;
            t = new Tail(level);
            k = new knuckles(level);
        }
        else if (level == 3) {
            if (!level1bg.loadFromFile("Data/lvl3_bg.jpg"))
            {
                cout << "Error loading image!" << endl;
            }
            nums = 5;
            ringstocollect = 60;
            width = 300;
            timeduration = 180;
            t = new Tail(level);
            k = new knuckles(level);


        }
        else if (level == 4) {
            if (!level1bg.loadFromFile("Data/bg4.jpg")) {
                cout << "Error loading image!" << endl;
            }
            width = 20;
            timeduration = 250;
        }

        if (!batTex.loadFromFile("Data/BatBrain.png")) {
            cout << "Failed to load BatBrain texture!" << endl;
        }



        if (!beeTex.loadFromFile("Data/BuzzBomber.png")) {
            cout << "Failed to load BeeBot texture!" << endl;
        }

        if (!bugTex.loadFromFile("Data/motoBug.png")) {
            cout << "Failed to load bug texture!" << endl;
        }

        if (!bulletTex.loadFromFile("Data/bulletBee.png")) {
            cout << "Failed to load bullet  texture!" << endl;
        }

        if (!crabTex.loadFromFile("Data/option2.png")) {
            cout << "Failed to load crabTex texture!" << endl;
        }


        if (!blockTex.loadFromFile("Data/lvl3_brick1.png")) {
            cout << "Failed to load lvl 3 brick 1 texture!" << endl;
        }

        if (!stingerTex.loadFromFile("Data/eggStinger.png")) {
            cout << "Failed to load egg stringer normal texture!" << endl;
        }

        if (!spike_eggTex.loadFromFile("Data/spike_egg.png")) {
            cout << "Failed to load egg stinger spike texture!" << endl;
        }

        if (!stingerLTex.loadFromFile("Data/stringer_left.png")) {
            cout << "Failed to load stinger left texture!" << endl;
        }

        if (!spikeAnimateTex.loadFromFile("Data/spikeAnimation.png")) {
            cout << "Failed to load spikeAnimateTex texture!" << endl;
        }





        level1prite.setTexture(level1bg);
        level1prite.setPosition(0, 0);
        level1prite.setScale(1, 1.5);
        if (level == 3) {
            level1prite.setScale(0.32, 0.4);
        }

        if (level == 2) {
            level1prite.setScale(0.9, 1.2);
        }

        if (level == 4) {
            level1prite.setScale(0.65, 0.65);
        }

        once = 0;
        s = new Sonic(level);

        player = s;
        Pprevious_x = player->Pposition_x;

        hp = 5;



        obs = new Obstacle(level);
        obs->draw_brick();
        if (level != 4) {
            collecties = new collectables(level);
            collecties->define_rings();
            collecties->defineability();
            collecties->definehp();
        }

        if (level == 3)
        {
            bat = new  BatBrain(400, 200, batTex, level);

            bee = new BeeBot(13000, 130, beeTex, bulletTex, obs->wall->lvl, level);

            bug = new Motobug(11000, 770, bugTex, 10770, 11430, level);

            crab = new CrabMeat(15600, 770, crabTex, bulletTex, 15340, 16065, obs->wall->lvl, level);
        }

        else if (level == 2)
        {
            bat = new  BatBrain(400, 200, batTex, level);

            bee = new BeeBot(4000, 600, beeTex, bulletTex, obs->wall->lvl, level);

            bug = new Motobug(11000, 770 - 64, bugTex, 10500, 11430, level);

            crab = new CrabMeat(15000, 770 - 64, crabTex, bulletTex, 14940, 15500, obs->wall->lvl, level);
        }

        else if (level == 4)
        {

            stinger = new EggStinger(blockTex, spike_eggTex, stingerTex, obs->wall->lvl, 900, 100, 4, stingerLTex, spikeAnimateTex);
        }
        else
        {
            bat = new  BatBrain(400, 200, batTex, level);



            bug = new Motobug(4000, 580, bugTex, 3500, 4300, level);


        }



        hpText.setFont(font);
        hpText.setCharacterSize(24);
        hpText.setFillColor(Color::White);
        hpText.setPosition(1000, 20);

        enemyText.setFont(font);
        enemyText.setCharacterSize(24);
        enemyText.setFillColor(Color::White);
        enemyText.setPosition(50, 20);

        duration.setFont(font);

        duration.setCharacterSize(40);
        duration.setFillColor(Color::Yellow);
        duration.setPosition(1030, 60);
        duration.setFont(font);
        score.setFont(font);
        score.setCharacterSize(40);
        score.setFillColor(Color::Yellow);
        score.setPosition(60, 60);



    }
    void run(RenderWindow& window, Event& ev) {
        window.clear();
        if (level == 1) {
            level1prite.setPosition(-player->cam_offset, 0);
        }
        else {
            level1prite.setPosition(0, 0);
        }
        window.draw(level1prite);

        if (level != 4)
        {
            float time_bee = clock_bee.restart().asSeconds();
            float time_crab = clock_crab.restart().asSeconds();
            obs->run(window, player->cam_offset);
            collecties->run(window, player->cam_offset);

            once = player->characterswitch();
            if (player->character_switch == 1) {
                if (once) {
                    player = s;
                    player->hpleft = k->hpleft;
                    player->character_switch = k->character_switch;

                    player->cam_offset = k->cam_offset;
                    player->points = k->points;
                    t->points = k->points;

                    once = 0;
                }

                t->followPlayer(player);
                /* t->drawplayer(window);*/
                k->followPlayer(player);
                /* k->drawplayer(window);*/
                t->followPlayer(player);
                k->followPlayer(player);

                k->offrun(window, player, obs->wall->lvl, *obs);
                t->offrun(window, player, obs->wall->lvl, *obs);
                player->run(obs->wall->lvl, window, *collecties, *obs);



            }
            else if (player->character_switch == 2) {
                if (once) {
                    player = t;
                    player->hpleft = s->hpleft;
                    player->character_switch = s->character_switch;
                    k->character_switch = s->character_switch;
                    player->cam_offset = s->cam_offset;
                    player->points = s->points;
                    k->points = s->points;
                    once = 0;
                }
                s->followPlayer(player);

                k->followPlayer(player);

                s->followPlayer(player);
                k->offrun(window, player, obs->wall->lvl, *obs);
                s->offrun(window, player, obs->wall->lvl, *obs);

                player->run(obs->wall->lvl, window, *collecties, *obs);
            }
            else if (player->character_switch == 3) {
                if (once) {
                    player = k;
                    player->hpleft = t->hpleft;
                    player->character_switch = t->character_switch;
                    player->cam_offset = t->cam_offset;
                    player->points = t->points;
                    s->points = t->points;
                    once = 0;
                }
                s->followPlayer(player);

                t->followPlayer(player);

                t->offrun(window, player, obs->wall->lvl, *obs);
                s->offrun(window, player, obs->wall->lvl, *obs);
                player->run(obs->wall->lvl, window, *collecties, *obs);



            }



            if (level == 1)

            {
                if (!bat->enemy_died())
                {
                    float direction = player->Pposition_x - Pprevious_x;

                    bat->movement(player->player_x, player->player_y, direction, player->hpleft, player);

                    Pprevious_x = player->Pposition_x;

                    bat->collision_check(player, enemykilled);
                    bat->collisionplayer(player);

                    bat->draw(window);
                }


                if (!bug->enemy_died())
                {
                    bug->collision_check(player, enemykilled);
                    bug->collisionplayer(player);
                    bug->movement(player->Pposition_x, player->cam_offset);
                    bug->draw(window);
                }

            }

            else if (level == 2)
            {

                if (!bug->enemy_died())
                {
                    bug->collision_check(player, enemykilled);
                    bug->collisionplayer(player);
                    bug->movement(player->Pposition_x, player->cam_offset);
                    bug->draw(window);
                }

                if (!crab->enemy_died())
                {
                    crab->collision_check(player, enemykilled);
                    crab->collisionplayer(player);
                    crab->movement(player->Pposition_x, player->cam_offset, time_crab);
                    crab->draw(window);
                }

                if (!bee->enemy_died())
                {

                    bee->collision_check(player, enemykilled);
                    bee->collisionplayer(player);
                    bee->movement(time_bee, player->cam_offset);
                    bee->draw(window);
                }

            }


            else if (level == 3)

            {
                if (!bat->enemy_died()) {
                    float direction = player->Pposition_x - Pprevious_x;

                    bat->movement(player->player_x, player->player_y, direction, player->hpleft, player);

                    Pprevious_x = player->Pposition_x;

                    bat->collision_check(player, enemykilled);
                    bat->collisionplayer(player);

                    bat->draw(window);
                }

                if (!bug->enemy_died())
                {
                    bug->collision_check(player, enemykilled);
                    bug->collisionplayer(player);
                    bug->movement(player->Pposition_x, player->cam_offset);
                    bug->draw(window);
                }

                if (!crab->enemy_died())
                {
                    crab->collision_check(player, enemykilled);
                    crab->collisionplayer(player);
                    crab->movement(player->Pposition_x, player->cam_offset, time_crab);
                    crab->draw(window);
                }

                if (!bee->enemy_died())
                {
                    bee->collision_check(player, enemykilled);
                    bee->collisionplayer(player);
                    bee->movement(time_bee, player->cam_offset);
                    bee->draw(window);
                }
            }




            if (player->Level == 0) {
                level = 0;


            }

            if (player->hpleft == 0 || timer >= timeduration)
            {
                level = 0;
            }
            if (level == 1 && collecties->ringscollected == ringstocollect && ((int)(player->Pposition_x + player->hit_box_factor_x + player->Pwidth / 2) / 64) == 199) {
                level = 2;
            }
            if (level == 2 && collecties->ringscollected == ringstocollect && ((int)(player->Pposition_x + player->hit_box_factor_x + player->Pwidth / 2) / 64) == 249) {
                level = 3;
            }
            if (level == 3 && collecties->ringscollected == ringstocollect && ((int)(player->Pposition_x + player->hit_box_factor_x + player->Pwidth / 2) / 64) == 290) {
                level = 4;
            }

            enemyText.setString("Enemies killed: " + to_string(enemykilled));
            window.draw(enemyText);

        }
        else {
            if (player->Level == 0) {
                level = 0;


            }
            if (player->hpleft == 0 || timer >= timeduration)
            {
                level = 0;
            }
            player->lvl4run(window, obs->wall->lvl);

            obs->wall->display_level(window, player->cam_offset);

            if (!stinger->enemy_died())
            {
                stinger->movement(player, obs->wall->lvl);
                stinger->collision_check(player, enemykilled);
                stinger->draw(window);
                stinger->drawHP(window, font);
                hpText.setString("Player lives: " + to_string(player->hpleft));
                window.draw(hpText);
            }
            else 
            {
                level = 9;
            }


        }
        points = getpoints(player);
        hpText.setString("Player lives: " + to_string(player->hpleft));
        window.draw(hpText);
        score.setString("POINTS: " + to_string(player->points));
        window.draw(score);
        timer = leveltime.getElapsedTime().asSeconds();
        int r = timeduration - timer;
        if (r < 0) {
            r = 0;
        }
        int minutes = (r) / 60;
        int seconds = (r) % 60;

        duration.setString(to_string(minutes) + " : " + to_string(seconds) + " s");
        window.draw(duration);
    }
    int getpoints(character* player) {
        return player->points;
    }


};