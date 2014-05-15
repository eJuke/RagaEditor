#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QLayout>
#include <QDockWidget>




MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
}


MainWindow::~MainWindow(){
    delete ui;
}

//File_sets
void MainWindow::on_actionQuit_2_triggered(){
    qApp->exit();
}
void MainWindow::on_actionOpen_triggered(){
    QString FilePath;
    FilePath = QFileDialog::getOpenFileName(this, tr("Open file"),"",tr("C++ source file(*.cpp);;Text file (*.txt);; Rich Text Format file (*.rtf);;All files (*.*)"));
    QFile file(FilePath);
}
//Window_sets
void MainWindow::on_actionToolBar_toggled(bool arg1){
    if (!arg1)  ui->ToolBarDock->close();
    else        ui->ToolBarDock->show();
}
void MainWindow::on_actionStatusBar_triggered(bool checked){
    if(!checked) ui->statusBar->close();
    else         ui->statusBar->show();
}
//Help_sets
void MainWindow::on_actionSettings_triggered()
{
    QWidget *settings = new QWidget;

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
