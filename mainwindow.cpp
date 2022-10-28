#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings settings("UTB", "TAXER");

    //loading the saved settings
    int taxLevel = settings.value("general/taxlevel", 21).toInt();

    if(taxLevel == 21) ui->rb21->setChecked(true);
    else ui-> rb15->setChecked(true);

    //handle saved value
    if(settings.value("general/language", "EN").toString() == "EN")
    {
        ui->actionItalian->setChecked(false);
        ui->actionEnglish->setChecked(true);

        translator.load(":/translation_en.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }else{
        ui->actionItalian->setChecked(true);
        ui->actionEnglish->setChecked(false);

        translator.load(":/translation_it.qm");
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
    }




    connect(ui->leWithoutTAX,&QLineEdit::textChanged,this,&MainWindow::recalculate);
    connect(ui->rb15,&QRadioButton::clicked,this,&MainWindow::recalculate);
    connect(ui->rb21,&QRadioButton::clicked,this,&MainWindow::recalculate);

    connect(ui->rb15,&QRadioButton::clicked,this,&MainWindow::rbChanged);
    connect(ui->rb21,&QRadioButton::clicked,this,&MainWindow::rbChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbClear_clicked()
{
 ui->leWithTAX->clear();
 ui->leWithoutTAX->clear();
}

void MainWindow::recalculate()
{
    bool success;
    double value = ui->leWithoutTAX->text().toDouble(&success);
    if (success){
        if (ui->rb15->isChecked()) value *= 1.15;
        else value *= 1.21;

        ui->leWithTAX->setText(QString("%1").arg(value));
    } else ui->leWithTAX->setText("N/A");
}


void MainWindow::rbChanged()
{
    QSettings settings("UTB", "TAXER");
    int value = 0;
    if(ui->rb15->isChecked(), value=15);
    else value = 21;

    //saving the value
    settings.setValue("general/taxlevel", value);


}

void MainWindow::on_actionItalian_triggered()
{
    QSettings settings("UTB", "TAXER");
    ui->actionEnglish->setChecked(false);

    settings.setValue("general/language", "IT");

    qApp->removeTranslator(&translator);
    translator.load(":/translation_it.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}


void MainWindow::on_actionEnglish_triggered()
{
    QSettings settings("UTB", "TAXER");
    ui->actionItalian->setChecked(false);

    settings.setValue("general/language", "EN");

    qApp->removeTranslator(&translator);
    translator.load(":/translation_en.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

