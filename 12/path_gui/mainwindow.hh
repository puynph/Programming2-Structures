/* Class: MainWindow
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class provides the main user interface and application logic.
 *
 * While other feauture will be mentioned in document.txt, a notable
 * attribute included in this class is a map<QPushButton*, Point>.
 * Not only does this help displaying the buttons but also stores
 * the location of buttons, which is useful when one wants to undo or
 * move the button.
 *
 * */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <QMessageBox>
#include <QLabel>
#include <QTime>
#include <QCoreApplication>
#include <QMovie>
#include <QPalette>
#include <gameboard.hh>
#include <map>
#include <vector>

const QString CANNOT_MOVE = "There is no path between start point and destination point.";
const QString GAME_OVER = "Congratulations! You have completed the game";
const QString RESET = "Press reset to start the game again";
const QString CANNOT_UNDO = "No moves left to undo";

using button_position = std::map<QPushButton*, Point>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handle_move_clicks();
    void handle_timer();
    void handle_reset_button_clicks();
    void handle_pause_button_clicks();
    void handle_animate_button_clicks();
    void handle_undo_button_clicks();

private:
    Ui::MainWindow *ui;

    // Location of the graphics view and scene
    const int VIEW_X = 60;
    const int VIEW_Y = 100;

    // Constants for push buttons
    const int BUTTON_WIDTH = 70;
    const int BUTTON_HEIGHT = 70;
    const int CONTROL_BUTTON_HEIGHT = 40;

    // Space between elements, both horizontally and vertically
    const int MARGIN = 100;

    // Initializes a map of button, of which keys are pointers
    // to the buttons, and payloads are the locations.
    button_position map_;

    // turns true if user first click onto the button
    bool is_first_button_click_;

    // the position of the first-clicked button
    Point first_position_;
    GameBoard gb_ = GameBoard();

    int time_passed_ = 0;
    QTimer* timer_;
    QLCDNumber* timer_lcd_;
    QLabel* timer_label;

    int moves_made_ = 0;
    QLCDNumber* moves_lcd_;
    QLabel* moves_label;

    QPushButton* reset_button_;
    QPushButton* pause_button_;
    QPushButton* animate_button_;
    QPushButton* undo_button_;

    // congratulation gif appears if the user complete the game
    // for visual purpose
    QLabel* gif_label;
    QMovie* gif;

    // vector contains a pair of position of the first and second click
    // this is then used for undo purpose
    std::vector<std::pair<Point, Point>> previous_moves_;

    // Initialized map is displayed as a 5x4 matrix. The colors of
    // the buttons are manipulated by the method 'update board'
    void init_map();

    // Utilizes the method from class Gameboard to assign colors
    // to the corresponding button
    void update_board();

    // Initializes the timer
    void init_timer();

    void init_moves();

    // update time display
    void update_LCD_display();

    // Initialization methods for buttons
    // (for setting the locations of these widgets)
    void init_reset_button();
    void init_pause_button();
    void init_animate_button();
    void init_undo_button();
    void init_congratulation_gif();

    // Changes the UI once the player has completed the game
    void emit_game_over_signal();

    // Delays of 1 second.
    // It works by using the QTime class to create a time value
    // that is 1 second in the future, and then looping
    // until the current time is greater than or equal to that time.
    void delay();
};
#endif // MAINWINDOW_HH
