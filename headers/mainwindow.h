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
#include <QTextCursor>
#include <QDialog>
#include <QMessageBox>
#include <QCheckBox>


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


    //File_paths
    QString *FilePath;
    QString *Save_path;
    //Search
    QWidget *searchWindow;
    QLineEdit *search_request;
    QLineEdit *replace_request;
    QCheckBox *replace_enabled;
    QPushButton *search_findForward;
    QPushButton *search_findBackward;
    QPushButton *search_find_replace;
    QPushButton *search_cancel;
    QString *search_value;
    QLabel *search_results;
    QLabel *search_results_main;
    int search_results_count;
    bool chk;



private slots:
    void on_actionQuit_2_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_actionToolBar_toggled(bool arg1);
    void on_actionStatusBar_triggered(bool checked);
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
    void action_searchForward();
    void action_searchBackward();
    void action_search_and_replace();
    void Search_TextChanged(QString str_search);
    void Replace_TextChanged();
    void Search_Results_count();
    void Search_Replace_match();
    void buttons ();
    void on_butFontDown_clicked();
    void on_butFontUp_clicked();
};
#endif // MAINWINDOW_H
