#include "headers/mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
        ui->textEdit->setFontPointSize(8);
        connect(ui->textEdit,SIGNAL(cursorPositionChanged()),
                this,SLOT(buttons()));
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
    {
        ui->textEdit->setFontItalic(1);
    }
    else
    {
        ui->textEdit->setFontItalic(0);
    }
}



void MainWindow::on_butBold_clicked(bool checked)
{
    if(checked)
    {
        ui->textEdit->setFontWeight(99);
    }
    else
    {
        ui->textEdit->setFontWeight(10);
    }
}

void MainWindow::on_butUnderL_clicked(bool checked)
{
    ui->textEdit->setFontUnderline(checked);
}

void MainWindow::on_butAlLeft_clicked(bool checked)
{
    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignLeft);
    }
}

void MainWindow::on_butAlCenter_clicked(bool checked)
{
    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_butAlRight_clicked(bool checked)
{
    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignRight);
    }
}

void MainWindow::on_butAlJust_clicked(bool checked)
{
    if (checked)
    {
        ui->textEdit->setAlignment(Qt::AlignJustify);
    }
}

void MainWindow::on_butSearch_clicked()
{
    searchWindow = new QWidget;
    QVBoxLayout *search = new QVBoxLayout;
    QHBoxLayout *search_1 = new QHBoxLayout;
    QHBoxLayout *search_2 = new QHBoxLayout;
    QHBoxLayout *search_3 = new QHBoxLayout;
    QLabel *search_text = new QLabel("Find:");
    QLabel *replace_text = new QLabel("Replace by:");
    QLineEdit *search_request = new QLineEdit;
    QLineEdit *replace_request = new QLineEdit;
    search_1->addWidget(search_text);
    search_1->addWidget(search_request);
    search_2->addWidget(replace_text);
    search_2->addWidget(replace_request);
    search_find = new QPushButton("Find next",this);
    search_find_replace = new QPushButton("Replace all",this);
    search_cancel = new QPushButton("Cancel", this);
    search_3->addWidget(search_find);
    search_3->addWidget(search_find_replace);
    search_3->addWidget(search_cancel);
    search->addLayout(search_1);
    search->addLayout(search_2);
    search->addLayout(search_3);
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

void MainWindow::buttons() {
    if(ui->textEdit->alignment()==Qt::AlignRight)
    {
        ui->butAlRight->setChecked(true);
    }
    if(ui->textEdit->alignment()==Qt::AlignLeft)
    {
        ui->butAlLeft->setChecked(true);
    }
    if(ui->textEdit->alignment()==Qt::AlignCenter)
    {
        ui->butAlCenter->setChecked(true);
    }
    if(ui->textEdit->alignment()==Qt::AlignJustify)
    {
        ui->butAlJust->setChecked(true);
    }
    if (ui->textEdit->fontWeight()==99)
    {
        ui->butBold->setChecked(true);
    }
    else
    {
        ui->butBold->setChecked(false);
    }
    if(ui->textEdit->fontItalic()==true)
    {
        ui->butItalic->setChecked(true);
    }
    else
    {
        ui->butItalic->setChecked(false);
    }
    if(ui->textEdit->fontUnderline()==true)
    {
        ui->butUnderL->setChecked(true);
    }
    else
    {
        ui->butUnderL->setChecked(false);
    }
}

void MainWindow::on_butFontDown_clicked()
{
    ui->textEdit->setFontPointSize(ui->textEdit->fontPointSize()-1);
}

void MainWindow::on_butFontUp_clicked()
{
    ui->textEdit->setFontPointSize(ui->textEdit->fontPointSize()+1);
}
