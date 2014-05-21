#include "headers/mainwindow.h"
#include "ui_mainwindow.h"



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

//Open File
void MainWindow::on_actionOpen_triggered(){

    QString FilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h);; Rich Text Format file (*.rtf);;All files (*.*)"));

        if (FilePath != "")
        {
            QFile file(FilePath);

            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }

            QTextStream text(&file);

            ui->textEdit->setText(text.readAll());

            file.close();
        }
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
    //setting an edit mode
    str_sets = new QString;
    setting = new QFile(".\\settings.txt",this);
    setting->open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(setting);
    in >> *str_sets;
    setting->close();
        set_Mode_text = new QLabel("Choose a mode:");
        set_ModeA = new QComboBox;
        set_ModeA->addItem("Code Edit");
        set_ModeA->addItem("Text Edit");
        set_Theme_text = new QLabel("Theme:");
        set_ThemeA = new QComboBox;
        set_ThemeA->addItem("Dark");
        set_ThemeA->addItem("Bright");
        set_Lang_text = new QLabel("Language:");
        set_LangA = new QComboBox;
        set_LangA->addItem("English");
        set_LangA->addItem("Russian");
        set_apply = new QPushButton("Apply",this);
        set_decline = new QPushButton("Decline",this);
        set_apply->setMinimumSize(60,30);
        set_decline->setMinimumSize(60,30);
        set_apply->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        set_decline->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
     /*   connect(set_ModeA,SIGNAL(activated(1)),this,SLOT(change_EditMode(true)));
        connect(set_ModeA,SIGNAL(activated(2)),this,SLOT(change_EditMode(false)));*/
    //compositiona
        QVBoxLayout *set = new QVBoxLayout;
        QHBoxLayout *set1_1 = new QHBoxLayout;
        QHBoxLayout *set2_1 = new QHBoxLayout;
        QHBoxLayout *set3_1 = new QHBoxLayout;
        QHBoxLayout *setLast_1 = new QHBoxLayout;
    set1_1->addWidget(set_Mode_text);
    set1_1->addWidget(set_ModeA);
    set2_1->addWidget(set_Theme_text);
    set2_1->addWidget(set_ThemeA);
    set3_1->addWidget(set_Lang_text);
    set3_1->addWidget(set_LangA);
    setLast_1->addWidget(set_apply);
    setLast_1->addWidget(set_decline);
    setLast_1->setAlignment(set_apply,Qt::AlignRight);
    set->addLayout(set1_1);
    set->addLayout(set2_1);
    set->addLayout(set3_1);
    set->addLayout(setLast_1);


    settings->setLayout(set);
    settings->show();
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
void MainWindow::change_EditMode(bool x){
    *SetMode = x;
}

//Save File
void MainWindow::on_actionSave_triggered()
{

    QString Save_pat = QFileDialog::getSaveFileName(this, tr("Saving by Raga"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp *.h);; html (*.html)"));

        if (Save_pat != "")
        {
            QFile file(Save_pat);

            if (!file.open(QIODevice::WriteOnly))
            {
                QMessageBox::critical(this,tr("Error"),tr("Error"));
                return;
            }

            else
            {
                QTextStream stream(&file);

                stream << ui->textEdit->toPlainText();

                stream.flush();

                file.close();
            }
        }
}

void MainWindow::on_butRedo_clicked()
{
    ui->textEdit->redo();
}

void MainWindow::on_butUndo_clicked()
{
    ui->textEdit->undo();
}

void MainWindow::on_butItalic_clicked(bool checked)
{
    if(checked)
        ui->textEdit->setFontItalic(1);
    else
        ui->textEdit->setFontItalic(0);
}



void MainWindow::on_butBold_clicked(bool checked)
{
    if(checked)
        ui->textEdit->setFontWeight(99);
    else
        ui->textEdit->setFontWeight(10);
}

void MainWindow::on_butUnderL_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}

void MainWindow::on_butAlLeft_clicked(bool checked)
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_butAlCenter_clicked(bool checked)
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_butAlRight_clicked(bool checked)
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_butAlJust_clicked(bool checked)
{
    ui->textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_butSearch_clicked()
{
    searchWindow = new QWidget;
    QVBoxLayout *search = new QVBoxLayout;
    QHBoxLayout *search_1 = new QHBoxLayout;
    QHBoxLayout *search_2 = new QHBoxLayout;
    QLabel *search_text = new QLabel("Enter the search request:");
    QLineEdit *search_request = new QLineEdit;
    search_1->addWidget(search_text);
    search_1->addWidget(search_request);
    search_find = new QPushButton("Find",this);
    search_find_replace = new QPushButton("Find and Replace",this);
    search_cancel = new QPushButton("Cancel", this);
    search_2->addWidget(search_find);
    search_2->addWidget(search_find_replace);
    search_2->addWidget(search_cancel);
    search->addLayout(search_1);
    search->addLayout(search_2);
    searchWindow->setLayout(search);
    searchWindow->show();
    connect(search_cancel,SIGNAL(clicked()),searchWindow,SLOT(close()));
    connect(search_find,SIGNAL(clicked()),this,SLOT(action_search()));
    connect(search_find_replace,SIGNAL(clicked()),this,SLOT(action_search_and_replace()));


}
void MainWindow::action_search(){

}

void MainWindow::action_search_and_replace(){

}
