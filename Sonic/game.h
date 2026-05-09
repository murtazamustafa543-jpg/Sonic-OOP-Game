#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include"menu.h"
#include<string>
using namespace sf;
using namespace std;
class Game {
private:
    Music lvlMus;
    Texture buzz;
    fstream file;
    Clock buzzclock;
    Event ev;
    Menu* m;
    Sprite buzz1;

    int screen_x = 1200;
    int screen_y = 900;
    int level = 1;

public:
    Game() {
        lvlMus.openFromFile("Data/labrynth.ogg");
        if (!buzz.loadFromFile("Data/game1.jpg")) {
            cout << "Error loading image!" << std::endl;
        }
        lvlMus.setVolume(30);
        lvlMus.play();
        lvlMus.setLoop(true);
        buzz1.setTexture(buzz);
        buzz1.setPosition(0, 0);
        buzz1.setScale(0.4, 0.5);
        buzzclock.restart();
        m = new Menu;


    }
    ~Game() {
        file.close();
    }
    void run() {
        RenderWindow window(VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", Style::Close);
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
        srand(time(0));
        while (window.isOpen()) {

            while (window.pollEvent(ev)) {

                if (ev.type == Event::Closed) {
                    file.open("continue.txt", ios::out);
                    if (!(file.is_open())) {
                        cout << "error opening file" << endl;
                    }
                    file << m->l->level << endl << m->l->player->hpleft << endl << m->l->player->character_switch << endl << m->l->player->player_x << endl << m->l->player->player_y << endl << m->l->player->Pposition_x << endl;
                    file << m->l->player->cam_offset << endl << m->l->collecties->ringscollected << endl << m->l->enemykilled << endl << m->points << endl << m->playername << endl;

                    file.close();
                    window.close();
                }

            }

            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                file.open("continue.txt", ios::out);
                if (!(file.is_open())) {
                    cout << "error opening file" << endl;
                }
                file << m->l->level << endl << m->l->player->hpleft << endl << m->l->player->character_switch << endl << m->l->player->player_x << endl << m->l->player->player_y << endl << m->l->player->Pposition_x << endl;
                file << m->l->player->cam_offset << endl << m->l->collecties->ringscollected << endl << m->l->enemykilled << endl << m->points << endl << m->playername << endl;
                file.close();
                window.close();
            }

            if (buzzclock.getElapsedTime().asSeconds() <= 2) {

                window.clear(); 
                window.draw(buzz1);
                window.display();
            }
            else {

                m->show(window, ev, lvlMus);
                window.display();
            }
        }
    }
};
