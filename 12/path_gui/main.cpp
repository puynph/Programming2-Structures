/* Path_gui
 *
 * Desc:
 *   The program consists of class Gameboard and a Graphical User Interface
 * as well as the main program module. This program makes use of Qt implementation
 * to create the interface based on the initial game logic.
 *   User interacts with the interface and use buttons such as reset, pause, ...
 * as with normal game. More detailed features and rules for the game is included
 * in document.txt.
 *   Warning is given in certain situations, for example, illegal move.
 *
 * Name: Uyen Phan
 * Student number: 151372454
 * UserID: cpuyph
 * E-Mail: uyen.phan@tuni.fi
 *
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
