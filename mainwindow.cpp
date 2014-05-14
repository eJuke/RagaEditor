#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QLayout>




MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_actionQuit_2_triggered(){
    qApp->exit();
}

void MainWindow::on_actionAbout_triggered(){
    QWidget *about = new QWidget;
    about_pic = new QLabel;
    about_text = new QLabel("RagaEditor v0.1alpha (c)2014");
    about_pic->setPixmap(QPixmap::fromImage(QImage(":/about/About_pic.png")));
    QVBoxLayout *aboutLayout = new QVBoxLayout;
    aboutLayout->addWidget(about_pic);
    aboutLayout->addWidget(about_text);
    about->setLayout(aboutLayout);
    about->setFixedSize(400,400);
    about->show();
}



void MainWindow::on_actionOpen_triggered(){
    QString FilePath;
    FilePath = QFileDialog::getOpenFileName(this, tr("Open file"),"",tr("C++ source file(*.cpp);;Text file (*.txt);; Rich Text Format file (*.rtf);;All files (*.*)"));
    QFile file(FilePath);
        if (!file.open(QIODevice::ReadOnly)){ return;}
        else{
            ErrorOpen = new QMessageBox();
            ErrorOpen->information(this,"Error","File is read only");
        }
}
