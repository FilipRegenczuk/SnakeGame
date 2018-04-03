#include "game.h"
#include <QApplication>
Game *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMainMenu(" by M & F ","PLAY");
    return a.exec();
}
