#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;


public slots:

    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();


public:
    int grid[4][4];
    bool kostyl;
    int score;
    int scorePlus;
    void MakeGrid();
    void Define2AtStart();
    void Define2();
    void RefreshGrid();
    void CheckLose();

};

#endif // MAINWINDOW_H
