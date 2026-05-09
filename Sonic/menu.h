#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"level.h"
#include"string.h"

using namespace sf;
using namespace std;
class Menu {
private:
    int volume = 100;
    int filing = 1;
    int pressed = 0;

    Texture opTexture;
    Sprite opSprite;
    Texture menuTexture;
    Sprite menuSprite;
    Font font;
    Text welcome;
    const int num = 4;
    Text menu[4];
    string menulabels[4] = { "New Game", "Options", "Countinue", "Leaderboard" };
    Text options[5];
    string optionlabels[5] = { "+", "-", "labrynth", "Spooky","Patriotic" };
    bool Menuon = true;
    bool optionon = true;
    /* int mouse_x;
     int mouse_y; */
     /*window.draw(menuSprite);*/
    int level = 0;

    Text vol;
    Texture leader;
    Texture ask;
    Sprite askn;
    Sprite leadersprite;

    Texture winTex;
    Sprite sprite_w;
    Clock win_clock;

    char  top[100][2][1000];
    char*** toplayer;
    Text leaderboard; // Set font and size

    Text scores;
    IntRect menuBounds[4] = {
    IntRect(440, 350 + (0 * 80), 300, 60),
    IntRect(490, 350 + (1 * 80), 300, 60),
    IntRect(440, 350 + (2 * 80), 300, 60),
    IntRect(405, 650, 300, 60)

    };
    IntRect optionsBounds[5] = {
   IntRect(400,440, 60, 60),
   IntRect(410, 530, 60, 60),
   IntRect(680, 360, 300, 60),
   IntRect(680, 460, 300, 60),
   IntRect(680, 550, 300, 60)

    };
    fstream file;;
    fstream f;
    fstream filein; ;
    Text name;
    string topplayer[100];
    int topscore[100];
    Text enter;
    Text forexit;
    string leaderscore;
    string topscores;
    int lenght;

    int one=1;

public:
    char playername[1000] = "\0";
    int points = 0;
    
    Level* l;
    Menu() {
        one = 1;
        win_clock.restart();

        forexit.setFont(font);
        forexit.setCharacterSize(30);
        forexit.setFillColor(Color::Yellow);
        forexit.setPosition(200, 705);
        forexit.setString("Enter Space to Go back to Menu");
        file.open("record1.txt", ios::app);
        if (!(file.is_open())) {
            cout << "error opening file" << endl;
        }
        f.open("continue.txt", ios::in);
        if (!(f.is_open())) {
            cout << "error opening file" << endl;
        }
        filein.open("record1.txt", ios::in);
        if (!(filein.is_open())) {
            cout << "error opening file" << endl;
        }

        if (!winTex.loadFromFile("Data/win.jpg")) {
            cout << "Failed to load Win texture!" << endl;
        }



        sprite_w.setTexture(winTex);
        

        sprite_w.setScale(1.5, 1.5);

        enter.setFont(font);
        enter.setString("\n\nPlayer Name :");
        enter.setCharacterSize(50);
        enter.setFillColor(Color::Black);
        enter.setPosition(30, 160);
        name.setFont(font);
        name.setString(playername);
        name.setCharacterSize(40);
        name.setFillColor(Color::Blue);
        name.setPosition(30, 360);
        scores.setFont(font);
        vol.setFont(font);
        vol.setCharacterSize(40);
        vol.setFillColor(Color::Blue);
        vol.setPosition(380, 360);
        scores.setCharacterSize(30);
        scores.setFillColor(Color::Blue);
        scores.setPosition(400, 140);



        leaderboard.setFont(font);
        leaderboard.setCharacterSize(30);
        leaderboard.setFillColor(Color::Black);
        leaderboard.setPosition(100, 100);
        if (!leader.loadFromFile("Data/leader.jpg")) {
            cout << "Error loading image!" << endl;
        }
        if (!font.loadFromFile("Data/ArchivoBlack-Regular.ttf")) {
            cout << "Error loading font!" << endl;
        }
        if (!menuTexture.loadFromFile("Data/menu.png")) {
            cout << "Error loading background texture!" << endl;

        }
        if (!opTexture.loadFromFile("Data/options.png")) {
            cout << "Error loading background texture!" << endl;

        }
        if (!ask.loadFromFile("Data/ask.jpg")) {
            cout << "Error loading image!" << endl;
        }
        askn.setTexture(ask);
        leadersprite.setPosition(0, 0);
        leadersprite.setScale(0.5, 0.5);
        leadersprite.setTexture(leader);
        leadersprite.setPosition(0, 0);
        leadersprite.setScale(0.28, 0.24);
        menuSprite.setTexture(menuTexture);
        menuSprite.setPosition(0, 0);
        menuSprite.setScale(1.9, 2.7);
        opSprite.setTexture(opTexture);
        opSprite.setPosition(0, 0);
        opSprite.setScale(0.85, 0.85);
        Menuon = true;
        optionon = true;
        welcome.setFont(font);
        welcome.setCharacterSize(60);
        welcome.setFillColor(Color::Red);
        welcome.setPosition(210, 120);
        welcome.setString("SONIC THE HEDGEHOG");
        /* l1 = new Level(1);*/
        for (int i = 0; i < 4; i++) {
            menu[i].setFont(font);
            menu[i].setString(menulabels[i]);

            menu[i].setCharacterSize(50);
        }
        menu[0].setPosition(440, 350 + (0 * 80));
        menu[1].setPosition(490, 350 + (1 * 80));
        menu[2].setPosition(440, 350 + (2 * 80));

        menu[3].setPosition(405, 650);
        for (int i = 0; i < 5; i++) {
            options[i].setFont(font);
            options[i].setString(optionlabels[i]);

            options[i].setCharacterSize(40);
        }
        options[0].setPosition(400, 440);
        options[1].setPosition(410, 530);
        options[0].setCharacterSize(50);
        options[1].setCharacterSize(60);
        options[2].setPosition(680, 360);
        options[3].setPosition(680, 460);
        options[4].setPosition(680, 550);

    }
    ~Menu() {
        file.close();
        filein.close();
        f.close();
    }
    void show(RenderWindow& window, Event& ev, Music& lvlMus) {

        int mouse_x = Mouse::getPosition(window).x;
        int mouse_y = Mouse::getPosition(window).y;
        switch (level)
        {

        case 0:

            if (Menuon == true) {
                // Mouse hover effect
                for (int j = 0; j < num; j++) {
                    if (menuBounds[j].contains(mouse_x, mouse_y)) {
                        menu[j].setFillColor(Color::White);
                    }
                    else {
                        menu[j].setFillColor(Color::Cyan);
                    }
                }

                // Mouse click detection
                if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
                    for (int j = 0; j < num; j++) {
                        if (menuBounds[j].contains(mouse_x, mouse_y)) {
                            if (j < 1) {
                                level = 6;
                                window.clear();
                                /*  level = 1;
                                  l = new Level(level);*/
                                Menuon = true;
                            }
                            else if (j == 1) {
                                level = 7;
                            }
                            else if (j == 2) {
                                level = 8;
                                filing = 0;
                            }
                            else if (j == 3) {
                                level = 5;
                                filing = 0;
                                Menuon = true;
                            }
                        }
                    }
                }
            }


            window.draw(menuSprite);
            for (int i = 0; i < num; i++) {
                window.draw(menu[i]);
            }
            window.draw(welcome);
            break;
        case 1:

            l->run(window, ev);
            level = l->level;
            points = l->points;
            if (level == 0) {
                file << points << endl;;
                filing = 0;

            }
            if (level != 1) {

                delete l;

            }
            if (level == 2) {
                l = new Level(2);
                l->player->points = points;
            }
            break;

        case 2:

            l->run(window, ev);
            points = l->points;
            level = l->level;
            if (level == 0) {
                filing = 0;
                file << points << endl;;

            }
            if (level != 2) {
                delete l;

            }
            if (level == 3) {
                l = new Level(3);
                l->player->points = points;
            }

            break;
        case 3:
            l->run(window, ev);
            points = l->points;
            level = l->level;
            if (level == 0) {
                filing = 0;
                file << points << endl;;
            }
            if (level != 3) {
                delete l;

            }
            if (level == 4) {
                l = new Level(4);
                l->player->points = points;
            }
            break;
        case 4:
            l->run(window, ev);
            points = l->points;
            level = l->level;
            if (level == 0) {
                file << points << endl;
                filing = 0;
            }
            if (level != 4) {

                delete l;


            }

            if (level == 9)
            {
                file << points << endl;
                filing = 0;
            }

            break;
        case 5:
            window.draw(leadersprite);


            if (filing == 0) {

                int top = 0;
                string player = "-";
                string scored = "0";
                filein.clear();
                filein.seekg(0);

                while (!filein.eof() && top < 100) {

                    getline(filein, player);
                    getline(filein, scored);

                    topplayer[top] = player;
                    topscore[top] = stoi(scored);
                    player = "-";
                    scored = "0";
                    top++;
                }
                string temp;
                int temp2 = 0;

                for (int i = 0; i < top - 1; i++) {
                    for (int j = 0; j < top - i - 1; j++) {
                        if (topscore[j] < topscore[j + 1]) {

                            temp2 = topscore[j];
                            topscore[j] = topscore[j + 1];
                            topscore[j + 1] = temp2;

                            temp = topplayer[j];
                            topplayer[j] = topplayer[j + 1];
                            topplayer[j + 1] = temp;
                        }
                    }
                }


                topscores = "Score\n\n";
                leaderscore = "LEADERBOARD  \n  Name  \n\n";
                for (int j = 0; j < 10; j++) {
                    leaderscore += to_string(j + 1) + " . " + topplayer[j] + "\n";
                    topscores += to_string(topscore[j]) + "\n";
                }



                filing = 1;
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                level = 0;
            }

            points = 0;
            leaderboard.setString(leaderscore);
            scores.setString(topscores);


            window.draw(scores);
            window.draw(leaderboard);
            window.draw(forexit);

            break;
        case 6:
            window.clear();
            window.draw(askn);
            if (ev.type == sf::Event::TextEntered) {
                if (!pressed) {
                    if (ev.text.unicode == 8) {
                        if (lenght > 0) {
                            lenght--;
                            playername[lenght] = '\0';
                        }
                    }
                    else if (ev.text.unicode >= 32 && ev.text.unicode < 128) {
                        if (lenght < 999) {
                            playername[lenght++] = static_cast<char>(ev.text.unicode);
                            playername[lenght] = '\0';
                        }
                    }
                    pressed = true;
                }
            }

            if (ev.type == sf::Event::KeyReleased) {
                pressed = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                lenght = 0;
                level = 4;
                l = new Level(4);
                file << playername << endl;

            }
            name.setString(playername);
            window.draw(enter);
            window.draw(name);

            break;
        case 7:
            window.draw(opSprite);
            window.draw(forexit);

            vol.setString(to_string(volume));
            window.draw(vol);

            if (optionon == true) {

                for (int j = 0; j < 5; j++) {
                    if (optionsBounds[j].contains(mouse_x, mouse_y)) {
                        options[j].setFillColor(Color::White);
                        if (j == 4) {
                            options[4].setFillColor(Color::Green);
                        }
                    }
                    else {
                        options[j].setFillColor(Color::Red);
                    }
                }


                if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
                    for (int j = 0; j < 5; j++) {
                        if (optionsBounds[j].contains(mouse_x, mouse_y)) {
                            if (j == 0) {
                                volume++;
                                if (volume >= 100) {
                                    volume = 100;
                                }
                                lvlMus.setVolume(volume);
                                optionon = true;
                            }
                            else if (j == 1) {
                                volume--;
                                if (volume <= 0) {
                                    volume = 0;
                                }
                                lvlMus.setVolume(volume);
                                optionon = true;
                            }
                            else if (j == 2) {
                                lvlMus.openFromFile("Data/labrynth.ogg");
                                lvlMus.play();
                                lvlMus.setLoop(true);
                                optionon = true;
                            }
                            else if (j == 3) {
                                lvlMus.openFromFile("Data/magical_journey.ogg");
                                lvlMus.play();
                                lvlMus.setLoop(true);
                                optionon = true;
                            }
                            else if (j == 4) {
                                lvlMus.openFromFile("Data/patriotic.mp3");
                                lvlMus.play();
                                lvlMus.setLoop(true);
                                optionon = true;
                            }
                        }
                    }
                }
            }



            for (int i = 0; i < 5; i++) {
                window.draw(options[i]);
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                level = 0;
            }
            break;
        case 8:
            if (filing == 0) {

                string level2;
                string hp;
                string character;
                string x;
                string y;
                string px;
                string cam;
                string ring;
                string killed;
                string point;
                string name;

                f.clear();
                f.seekg(0);



                getline(f, level2);
                getline(f, hp);
                getline(f, character);
                getline(f, x);
                getline(f, y);
                getline(f, px);
                getline(f, cam);
                getline(f, ring);
                getline(f, killed);
                getline(f, point);
                getline(f, name);

                int level1 = stoi(level2);
                
                l = new Level(level1);
                l->player->hpleft = stoi(hp);
                l->player->player_x = stoi(x);
                l->player->character_switch = stoi(character);
                l->player->player_x = stoi(y);
                l->player->Pposition_x = stoi(px);
                l->player->cam_offset = stoi(cam);
                l->collecties->ringscollected = stoi(ring);
                l->points = stoi(point);
                l->enemykilled = stoi(killed);


                this->level = level1;



            }
            break;

        case 9:
            if (one == 1)
            {
                win_clock.restart();
                one = 0;
            }
            window.clear();
            if (win_clock.getElapsedTime().asSeconds() < 7)
            {
                window.draw(sprite_w);
            }
            else
            {
                level = 0;
            }

            break;


        }




    }
};