#include "headers/mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow){
        ui->setupUi(this);
        this->setWindowTitle("RagaEditor");
        ui->textEdit->setFontPointSize(8);
        connect(ui->textEdit,SIGNAL(cursorPositionChanged()),
                this,SLOT(buttons()));
        connect(ui->textEdit,SIGNAL(textChanged()),this,SLOT(Save_check()));
        save_check = false;
        save_done = false;
}


MainWindow::~MainWindow(){
    delete ui;
}

//File_sets
void MainWindow::on_actionQuit_2_triggered(){
    if (save_check){
    QMessageBox CloseDialog;
        CloseDialog.setText(tr("Do you want to save file before exit? "));
        CloseDialog.setStandardButtons( QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        CloseDialog.setDefaultButton(QMessageBox::Cancel);
        CloseDialog.setStyleSheet("color: #fff; background-color: #303030");
        int ret = CloseDialog.exec();
        switch (ret) {
        case QMessageBox::No:
            qApp->exit();
            break;
        case QMessageBox::Yes:
            on_actionSave_triggered();
            if (save_done)
            qApp->exit();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    } else {
        qApp->exit();
    }
}

//Open File
void MainWindow::on_actionOpen_triggered(){
    make_open = 1;
    if (save_check){
        QMessageBox NewDialog;
            NewDialog.setWindowTitle("WARNING!");
            NewDialog.setText(tr("File have been modified! Do you want to save changes? \nAll unsaved changes will be lost!"));
            NewDialog.setStandardButtons( QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            NewDialog.setDefaultButton(QMessageBox::Cancel);
            NewDialog.setStyleSheet("color: #fff; background-color: #303030");
            int res = NewDialog.exec();
            switch (res)
            {
            case QMessageBox::Yes:
                on_actionSave_triggered();
                break;
            case QMessageBox::No:
                break;
            case QMessageBox::Cancel:
                make_open = 0;
                break;
            default:
                break;
        }
    }
    if (make_open){
    QString FilePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("Text Files (*.txt);;C++ Files (*.cpp);; HTML (*.html);;All files (*.*)"));
        if (!FilePath.isEmpty())
        {
            QFile file(FilePath);
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QTextStream text(&file);
            QTextCursor cursor(ui->textEdit->document());
            ui->textEdit->setText(text.readAll());
            file.close();
            ui->textEdit->selectAll();
            ui->textEdit->setFontItalic(0);
            ui->textEdit->setFontWeight(10);
            ui->textEdit->setFontUnderline(0);
            ui->textEdit->setAlignment(Qt::AlignLeft);
            ui->textEdit->setCurrentFont(QFont ("Arial",8));
            ui->textEdit->setTextCursor(cursor);
            save_check = false;
            save_done = true;
        }
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
    about_text = new QLabel("RagaEditor v0.2beta (c)2014");
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
    /*QString Save_pat = QFileDialog::getSaveFileName(this, tr("Saving by Raga"), "",
        tr("Text Files (*.txt);;C++ Files (*.cpp);; html (*.html)"));
        if (!Save_pat.isEmpty())
        {
            QFile file(Save_pat);
            if (!file.open(QIODevice::WriteOnly)){
                QMessageBox::critical(this,tr("Error"),tr("Error"));
                return;
            }
            else{
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                stream.flush();
                file.close();
                save_check = false;
                save_done = true;
            }
        }
        */

    QFileDialog dialog(this, tr("Save as ..."), "");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList filters;
    filters << "Text Files (*.txt)" << "C++ Files (*.cpp)" << "HTML (*.html)";
    dialog.setNameFilters(filters);
    QString Save_pat, selectedFilter;
    if (dialog.exec() == QDialog::Accepted)
    {
        selectedFilter = dialog.selectedNameFilter();
        Save_pat = dialog.selectedFiles()[0];
    }
    if (!Save_pat.isEmpty())
    {
        QFile file(Save_pat);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,tr("Error"),tr("Error"));
            return;
        }
        else{
            QTextStream stream(&file);
            if (selectedFilter == "Text Files (*.txt)" || selectedFilter == "C++ Files (*.cpp)")    stream << ui->textEdit->toPlainText();
            if (selectedFilter == "HTML (*.html)") stream << ui->textEdit->toHtml();
            stream.flush();
            file.close();
            save_check = false;
            save_done = true;
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
    searchWindow->setWindowFlags(Qt::WindowMinimizeButtonHint);
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
    search_find_replace = new QPushButton("Replace");
    search_find_replace->setEnabled(0);
    search_find_replace_all = new QPushButton("Replace all",this);
    search_find_replace_all->setEnabled(0);
    search_cancel = new QPushButton("Cancel", this);
    search_3->addWidget(search_findBackward);
    search_3->addWidget(search_findForward);
    search_3->addWidget(search_find_replace);
    search_3->addWidget(search_find_replace_all);
    search_3->addWidget(search_cancel);
    search_4->addWidget(search_results);
    search->addLayout(search_1);
    search->addLayout(search_2);
    search->addLayout(search_3);
    search->addLayout(search_4);
    searchWindow->setLayout(search);
    searchWindow->setFixedSize(500,125);
    searchWindow->setWindowTitle("Text Search");
    searchWindow->show();
    connect(search_request,SIGNAL(textChanged(QString)),this,SLOT(Search_Results_count()));
    connect(search_request,SIGNAL(textChanged(QString)),this,SLOT(Search_TextChanged(QString)));
    connect(replace_enabled,SIGNAL(clicked(bool)),this,SLOT(Replace_CheckBox_clicked()));
    connect(search_cancel,SIGNAL(clicked()),searchWindow,SLOT(close()));
    connect(search_cancel,SIGNAL(clicked()),this,SLOT(Search_close_clicked()));
    connect(search_findBackward,SIGNAL(clicked()),this,SLOT(action_searchBackward()));
    connect(search_findForward,SIGNAL(clicked()),this,SLOT(action_searchForward()));
    connect(search_find_replace,SIGNAL(clicked()),this,SLOT(Replace_once()));
    connect(search_find_replace_all,SIGNAL(clicked()),this,SLOT(action_search_and_replace()));
}



void MainWindow::Save_check(){
    save_check = true;
    save_done = false;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if (save_check){
    QMessageBox CloseDialog;
        CloseDialog.setText(tr("Do you want to save file before exit? "));
        CloseDialog.setStandardButtons( QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        CloseDialog.setDefaultButton(QMessageBox::Cancel);
        CloseDialog.setStyleSheet("color: #fff; background-color: #303030");
        int ret = CloseDialog.exec();
        switch (ret) {
        case QMessageBox::No:
            break;
        case QMessageBox::Yes:
            on_actionSave_triggered();
            if (!save_done)
            event->ignore();
            break;
        case QMessageBox::Cancel:
            event->ignore();
        default:
            break;
        }
    }
}

void MainWindow::Search_Results_count(){
    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(Qt::transparent);
    search_results_count = 0;
    if(!((search_request->text()).isEmpty())){
    ui->textEdit->setTextCursor(cursor);
    while (ui->textEdit->find(search_request->text())){
        search_results_count++;
        ui->textEdit->setTextBackgroundColor(QColor(0,145,255));
    }
    QString tmp = QString::number(search_results_count);
    search_results->setText("<font color='darkgreen'>" + tmp + " matches found</font>");
    ui->textEdit->setTextCursor(cursor);
    } else {
        search_results->setText("Waiting for enter search variable...");
        ui->textEdit->setTextCursor(cursor);
    }
}

void MainWindow::Search_close_clicked(){
    QTextCursor cursor(ui->textEdit->document());
    ui->textEdit->selectAll();
    ui->textEdit->setTextBackgroundColor(Qt::transparent);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::Replace_once(){
    if(ui->textEdit->textCursor().hasSelection()){
    ui->textEdit->textCursor().insertText(replace_request->text());
    Search_Results_count();
    }
}

void MainWindow::Replace_CheckBox_clicked(){
    replace_request->setEnabled((replace_enabled->isChecked()));
    search_find_replace_all->setEnabled((replace_enabled->isChecked()));
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
    } else {
        warn_search_and_replace.setText("Values in \"Find\" and \"Replace by\" must be different!");
        warn_search_and_replace.exec();
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
    ui->fontComboBox->setCurrentFont(ui->textEdit->currentFont());
    ui->fontSizeBox->setValue(ui->textEdit->fontPointSize());
}

void MainWindow::on_actionSyntax_triggered(bool check)
{
    if(check)
    {
        syntax = new Syntax(ui->textEdit->document());
        QFile file("mainwindow.h");
        if (file.open(QFile::ReadOnly | QFile::Text)) ui->textEdit->setPlainText(file.readAll());
        ui->butBold->setDisabled(true);
        ui->butItalic->setDisabled(true);
        ui->butUnderL->setDisabled(true);
        ui->butAlCenter->setDisabled(true);
        ui->butAlJust->setDisabled(true);
        ui->butAlLeft->setDisabled(true);
        ui->butAlRight->setDisabled(true);
        ui->textEdit->setAlignment(Qt::AlignLeft);
        ui->textEdit->setFontFamily("Courier");
        ui->textEdit->setFontPointSize(10);
        ui->textEdit->setWordWrapMode(QTextOption::NoWrap);
        ui->fontComboBox->setDisabled(true);
        ui->fontSizeBox->setDisabled(true);
    }
    else
    {
        ui->butBold->setEnabled(true);
        ui->butItalic->setEnabled(true);
        ui->butUnderL->setEnabled(true);
        ui->butAlCenter->setEnabled(true);
        ui->butAlJust->setEnabled(true);
        ui->butAlLeft->setEnabled(true);
        ui->butAlRight->setEnabled(true);
        ui->textEdit->setWordWrapMode(QTextOption::WordWrap);
        ui->fontComboBox->setEnabled(true);
        ui->fontSizeBox->setEnabled(true);

        syntax->deleteLater();
    }
}

void MainWindow::on_actionNew_triggered()
{
    QTextCursor cursor(ui->textEdit->document());
    if (save_check)
    {

        QMessageBox NewDialog;
            NewDialog.setWindowTitle("WARNING!");
            NewDialog.setText(tr("File have been modified! Do you want to save changes? \nAll unsaved changes will be lost!"));
            NewDialog.setStandardButtons( QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
            NewDialog.setDefaultButton(QMessageBox::Cancel);
            NewDialog.setStyleSheet("color: #fff; background-color: #303030");
            int res = NewDialog.exec();
            switch (res)
            {
            case QMessageBox::Yes:
                on_actionSave_triggered();
                if (save_done)
                {
                    ui->textEdit->clear();
                    save_check = 0;
                }
                break;
            case QMessageBox::No:
                ui->textEdit->clear();

                ui->textEdit->selectAll();
                ui->textEdit->setFontItalic(0);
                ui->textEdit->setFontWeight(10);
                ui->textEdit->setFontUnderline(0);
                ui->textEdit->setAlignment(Qt::AlignLeft);
                ui->textEdit->setCurrentFont(QFont ("Arial",8));
                ui->textEdit->setTextCursor(cursor);
                save_check = 0;
                break;
            case QMessageBox::Cancel:
                break;
            default:
                break;
        }
    } else {
        ui->textEdit->clear();
        ui->textEdit->selectAll();
        ui->textEdit->setFontItalic(0);
        ui->textEdit->setFontWeight(10);
        ui->textEdit->setFontUnderline(0);
        ui->textEdit->setAlignment(Qt::AlignLeft);
        ui->textEdit->setCurrentFont(QFont ("Arial",8));
        ui->textEdit->setTextCursor(cursor);
        save_check = 0;
    }
}

void MainWindow::on_fontSizeBox_valueChanged(int arg1)
{
    ui->textEdit->setFontPointSize(arg1);
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->textEdit->setCurrentFont(f);
}
