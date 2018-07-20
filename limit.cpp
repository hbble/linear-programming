#include "limit.h"

int Limit::n_limit = 0;

Limit::Limit(QWidget *parent) : QWidget(parent){

    x1 = new QLineEdit();   //creating widgets
    x1->setAlignment(Qt::AlignRight);
    x2 = new QLineEdit();
    x2->setAlignment(Qt::AlignRight);
    y = new QLineEdit();
    y->setAlignment(Qt::AlignRight);
    b = new QLineEdit();

    x1_text = new QLabel("x1");
    x2_text = new QLabel("x2");
    y_text = new QLabel("y");
    than_text = new QLabel(">=");

    QRegExp exp("[-]{0,1}[0-9]{1,5}"); //QEditLine format
    //applying format
    x1->setValidator(new QRegExpValidator(exp,this));
    x2->setValidator(new QRegExpValidator(exp,this));
    y->setValidator(new QRegExpValidator(exp,this));
    b->setValidator(new QRegExpValidator(exp,this));

    limit_line = new QHBoxLayout();

    Limit::n_limit++;


}

void Limit::build_layout(){
    limit_line->addWidget(x1);
    limit_line->addWidget(x1_text);
    limit_line->addWidget(x2);
    limit_line->addWidget(x2_text);
    limit_line->addWidget(y);
    limit_line->addWidget(y_text);
    limit_line->addWidget(than_text);
    limit_line->addWidget(b);

}

QHBoxLayout* Limit::getlimit_line(){
    return limit_line;
}

int Limit::getn_limit(){
        return Limit::n_limit;
}

void Limit::limit_hide(){   //hiding limits
    if(Limit::n_limit > 2){
        x1->setVisible(false);
        x2->setVisible(false);
        y->setVisible(false);
        b->setVisible(false);
        x1_text->setVisible(false);
        x2_text->setVisible(false);
        y_text->setVisible(false);
        than_text->setVisible(false);

        Limit::n_limit--;
    }
}

void Limit::limit_show(){   //showing limits
    if(Limit::n_limit < MAX_L){
        x1->setVisible(true);
        x2->setVisible(true);
        y->setVisible(true);
        b->setVisible(true);
        x1_text->setVisible(true);
        x2_text->setVisible(true);
        y_text->setVisible(true);
        than_text->setVisible(true);

        Limit::n_limit++;
    }
}

int Limit::get_x1(){
    return x1->text().toInt();
}

int Limit::get_x2(){
    return x2->text().toInt();
}

int Limit::get_y(){
    return y->text().toInt();
}

int Limit::get_b(){
    return b->text().toInt();
}

void Limit::setLineText(QString str1, QString str2, QString str3, QString str4){
    x1->setText(str1);
    x2->setText(str2);
    b->setText(str3);
    y->setText(str4);
}
