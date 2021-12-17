#include "mainwindow.h"
#include "huffman.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <string>
#include <unordered_map>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
    QLabel *label = new QLabel(statusBar());
    label->setText("Made By Student");
    label->setGeometry(1420,0,180,20);
    this->setWindowTitle("HuffPad");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
   currentFile.clear();
   setWindowTitle("New File");
   ui->plainTextEdit->setPlainText(QString());
   statusBar()->showMessage(tr("New File"), 2000);
}

void MainWindow::on_actionOpen_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
   QFile file(fileName);
   if(!file.open(QIODevice::ReadOnly | QFile::Text)){
       QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
       return;
   }
   currentFile = fileName;
   setWindowTitle(fileName);
   QTextStream in(&file);
   QString text = in.readAll();
   ui->plainTextEdit->setPlainText(text);
   file.close();
   statusBar()->showMessage(QString("Opened ") + currentFile, 2000);
}

void MainWindow::on_actionSave_triggered()
{
   QString fileName = QFileDialog::getSaveFileName(this, "Save the file as");
   QFile file(fileName);
   if(!file.open(QFile::WriteOnly | QFile::Text)){
       QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
       return;
   }
   currentFile = fileName;
   setWindowTitle(fileName);
   QTextStream out(&file);
   QString text = ui->plainTextEdit->toPlainText();
   out << text;
   file.close();
}

void MainWindow::on_actionPrint_triggered()
{
   QPrinter printer;
   printer.setPrinterName("Printer name");
   QPrintDialog pDialog(&printer, this);
   if(pDialog.exec() == QDialog::Rejected){
       QMessageBox::warning(this, "Warning", "Cannot access printer");
   }
   ui->plainTextEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
   QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
   ui->plainTextEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
   ui->plainTextEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
   ui->plainTextEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
   ui->plainTextEdit->redo();
}

void MainWindow::on_actionAuthors_triggered()
{
    QMessageBox::about(this, "About Us", "Anurag Hooda - 2K19/CO/070 && Aadi Rawat - 2K19/CO/002");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
   QApplication::aboutQt();
}

void MainWindow::on_actionCompress_triggered()
{
//       QString fileName = QFileDialog::getSaveFileName(this, "Save the file as");
       QString fileName =currentFile + "-compressed";
       QFile file(fileName);
       if(!file.open(QFile::WriteOnly | QFile::Text)){
           QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
           return;
       }
//       currentFile = fileName;
//       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->plainTextEdit->toPlainText();
       QString hufftext = QString::fromStdString(buildHuffmanTree(text.toStdString()));
       out << hufftext;
       file.close();
}
