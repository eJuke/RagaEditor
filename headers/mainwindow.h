#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QWidget>
#include <QLayout>
#include <QDockWidget>
#include <QRadioButton>
#include <QFile>
#include <QTextStream>
#include <QComboBox>
#include <QFont>
#include <QLineEdit>

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
    //File_paths
    QString *FilePath;
    QString *Save_path;
    QWidget *searchWindow;
    QPushButton *search_find;
    QPushButton *search_find_replace;
    QPushButton *search_cancel;




private slots:
    void on_actionQuit_2_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionToolBar_toggled(bool arg1);
    void on_actionStatusBar_triggered(bool checked);
    void on_actionSettings_triggered();
    void change_EditMode(bool x);
    void on_actionSave_triggered();
    void on_butRedo_clicked();
    void on_butUndo_clicked();
    void on_butItalic_clicked(bool checked);
    void on_butBold_clicked(bool checked);
    void on_butUnderL_clicked(bool checked);
    void on_butAlLeft_clicked(bool checked);
    void on_butAlCenter_clicked(bool checked);
    void on_butAlRight_clicked(bool checked);
    void on_butAlJust_clicked(bool checked);
    void on_butSearch_clicked();
    void action_search();
    void action_search_and_replace();
};
#endif // MAINWINDOW_H
