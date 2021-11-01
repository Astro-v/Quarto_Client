/*
    ################ QUARTO ################
    MICHEL VALENTIN
    -- CLIENT --
    Octobre 2021
    ################ END ################
*/

/*---- LIBRARY ----*/
#include <iostream>

/*---- LIBRARY SFML ----*/

/*---- LOCAL FILE ----*/
#include "constant.hpp"
#include "home_page.hpp"

using namespace std;

int main(){
    HomePage homePage("Didou");
    homePage.mainWindow();
    return 0;
}