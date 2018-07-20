#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "limit.h"
#include "rezults.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int calculate_func_x1();
    int calculate_func_x2();

signals:
    void sendData(int, int, Limit**, int, int);

private:
    Ui::MainWindow *ui;

    Limit *lim[MAX_L];   //pointers array for limits
    Rezults *dialog;

private slots:

    void on_addLButton_clicked();

    void on_removeLButton_clicked();

    void on_submitButton_clicked();
};

#endif // MAINWINDOW_H
