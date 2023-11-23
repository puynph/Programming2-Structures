#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , is_first_button_click_(true)
{
    ui->setupUi(this);
    init_map();
    init_timer();
    init_moves();
    init_reset_button();
    init_pause_button();
    init_animate_button();
    init_undo_button();
    init_congratulation_gif();
}

MainWindow::~MainWindow()
{
    delete ui;

    // gif is not deallocated via parent-child mechanism
    delete gif;
}

void MainWindow::init_map()
{
    for (unsigned int row = 0; row < ROWS; row ++)
    {
        for (unsigned int column = 0; column < COLUMS; column ++)
        {
            QPushButton* button = new QPushButton(this);
            Point point;
            point.y = row;
            point.x = column;

            // creates a map containing the position of buttons
            map_.insert({button, point});

            // add colors to buttons
            update_board();
            button->setGeometry(column * MARGIN + VIEW_Y,
                                row * MARGIN + VIEW_X,
                                BUTTON_WIDTH, BUTTON_HEIGHT);
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::handle_move_clicks);
        }
    }

}

void MainWindow::handle_move_clicks()
{
    // get the position of the clicked button
    QPushButton* clicked_button = qobject_cast<QPushButton*>(sender());

    if (is_first_button_click_)
    {
        // if user clicks into empty square, do nothing
        if (gb_.which_slot(map_.at(clicked_button)) == EMPTY)
        {
            return;
        }

        // store the position of first clicked, which is then used
        // as a param for method 'move' of class Gameboard
        first_position_ = map_.at(clicked_button);
        is_first_button_click_ = false;

        // darker color of the button means that it has been clicked only once
        QColor darker_color = clicked_button->palette().color(QPalette::Button).darker(150);

        // get the string of the color for setStyleSheet method
        QString darker_color_string = "background-color: " + darker_color.name();
        clicked_button->setStyleSheet(darker_color_string);
    }

    else
    {
        Point second_position = map_.at(clicked_button);
        if (gb_.move(first_position_, second_position))
        {
            update_board();

            // record previous moves for possible undo action later
            previous_moves_.push_back(std::make_pair(first_position_, second_position));

            // if the block is moved from its initial position
            if (!(first_position_ == second_position))
            {
                // timer starts after user succeeds making first move
                timer_->start(1000);
                moves_made_ ++;
                moves_lcd_->display(moves_made_);      // update moves
            }
            emit_game_over_signal();    // changes UI if the game is completed
        }

        else // warning of illegal move
        {
            QMessageBox::warning(this, "Warning", CANNOT_MOVE);
            update_board();
        }
        is_first_button_click_ = true;
    }
}


void MainWindow::handle_timer()
{
    time_passed_ ++;
    update_LCD_display();
}

void MainWindow::handle_reset_button_clicks()
{
    gb_.set_board_to_orig();
    update_board();
    reset_button_->setEnabled(true); pause_button_->setEnabled(true);
    animate_button_->setEnabled(true); undo_button_->setEnabled(true);

    // handle_timer() slot function is being called continuously
    // even after the timer_ object is stopped or reset
    timer_->stop();
    time_passed_ = 0;
    update_LCD_display();

    moves_made_ = 0;
    moves_lcd_->display(moves_made_);

    // set bg color to default color and delete gif
    this->setStyleSheet("background-color:;");
    gif_label->clear();
}

void MainWindow::handle_pause_button_clicks()
{
    if (timer_->isActive())      // if the user wants to pause
    {
        timer_->stop();

        // The game does not response to key commands
        reset_button_->setEnabled(false);
        pause_button_->setText("Resume");

        // Disable all buttons
        for (auto &button_pair : map_)
        {
            QPushButton* button = button_pair.first;
            button->setEnabled(false);
        }
    }

    else if (time_passed_ != 0)   // if the user wants to resume
    {
        timer_->start(1000);
        reset_button_->setEnabled(true);
        pause_button_->setText("Pause");
        for (auto &button_pair : map_)
        {
            QPushButton* button = button_pair.first;
            button->setEnabled(true);
        }
    }
}

void MainWindow::handle_animate_button_clicks()
{
    handle_reset_button_clicks();    // reset board, moves, and timer to original
    timer_->start(1000);

    reset_button_->setEnabled(false); pause_button_->setEnabled(false);
    animate_button_->setEnabled(false); undo_button_->setEnabled(false);
    delay();       // allows a second interval between each movement of button

    gb_.move({1, 0}, {2, 2});
    // update boards and moves
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 4}, {1, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 4}, {1, 1});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 2}, {0, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 1}, {1, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 0}, {2, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 0}, {1, 3});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 2}, {0, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 3}, {2, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 4}, {1, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 4}, {1, 1});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({3, 4}, {1, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 4}, {3, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 2}, {0, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 2}, {2, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 1}, {1, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 0}, {1, 3});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 0}, {2, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({3, 0}, {1, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 0}, {3, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 2}, {0, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 3}, {2, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 4}, {1, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 4}, {1, 1});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 2}, {0, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 1}, {1, 4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 0}, {1, 3});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({0, 0}, {2, 2});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 3}, {0, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({1, 4}, {1, 0});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    gb_.move({2, 2}, {1,4});
    update_board(); moves_made_ ++; moves_lcd_->display(moves_made_); delay();

    timer_->stop();
    reset_button_->setEnabled(true); pause_button_->setEnabled(true);
    animate_button_->setEnabled(true); undo_button_->setEnabled(true);
}

void MainWindow::handle_undo_button_clicks()
{
    if (previous_moves_.size() > 0)
    {
        // Get the previous move of the object from the vector
        std::pair<Point, Point> previous_move = previous_moves_.back();

        // move the object to the previous position
        gb_.move(previous_move.second, previous_move.first);
        update_board();
        // Remove the current position of the object from the vector
        previous_moves_.pop_back();

        moves_made_ --;
        moves_lcd_->display(moves_made_);

    }
    else
    {
        QMessageBox::warning(this, "Warning", CANNOT_UNDO);
    }
}

void MainWindow::update_board()
{
    for (auto &button_pair : map_)
    {
        QPushButton* button = button_pair.first;
        Point point = button_pair.second;
        Slot_type slot = gb_.which_slot(point);
        switch(slot)
        {
            case GREEN: button->setStyleSheet("background-color: green"); break;
            case RED: button->setStyleSheet("background-color: red"); break;
            case EMPTY: button->setStyleSheet("background-color: white"); break;
            case UNUSED: button->setEnabled(false);
                         button->hide(); break;

        }
    }
}

void MainWindow::init_timer()
{
    timer_ = new QTimer(this);
    timer_lcd_ = new QLCDNumber(this);
    timer_label = new QLabel(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::handle_timer);

    timer_lcd_->setGeometry(130 + VIEW_Y, -55 + VIEW_X,
                            5 + timer_lcd_->width(), CONTROL_BUTTON_HEIGHT);
    timer_lcd_->setDigitCount(5); // for minutes:seconds format

    timer_label->setText("Time used:");
    timer_label->setGeometry(50 + VIEW_Y, -55 + VIEW_X,
                             timer_label->width(), CONTROL_BUTTON_HEIGHT);
}

void MainWindow::init_moves()
{
    moves_lcd_ = new QLCDNumber(this);
    moves_lcd_->display(moves_made_);
    moves_lcd_->setGeometry(420 + VIEW_Y, -55 + VIEW_X, 5 + moves_lcd_->width(), CONTROL_BUTTON_HEIGHT);

    moves_label = new QLabel(this);
    moves_label->setText("Moves made: ");
    moves_label->setGeometry(330 + VIEW_Y, -55 + VIEW_X, moves_label->width(), CONTROL_BUTTON_HEIGHT);
}

void MainWindow::update_LCD_display()
{
    int minutes = time_passed_ / 60;
    int seconds = time_passed_ % 60;

    // timer display label
    // placeholders (%1 and %2) will be replaced with the values of minutes and seconds
    // arg(minutes, 2, 10): 2 specifies that at least two digits are displayed
    // 10 means base 10 is used
    timer_lcd_->display(QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0'))
                        .arg(seconds, 2, 10, QLatin1Char('0')));
}


void MainWindow::init_reset_button()
{
    reset_button_ = new QPushButton(this);
    connect(reset_button_, &QPushButton::clicked, this,
            &MainWindow::handle_reset_button_clicks);

    reset_button_->setText("Reset");
    reset_button_->setGeometry(520 + VIEW_Y, 150 + VIEW_X,
                               BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT);
}

void MainWindow::init_pause_button()
{

    pause_button_ = new QPushButton(this);
    connect(pause_button_, &QPushButton::clicked, this,
            &MainWindow::handle_pause_button_clicks);

    pause_button_->setText("Pause");
    pause_button_->setGeometry(520 + VIEW_Y, 200 + VIEW_X,
                               BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT);
}

void MainWindow::init_animate_button()
{
    animate_button_ = new QPushButton(this);
    connect(animate_button_, &QPushButton::clicked, this,
            &MainWindow::handle_animate_button_clicks);

    animate_button_->setText("Animate");
    animate_button_->setGeometry(520 + VIEW_Y, 250 + VIEW_X,
                                 BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT);
}

void MainWindow::init_undo_button()
{
    undo_button_ = new QPushButton(this);
    connect(undo_button_, &QPushButton::clicked, this,
            &MainWindow::handle_undo_button_clicks);

    undo_button_->setText("Undo");
    undo_button_->setGeometry(520 + VIEW_Y, 300 + VIEW_X,
                              BUTTON_WIDTH, CONTROL_BUTTON_HEIGHT);
}

void MainWindow::init_congratulation_gif()
{
    gif = new QMovie(":/gif/congratulation.gif");
    gif_label = new QLabel(this);
    gif_label->setGeometry(300 + VIEW_Y, 145 + VIEW_X, 200, 200);
}

void MainWindow::emit_game_over_signal()
{
    if (gb_.is_game_over())
    {
        // congratulation gif is shown on UI
        gif_label->setMovie(gif);
        gif->start();
        timer_->stop();
        pause_button_->setEnabled(false);
        animate_button_->setEnabled(false); undo_button_->setEnabled(false);

        if (moves_made_ == 31)
        {
            // background color changes when the player finishes the game with 31 moves
            QPalette pal = this->palette();
            pal.setColor(QPalette::Window, QColor(255, 192, 203));
            this->setAutoFillBackground(true);
            this->setPalette(pal);
            QMessageBox::information(this, "Game Over",
                                     GAME_OVER + "with a minimum amount of moves!\n" + RESET);
        }
        else
        {
            QMessageBox::information(this, "Game Over",
                                     GAME_OVER + "\n" + RESET);
        }

    }

}

void MainWindow::delay()
{
    QTime die_time = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < die_time)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
}



