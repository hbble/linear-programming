#ifndef LIMIT_H
#define LIMIT_H

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QValidator>

#define MAX_L 10

class Limit : public QWidget //limit class
{
    Q_OBJECT
private:
    QLineEdit *x1;  //value fields
    QLineEdit *x2;
    QLineEdit *y;
    QLineEdit *b;


    QLabel *x1_text;    //field labels
    QLabel *x2_text;
    QLabel *y_text;
    QLabel *than_text;


    QHBoxLayout *limit_line;    //Layout for limit

    static int n_limit;

public:

    Limit(QWidget *parent = 0);
    void build_layout();
    QHBoxLayout* getlimit_line();
    static int getn_limit();

    void limit_hide();
    void limit_show();

    int get_x1();
    int get_x2();
    int get_y();
    int get_b();

   void setLineText(QString, QString, QString, QString);

};

#endif // LIMIT_H
