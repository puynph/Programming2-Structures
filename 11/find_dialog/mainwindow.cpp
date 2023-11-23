#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->closePushButton, &QPushButton::clicked, this, &MainWindow::closePushButton);
    connect(ui->findPushButton, &QPushButton::clicked, this, &MainWindow::on_fileLineEdit_editingFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closePushButton()
{
    this->close();
}



void MainWindow::on_fileLineEdit_editingFinished()
{
    QString filename;
    QString key;
    std::string line;
    filename = ui->fileLineEdit->text();
    std::ifstream file_object (filename.toStdString());
    key = ui->keyLineEdit->text();
    if(!file_object)
    {
        ui->textBrowser->setText("File not found");
        return;
    }
    if(key.isEmpty())
    {
        ui->textBrowser->setText("File found");
        return;
    }
    while(std::getline(file_object, line))
    {
        if(ui->matchCheckBox->isChecked())
        {
            if(line.find(key.toStdString()) != std::string::npos)
            {
                ui->textBrowser->setText("Word found");
                return;
            }
        }
        else
        {   QString qtLine = QString::fromStdString(line);
            qtLine = qtLine.toLower();
            if(qtLine.contains(key.toLower()))
            {
                ui->textBrowser->setText("Word found");
                return;
            }
        }

    }
    ui->textBrowser->setText("Word not found");
    file_object.close();
}

