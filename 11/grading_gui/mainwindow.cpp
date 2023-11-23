#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calculatePushButton, &QPushButton::clicked, this, &MainWindow::caculateGrade);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::caculateGrade()
{
    int n = ui->spinBoxN->value(),
        g = ui->spinBoxG->value(),
        p = ui->spinBoxP->value(),
        exam = ui->spinBoxE->value();
    int weeklyGrade = score_from_weekly_exercises(n, g);
    int projectGrade = score_from_projects(p);
    int totalGrade = calculate_total_grade(n, g, p, exam);
    ui->textBrowser->setText("W-Score: " + QString::fromStdString(std::to_string(weeklyGrade))
                             + "\nP-Score: " + QString::fromStdString(std::to_string(projectGrade))
                             + "\nTotal grade: " + QString::fromStdString(std::to_string(totalGrade)));

}




