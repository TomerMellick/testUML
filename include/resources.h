#pragma once
#include <string>




namespace Resources
{
    // (T)extures
    const std::string WALL_T = "wall.png";
    const std::string GHOST_T = "ghost.png";
    const std::string GHOSTS_T = "ghosts.png";
    const int GHOST_TS = 32;
    
    const std::string EMPTY_T = "empty.png";
    const std::string PACMAN_GAME_T = "pacman_game.png";
    const int PACMAN_GAME_TS = 32;

    const std::string COOKIE_T = "cookie.png";
    const std::string DOOR_T = "door.png";
    const std::string KEY_T = "key.png";
    const std::string GIFT_SUPER_T = "Gift.png";
    const std::string GIFT_FREEZE_T = "blueGift.png";
    const std::string GIFT_ADD_TIME_T = "greenGift.png";
    const std::string GIFT_ADD_LIFE_T = "pinkGift.png";
    const std::string PLAY_BUTTON_T = "start.png";
    const std::string EXIT_BUTTON_T = "exit.png";
    const std::string EDITOR_BUTTON_T = "editor.png";
    const std::string HELP_BUTTON_T = "help.png";
    const std::string BACKGROUND_T = "scoreBack.png";
    const std::string HELP_SCREEN_T = "helpBack.png";
    const std::string HIGHSCORE_BUTTON_T = "highscore.png";
   
    // (F)onts
    const std::string KARMA_F = "Karma Future.otf";
    const std::string ARCADE_F = "ARCADECLASSIC.TTF";
    
    // (S)ounds
    const std::string SOUNDTRACK_S = "menuSoundTrack.ogg";
    const std::string COOKIE_S = "eatCookie.wav";
    const std::string GIFT_S = "eatGift.wav";
    
    const void *loadResources(std::string path);
}