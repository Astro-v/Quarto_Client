#ifndef __CONSTANT_HPP__
#define __CONSTANT_HPP__

/*---- LIBRARY ----*/
#include <iostream>

/*---- LIBRARY SFML ----*/

/*---- LOCAL FILE ----*/

/*---- GAME ----*/
#define NUMBER_ROW 4
#define NUMBER_COLUMN 4
#define NUMBER_PIECES (NUMBER_ROW*NUMBER_COLUMN)

/*---- HOME PAGE ----*/
#define HEIGHT_HOME_PAGE 600
#define WIDTH_HOME_PAGE 600
#define HEIGHT_BUTTON 100
#define WIDTH_BUTTON 500
#define POS_BUTTON_X 50
#define POS_BUTTON_Y 300

enum TypeGame{
    NO_GAME, QUARTO
};

/*---- WINDOW ----*/
#define HEIGHT_SCORE 200    // px
#define HEIGHT_PLATEAU 600  // px
#define WIDTH_PLATEAU 600   // px
#define HEIGHT 800          // px
#define WIDTH 1200          // px
#define HEIGHT_PIECE 100    // px
#define WIDTH_PIECE 100     // px
#define SPACE 40            // px


/*---- SERVER ----*/
#define SERVER_PORT 5500	
#define SERVER_ADRESS "90.39.145.229" // IP adress of the server

/*---- STATUS ----*/
enum Status{
    PLAYER_1_PICK, PLAYER_2_PLACE, PLAYER_2_PICK, PLAYER_1_PLACE, PAUSE
};
#define NONE -1

/*---- TO RECEIVE ----*/
enum TypeReceive{
    CONNECT_SERVER, GAME_SERVER, WIN_P1, WIN_P2, NOTHING
};

struct ToReceive{
    Status status;
    int posX[NUMBER_PIECES];
    int posY[NUMBER_PIECES];
    bool used[NUMBER_PIECES];
    int pick;
};

/*---- TO SEND ----*/
enum TypeSend{
    CONNECT_CLIENT, GAME_CLIENT, LEAVE
};

struct ToSend{
    int posX;
    int posY;
};

#endif // __CONSTANT_HPP__