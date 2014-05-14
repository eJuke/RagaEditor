#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include "headers/aboutwindow.h"
#include "headers/setwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:

    void on_actionQuit_2_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
