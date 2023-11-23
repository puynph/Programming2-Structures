#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closePushButton);
    connect(ui->countButton, &QPushButton::clicked, this, &MainWindow::calculateBMI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closePushButton()
{
    this->close();
}

void MainWindow::calculateBMI()
{
    QString qtWeight = ui->weightLineEdit->text();
    QString qtHeight = ui->heightLineEdit->text();
    if (qtWeight.isEmpty() or qtHeight.isEmpty() or qtHeight.toFloat() == 0)
    {
        ui->resultLabel->setText("Cannot count.");
        ui->infoTextBrowser->setText("");
        return;
    }
    // cast to integer
    float weight = qtWeight.toFloat();
    float height = qtHeight.toFloat()/100;
    float bmi = weight/(height*height);
    ui->resultLabel->setText(QString::fromStdString(std::to_string(bmi)));
    infoLabel(bmi);
}

void MainWindow::infoLabel(float bmi)
{
    if (bmi < 18.5)
    {
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if (bmi > 25)
    {
        ui->infoTextBrowser->setText("You are overweight.");
    }
    else
    {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
}

