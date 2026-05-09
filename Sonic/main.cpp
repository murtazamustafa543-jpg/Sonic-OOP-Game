#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include "obstacles.h"
#include "collectables.h"
#include "level.h"
#include"player.h"
#include "batBrain.h"
#include"Characters.h"
#include"animations.h"
#include"game.h"
using namespace sf;
using namespace std;
const int screen_x = 1200;
const int screen_y = 900;


int main() {
    Game game;   
    game.run();   
    return 0;    
}





