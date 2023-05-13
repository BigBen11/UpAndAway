#include "errorwindow.h"
#include "ui_errorwindow.h"

ErrorWindow::ErrorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorWindow)
{
    ui->setupUi(this);

}

ErrorWindow::~ErrorWindow()
{
    delete ui;
}

void ErrorWindow::setErrorText(std::string text){
    QString qtext(text.c_str());
    errorText = qtext;
     ui->label->setText(errorText);
}

void ErrorWindow::on_pushButtonDetails_clicked()
{
    ui->labelDetails->setText("Wenn Sie die Datei bereits korrigiert haben, drücken Sie an 'Wiederholen'. Wählen Sie 'Abbrechen' um das App zu verlassen.");
}


void ErrorWindow::on_pushButtonWiederholen_clicked()
{
    hide();
}


void ErrorWindow::on_pushButtonAbbrechen_clicked()
{
    QCoreApplication::quit();
}

