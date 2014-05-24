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
    QHBoxLayout *search_4 = new QHBoxLayout;
    QLabel *search_text = new QLabel("Find:");
    QLabel *replace_text = new QLabel("Replace by:");
    replace_enabled = new QCheckBox("Replace");
    search_results = new QLabel("Waiting for enter search variable...");
    search_request = new QLineEdit;
    replace_request = new QLineEdit;
    replace_request->setEnabled(0);
    search_1->addWidget(search_text);
    search_1->addWidget(search_request);
    search_2->addWidget(replace_text);
    search_2->addWidget(replace_request);
    search_2->addWidget(replace_enabled);
    search_findBackward = new QPushButton("Find Previous",this);
    search_findBackward->setEnabled(0);
    search_findForward = new QPushButton("Find next",this);
    search_findForward->setEnabled(0);
    search_find_replace = new QPushButton("Replace all",this);
    search_find_replace->setEnabled(0);
    search_cancel = new QPushButton("Cancel", this);
    search_3->addWidget(search_findBackward);
    search_3->addWidget(search_findForward);
    search_3->addWidget(search_find_replace);
    search_3->addWidget(search_cancel);
    search_4->addWidget(search_results);
    search->addLayout(search_1);
    search->addLayout(search_2);
    search->addLayout(search_3);
    search->addLayout(search_4);
    searchWindow->setLayout(search);
    searchWindow->setFixedSize(400,125);
    searchWindow->setWindowTitle("Text Search");
    searchWindow->show();
    connect(search_request,SIGNAL(textChanged(QString)),this,SLOT(Search_Replace_match()));
    connect(replace_request,SIGNAL(textChanged(QString)),this,SLOT(Search_Replace_match()));
    connect(search_request,SIGNAL(textChanged(QString)),this,SLOT(Search_Results_count()));
    connect(search_request,SIGNAL(textChanged(QString)),this,SLOT(Search_TextChanged(QString)));
    connect(replace_enabled,SIGNAL(clicked(bool)),this,SLOT(Replace_TextChanged()));
    connect(search_cancel,SIGNAL(clicked()),searchWindow,SLOT(close()));
    connect(search_findBackward,SIGNAL(clicked()),this,SLOT(action_searchBackward()));
    connect(search_findForward,SIGNAL(clicked()),this,SLOT(action_searchForward()));
    connect(search_find_replace,SIGNAL(clicked()),this,SLOT(action_search_and_replace()));
}

void MainWindow::Search_Replace_match(){
    if ((search_request->text()) == (replace_request->text())){
        search_results->setText("<font color='darkred'>Values in \"Find\" and \"Replace by\" must be different!</font>");
        chk = 0;
    }
    else
    {
        chk = 1;
        Search_Results_count();
    }
}

void MainWindow::Search_Results_count(){
    if(chk){
    search_results_count = 0;
    if(!((search_request->text()).isEmpty())){
    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->setTextCursor(cursor);
    while (ui->textEdit->find(search_request->text())){
        search_results_count++;
    }
    QString tmp = QString::number(search_results_count);
    search_results->setText("<font color='darkgreen'>" + tmp + " matches found</font>");
    } else {
        search_results->setText("Waiting for enter search variable...");
    }
    }
}

void MainWindow::Replace_TextChanged(){
    replace_request->setEnabled((replace_enabled->isChecked()));
    search_find_replace->setEnabled((replace_enabled->isChecked()));
}

void MainWindow::Search_TextChanged(QString str_search){
    search_findForward->setEnabled(!(str_search.isEmpty()));
    search_findBackward->setEnabled(!(str_search.isEmpty()));
}

void MainWindow::action_searchBackward(){
    QMessageBox warn_searchBackward;
    if (!(ui->textEdit->find(search_request->text(),QTextDocument::FindBackward))){
        warn_searchBackward.setText("Can't find variable: \"" + (search_request->text()) + "\"");
        warn_searchBackward.exec();
    }
}

void MainWindow::action_searchForward(){
    QMessageBox warn_searchForward;
    if (!(ui->textEdit->find(search_request->text()))){
        warn_searchForward.setText("Can't find variable: \"" + (search_request->text()) + "\"");
        warn_searchForward.exec();
    }
}

void MainWindow::action_search_and_replace(){
    QMessageBox warn_search_and_replace;
    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->setTextCursor(cursor);
    if ((!(replace_request->text() == search_request->text()))){
    if (ui->textEdit->find(search_request->text())){
    ui->textEdit->textCursor().insertText(replace_request->text());
    while (ui->textEdit->find(search_request->text()))
    ui->textEdit->textCursor().insertText(replace_request->text());
    warn_search_and_replace.setText("Replacement successful!");
    warn_search_and_replace.exec();
    } else {
        warn_search_and_replace.setText("Can't find variable: \"" + (search_request->text()) + "\"");
        warn_search_and_replace.exec();
    }
    }
    Search_Results_count();
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
