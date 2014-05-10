#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *window = new QWidget;
    mainArea = new QTextEdit;
    mainArea->setMinimumHeight(400);
    mainArea->setMinimumWidth(600);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(mainArea);
    window->setLayout(mainLayout);
    window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::textSlot(){

}
