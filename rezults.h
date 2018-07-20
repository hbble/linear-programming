#ifndef REZULTS_H
#define REZULTS_H
#define MAX_P 100

#include <QDialog>
#include <limit.h>

namespace Ui {
class Rezults;
}

typedef struct coef{
    int x1;
    int x2;
    int b;
}COEF;

typedef struct point{
    double x1;
    double x2;
}PNT;

class Rezults : public QDialog
{
    Q_OBJECT

public:
    explicit Rezults(QWidget *parent = 0);
    ~Rezults();
    void addPoint(double, double);
    void findAllPoints();
    void filterPoints();
    void showPoints();
    double findMax();
    double findMin(double);

private:
    Ui::Rezults *ui;

    COEF *function;
    COEF *limits[MAX_L];

    PNT *allP[MAX_P];
    PNT *rezP[MAX_P];

    int nAllP;
    int nRezP;

public slots:
    void receiveData(int,int, Limit**,int,int);

};

#endif // REZULTS_H
