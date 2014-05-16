#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QEvent>
#include <QWidget>
#include <QLayout>
#include <QDockWidget>
#include <QRadioButton>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QComboBox>

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
    QLabel *about_pic;
    QLabel *about_text;
    QString *str_sets;
    bool *SetMode = new bool;
    QPushButton *set_decline;
    QPushButton *set_apply;
    QComboBox *set_LangA;
    QLabel *set_Lang_text;
    QComboBox *set_ThemeA;
    QLabel *set_Theme_text;
    QComboBox *set_ModeA;
    QLabel *set_Mode_text;


    QFile *setting;


private slots:
    void on_actionQuit_2_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionToolBar_toggled(bool arg1);
    void on_actionStatusBar_triggered(bool checked);
    void on_actionSettings_triggered();
    void change_EditMode(bool x);
};
#endif // MAINWINDOW_H
