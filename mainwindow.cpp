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
void MainWindow::on_actionOpen_triggered(){
   // FilePath = new QString;
  //  FilePath = QFileDialog::getOpenFileName(this, tr("Open file"),"",tr("C++ source file(*.cpp);;Text file (*.txt);; Rich Text Format file (*.rtf);;All files (*.*)"));
  //  QFile file(FilePath);
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


void MainWindow::on_actionSave_triggered()
{
    QString Save_pat; // = new QString;
    Save_pat = QFileDialog::getSaveFileName(this, tr("Saving by Raga"), "", tr("Text(*.txt);;C++(*.cpp);; html (*.htm, *.html)"));
}
