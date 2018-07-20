#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);

    QRegExp exp("[-]{0,1}[0-9]{1,5}"); //setting format for QEditLine
    ui->lineF_x1->setValidator(new QRegExpValidator(exp,this));
    ui->lineF_x2->setValidator(new QRegExpValidator(exp,this));
    ui->lineF_y->setValidator(new QRegExpValidator(exp,this));

    //limits
    for(int i = 0; i < MAX_L; i++){    //adding loop
        lim[i] = new Limit();//creating
        lim[i]->build_layout();
        ui->verticalLayout_L->addLayout(lim[i]->getlimit_line());

        if(i > 8)
            lim[i]->limit_hide();
    }//for

    ui->lineF_x1->setText("30");
    ui->lineF_x2->setText("76");
    ui->lineF_y->setText("1");

    ui->lineY_x1->setText("1");
    ui->lineY_x2->setText("-2");

    lim[0]->setLineText("0", "-1", "-12", "0");

    lim[1]->setLineText("8", "1", "16", "0");

    lim[2]->setLineText("1", "-1", "-10", "0");

    lim[3]->setLineText("1", "1", "10", "0");

    lim[4]->setLineText("4", "3", "12", "0");

    lim[5]->setLineText("0", "1", "-6", "-1");

    lim[6]->setLineText("-4", "3", "-48", "0");

    lim[7]->setLineText("-1", "0", "-16", "0");

    lim[8]->setLineText("-1", "-4", "-56", "0");

    ////////////////////

    //results dialogue
    dialog = new Rezults();
    dialog->setModal(true);

    //sending data to Rezults
    connect(this,SIGNAL(sendData(int,int, Limit**,int,int)),dialog,SLOT(receiveData(int,int, Limit**,int,int)));


    //close program signal
    connect(ui->exitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}

MainWindow::~MainWindow(){
    delete ui;
}

int MainWindow::calculate_func_x1(){
    return ui->lineF_x1->text().toInt() + ui->lineF_y->text().toInt() * ui->lineY_x1->text().toInt();
}

int MainWindow::calculate_func_x2(){
    return ui->lineF_x2->text().toInt() + ui->lineF_y->text().toInt() * ui->lineY_x2->text().toInt();
}

void MainWindow::on_addLButton_clicked(){
    lim[Limit::getn_limit()]->limit_show();
}

void MainWindow::on_removeLButton_clicked(){
    lim[Limit::getn_limit() - 1]->limit_hide();
    lim[Limit::getn_limit()]->setLineText(0,0,0,0);
}

void MainWindow::on_submitButton_clicked()
{
    dialog->show();
    //calling send data signal
    emit sendData(calculate_func_x1(), calculate_func_x2(), lim,
                  ui->lineY_x1->text().toInt(), ui->lineY_x2->text().toInt());

    //searching for points
    dialog->findAllPoints();
    dialog->filterPoints();
    dialog->showPoints();

    dialog->findMin(dialog->findMax());


}
