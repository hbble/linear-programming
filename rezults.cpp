#include "rezults.h"
#include "ui_rezults.h"

Rezults::Rezults(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rezults)
{
    ui->setupUi(this);

    function = new COEF;
    nAllP = nRezP = 0;


}

Rezults::~Rezults()
{
    delete ui;
}

void Rezults::receiveData(int f_x1, int f_x2, Limit** lim, int y_x1, int y_x2){

    //read and save data
    function->x1 = f_x1;
    function->x2 = f_x2;

    for (int i = 0; i < Limit::getn_limit(); i++){
        limits[i] = new COEF;

        limits[i]->x1 = lim[i]->get_x1() + lim[i]->get_y() * y_x1;
        limits[i]->x2 = lim[i]->get_x2() + lim[i]->get_y() * y_x2;
        limits[i]->b = lim[i]->get_b();
    }
}

void Rezults::addPoint(double x1, double x2){
    allP[nAllP] = new PNT;
    allP[nAllP]->x1 = x1;
    allP[nAllP]->x2 = x2;

    nAllP++;
}

void Rezults::findAllPoints(){
    nAllP = nRezP = 0;
    //adding 0,0 point
    addPoint(0,0);

    //axes crossing
    for (int i = 0; i < Limit::getn_limit(); i++) {
        if(limits[i]->x1 != 0 || limits[i]->x2 != 0){

            if(limits[i]->x1 == 0 || limits[i]->x2 == 0){//for parallel lines to axes

                if(limits[i]->x1 == 0){
                    addPoint(0, (double)limits[i]->b / limits[i]->x2);
                    continue;
                }

                if(limits[i]->x2 == 0){
                   addPoint((double)limits[i]->b / limits[i]->x1, 0);
                   continue;
                }
            }
            else{   //not parallel
                addPoint(0, (double)limits[i]->b / limits[i]->x2);
                addPoint((double)limits[i]->b / limits[i]->x1, 0);
            }//else
        }//if
    }//if

    //crossing lines itself (Cramer's rule)
    double delta, delta1, delta2;
    for (int i = 0; i < Limit::getn_limit(); i++) {
        for (int j = i + 1; j < Limit::getn_limit(); j++) {
            delta = limits[i]->x1 * limits[j]->x2 - limits[i]->x2 * limits[j]->x1;
            delta1 = limits[i]->b * limits[j]->x2 - limits[i]->x2 * limits[j]->b;
            delta2 = limits[i]->x1 * limits[j]->b - limits[i]->b * limits[j]->x1;

            if (delta != 0)
                addPoint(delta1 / delta, delta2 / delta);
        }
    }

}

void Rezults::filterPoints(){
    for (int i = 0; i < nAllP; i++) {
        for (int j = 0; j < Limit::getn_limit(); j++) {
            double check = limits[j]->x1 * allP[i]->x1 + limits[j]->x2 * allP[i]->x2;
            check *= 1000; check = floor(check); check /= 1000;

            if(allP[i]->x1 >= 0 && allP[i]->x2 >= 0 && check >= limits[j]->b){
                if (j == Limit::getn_limit() - 1){
                    rezP[nRezP] = allP[i];
                    nRezP++;
                }
            }
            else
                break;
        }//for j
    }//for i
}

void Rezults::showPoints(){
    QString temp = "";
    for(int i = 0; i < nRezP; i++)
        temp += "(" + QString::number(rezP[i]->x1, 'f', 2) + "," + QString::number(rezP[i]->x2, 'f', 2) + ")\n";

    ui->textEdit->setText(temp);
    temp.clear();

}

double Rezults::findMax(){
    PNT maxP;
    double value, max;

    for(int i = 0; i < nRezP; i++){
        value = function->x1 * rezP[i]->x1 + function->x2 * rezP[i]->x2;

        if (value > max) {
            max = value;
            maxP = *rezP[i];
        }
    }

    ui->lineMax->setText("(" + QString::number(maxP.x1, 'f', 2) + ","
                         + QString::number(maxP.x2, 'f', 2) + ")");
    ui->lineMaxValue->setText(QString::number(max, 'f', 2));

    return max;
}

double Rezults::findMin(double max){
    PNT minP;
    double value, min = max;

    for(int i = 0; i < nRezP; i++){
        value = function->x1 * rezP[i]->x1 + function->x2 * rezP[i]->x2;

        if (value < min) {
            min = value;
            minP = *rezP[i];
        }
    }
    ui->lineMin->setText("(" + QString::number(minP.x1, 'f', 2) + ","
                         + QString::number(minP.x2, 'f', 2) + ")");
    ui->lineMinValue->setText(QString::number(min, 'f', 2));

    return min;
}
