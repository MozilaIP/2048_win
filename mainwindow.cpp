#include "mainwindow.h"
//#include "stdafx.h"
#include <ctime>
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
//#include <termios.h> //линуксовая
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <QString>
#include <fcntl.h>
#include <math.h>
#include <QThread>
#include <QtGui>
#include <QFont>
#include <QWaitCondition>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->label->setPixmap(EmptyPix); to use

    QObject::connect(ui->LeftButton, SIGNAL(clicked()), this, SLOT(MoveLeft()));
    QObject::connect(ui->RightButton, SIGNAL(clicked()), this, SLOT(MoveRight()));
    QObject::connect(ui->UpButton, SIGNAL(clicked()), this, SLOT(MoveUp()));
    QObject::connect(ui->DownButton, SIGNAL(clicked()), this, SLOT(MoveDown()));
    QObject::connect(ui->RestartButton, SIGNAL(clicked()), this, SLOT (Restart()));



    kostyl=0;
    score=0;
    //scorePlus=0;
    MakeGrid();
}


void MainWindow::MakeGrid()
{
    RefreshGrid();
}

void MainWindow::Restart()
{
    kostyl=0;
    score=0;
    RefreshGrid();
}

void MainWindow::MoveLeft()
{
    bool moved=true;
    bool AllowDefine=false;
    while (moved)
    {
        moved=false;
        for (int y=0; y<=3; y++)
            for (int x=0; x<=3; x++)
            {
                if (grid[y][x]!=0 && x!=0)
                {
                    if (grid[y][x-1]==0)
                    {
                           grid[y][x-1]=(grid[y][x]);
                           grid[y][x]=0;
                           moved=true;
                           AllowDefine=true;
                           //this->repaint();
                           QThread::msleep(30);
                           RefreshGrid();
                    }

                    if (grid[y][x-1]==grid[y][x])
                    {
                           grid[y][x-1]=grid[y][x]*2;
                           //scorePlus=(grid[y][x])*2;
                           grid[y][x]=0;
                           moved=true;
                           AllowDefine=true;
                           //this->repaint();
                           QThread::msleep(30);
                           RefreshGrid();
                    }
                 }
            }
        repaint();
    }
    RefreshGrid();
    if (AllowDefine==true)
    Define2();
    RefreshGrid();
}


void MainWindow::MoveDown()
{
    bool moved=true;
    bool AllowDefine=false;
    while(moved)
    {
        moved=false;
        for (int x=3; x>=0; x--)
            for (int y=3; y>=0; y--)
            {
                if (grid[y][x]!=0 && y!=3)
                {
                   if (grid[y+1][x]==0)
                   {
                       grid[y+1][x]=grid[y][x];
                       grid[y][x]=0;
                       moved=true;
                       AllowDefine=true;
                       //this->repaint();
                       QThread::msleep(30);
                       RefreshGrid();
                   }

                   if (grid[y+1][x]==grid[y][x])
                   {
                       grid[y+1][x]=grid[y][x]*2;
                       //scorePlus=(grid[y][x])*2;
                       grid[y][x]=0;
                       moved=true;
                       AllowDefine=true;
                       //this->repaint();
                       QThread::msleep(30);
                       RefreshGrid();
                   }
                }
            }
        repaint();
    }
    RefreshGrid();
    if (AllowDefine==true)
    Define2();
    RefreshGrid();
}


void MainWindow::MoveUp()
{
    bool moved=true;
    bool AllowDefine=false;
    while(moved)
    {
    moved=false;
    for (int y=0; y<=3; y++)
        for (int x=0; x<=3; x++)
        {
            if (grid[y][x]!=0 && y!=0)
            {
               if (grid[y-1][x]==0)
               {
                   grid[y-1][x]=(grid[y][x]);
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   //this->repaint();
                   QThread::msleep(30);
                   RefreshGrid();
               }

               if (grid[y-1][x]==grid[y][x])
               {
                   grid[y-1][x]=grid[y][x]*2;
                   //scorePlus=(grid[y][x])*2;
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   //this->repaint();
                   QThread::msleep(30);
                   RefreshGrid();
               }
            }
        }
    repaint();
    }
    RefreshGrid();
    if (AllowDefine==true)
    Define2();
    RefreshGrid();
}


void MainWindow::MoveRight()
{
    bool moved=true;
    bool AllowDefine=false;
    while(moved)
    {
    moved=false;
    for (int y=3; y>=0; y--)
        for (int x=3; x>=0; x--)
        {
            if (grid[y][x]!=0 && x!=3)
            {
               if (grid[y][x+1]==0)
               {
                   grid[y][x+1]=grid[y][x];
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   //repaint();
                   QThread::msleep(30);
                   RefreshGrid();
               }

               if (grid[y][x+1]==grid[y][x])
               {
                   grid[y][x+1]=grid[y][x]*2;
                   //scorePlus=(grid[y][x])*2;
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   //repaint();
                   QThread::msleep(30);
                   RefreshGrid();
               }
            }
        }
         repaint();
    }
    RefreshGrid();
    if (AllowDefine==true)
    Define2();
    RefreshGrid();
}


void MainWindow::RefreshGrid()
{
    int c;

    LArr [0][0] = ui->CellBkg_0_0;
    LArr [0][1] = ui->CellBkg_0_1;
    LArr [0][2] = ui->CellBkg_0_2;
    LArr [0][3] = ui->CellBkg_0_3;

    LArr [1][0]=ui->CellBkg_1_0;
    LArr [1][1]=ui->CellBkg_1_1;
    LArr [1][2]=ui->CellBkg_1_2;
    LArr [1][3]=ui->CellBkg_1_3;

    LArr [2][0]=ui->CellBkg_2_0;
    LArr [2][1]=ui->CellBkg_2_1;
    LArr [2][2]=ui->CellBkg_2_2;
    LArr [2][3]=ui->CellBkg_2_3;

    LArr [3][0]=ui->CellBkg_3_0;
    LArr [3][1]=ui->CellBkg_3_1;
    LArr [3][2]=ui->CellBkg_3_2;
    LArr [3][3]=ui->CellBkg_3_3;


    QPixmap EmptyPix (":/new/pix/C:/Users/Admin/Desktop/release/empty.png");
    QPixmap CellPix (":/new/pix/C:/Users/Admin/Desktop/release/cellBkg100.png");
    QPixmap Cell4 (":/new/pix/C:/Users/Admin/Desktop/release/cellBkg4.png");

    if (kostyl==0) // if first start
    {
            for (int i=0; i<=3; i++)
                for (int j=0; j<=3; j++)
                {
                    grid[i][j]=0;
                    LArr [i][j]->setText(" ");
                    LArr [i][j]->setPixmap(EmptyPix);

                }

            Define2AtStart();
            kostyl=1;
    }

    //LArr [4][4];





    //LArr [0][0]->setPixmap(Cell4);

    ui->Cell_0_0->setText(" ");
    ui->CellBkg_0_0->setPixmap(EmptyPix);
    ui->Cell_0_1->setText(" ");
    ui->CellBkg_0_1->setPixmap(EmptyPix);
    ui->Cell_0_2->setText(" ");
    ui->CellBkg_0_2->setPixmap(EmptyPix);
    ui->Cell_0_3->setText(" ");
    ui->CellBkg_0_3->setPixmap(EmptyPix);

    ui->Cell_1_0->setText(" ");
    ui->CellBkg_1_0->setPixmap(EmptyPix);
    ui->Cell_1_1->setText(" ");
    ui->CellBkg_1_1->setPixmap(EmptyPix);
    ui->Cell_1_2->setText(" ");
    ui->CellBkg_1_2->setPixmap(EmptyPix);
    ui->Cell_1_3->setText(" ");
    ui->CellBkg_1_3->setPixmap(EmptyPix);

    ui->Cell_2_0->setText(" ");
    ui->CellBkg_2_0->setPixmap(EmptyPix);
    ui->Cell_2_1->setText(" ");
    ui->CellBkg_2_1->setPixmap(EmptyPix);
    ui->Cell_2_2->setText(" ");
    ui->CellBkg_2_2->setPixmap(EmptyPix);
    ui->Cell_2_3->setText(" ");
    ui->CellBkg_2_3->setPixmap(EmptyPix);

    ui->Cell_3_0->setText(" ");
    ui->CellBkg_3_0->setPixmap(EmptyPix);
    ui->Cell_3_1->setText(" ");
    ui->CellBkg_3_1->setPixmap(EmptyPix);
    ui->Cell_3_2->setText(" ");
    ui->CellBkg_3_2->setPixmap(EmptyPix);
    ui->Cell_3_3->setText(" ");
    ui->CellBkg_3_3->setPixmap(EmptyPix);

//    for (int i=0; i<=3; i++)
//        for (int j=0; j<=3; j++)
//        {
//                if (grid [i][j]==0)
//                    {
//                     LArr [i][j]->setPixmap(EmptyPix);
//                     LArr [i][j]->setText(" ");
//                    }
//                if (grid [i][j]==2)
//                    {
//                     LArr [i][j]->setPixmap(CellPix);
//                     LArr [i][j]->setText((QString::number(grid[i][j])));
//                    }

//                if (grid [i][j]==4)
//                    {
//                     LArr [i][j]->setPixmap(Cell4);
//                     LArr [i][j]->setText((QString::number(grid[i][j])));
//                    }

//        }







    if (grid [0][0]!=0)
    {
      ui->CellBkg_0_0->setPixmap(CellPix);
      ui->Cell_0_0->setText((QString::number(grid[0][0])));
    }
    if (grid [0][1]!=0)
    {
        ui->CellBkg_0_1->setPixmap(CellPix);
        ui->Cell_0_1->setText((QString::number(grid[0][1])));
    }
    if (grid [0][2]!=0)
    {
        ui->CellBkg_0_2->setPixmap(CellPix);
        ui->Cell_0_2->setText((QString::number(grid[0][2])));
    }
    if (grid [0][3]!=0)
    {
        ui->CellBkg_0_3->setPixmap(CellPix);
        ui->Cell_0_3->setText((QString::number(grid[0][3])));
    }

    if (grid [1][0]!=0)
    {
        ui->CellBkg_1_0->setPixmap(CellPix);
        ui->Cell_1_0->setText((QString::number(grid[1][0])));
    }
    if (grid [1][1]!=0)
    {
        ui->CellBkg_1_1->setPixmap(CellPix);
        ui->Cell_1_1->setText((QString::number(grid[1][1])));
    }
    if (grid [1][2]!=0)
    {
        ui->CellBkg_1_2->setPixmap(CellPix);
        ui->Cell_1_2->setText((QString::number(grid[1][2])));
    }
    if (grid [1][3]!=0)
    {
        ui->CellBkg_1_3->setPixmap(CellPix);
        ui->Cell_1_3->setText((QString::number(grid[1][3])));
    }

    if (grid [2][0]!=0)
    {
        ui->CellBkg_2_0->setPixmap(CellPix);
        ui->Cell_2_0->setText((QString::number(grid[2][0])));
    }
    if (grid [2][1]!=0)
    {
        ui->CellBkg_2_1->setPixmap(CellPix);
        ui->Cell_2_1->setText((QString::number(grid[2][1])));
    }
    if (grid [2][2]!=0)
    {
        ui->CellBkg_2_2->setPixmap(CellPix);
        ui->Cell_2_2->setText((QString::number(grid[2][2])));
    }
    if (grid [2][3]!=0)
    {
        ui->CellBkg_2_3->setPixmap(CellPix);
        ui->Cell_2_3->setText((QString::number(grid[2][3])));
    }

    if (grid [3][0]!=0)
    {
        ui->CellBkg_3_0->setPixmap(CellPix);
        ui->Cell_3_0->setText((QString::number(grid[3][0])));
    }
    if (grid [3][1]!=0)
    {
        ui->CellBkg_3_1->setPixmap(CellPix);
        ui->Cell_3_1->setText((QString::number(grid[3][1])));
    }
    if (grid [3][2]!=0)
    {
        ui->CellBkg_3_2->setPixmap(CellPix);
        ui->Cell_3_2->setText((QString::number(grid[3][2])));
    }
    if (grid [3][3]!=0)
    {
        ui->CellBkg_3_3->setPixmap(CellPix);
        ui->Cell_3_3->setText((QString::number(grid[3][3])));
    }


//    for (int i=0; i<4; i++)
//        for (int j=0; j<4; j++)
//            score+=grid[i][j];

//    score-=4;


    //score+=scorePlus;
    //ui->ScoreLabel->setText(QString::number(score));
    //scorePlus=0;

    CheckLose();
}

void MainWindow::Define2AtStart()
{
   
    int x1,x2,y1,y2;

    do
    {
        x1=rand()%4;
        y1=rand()%4;
        x2=rand()%4;
        y2=rand()%4;
    }

    while (x1==x2 || y1==y2);

    grid[y1][x1]=2;
    grid[y2][x2]=2;

}

void MainWindow::Define2()
{
    repaint();
    QThread::msleep(50);
    int count=0;
    int m;
    for (int y=3; y>=0; y--)
        for (int x=3; x>=0; x--)
            if (grid[y][x]==0) count++;

    if (count>0)
    {
        m=rand()%count;
        for (int y=3; y>=0; y--)
            for (int x=3; x>=0; x--)
            {
                if (grid[y][x]==0)
                {
                    if (m==0)
                    {
                        grid[y][x]=2;
                        return;
                    }
                    else m--;
                }
            }
    }

    RefreshGrid();
}

void MainWindow::CheckLose()
{
    bool lose=true;

    for (int y=0; y<=3; y++)
        for (int x=0; x<=3; x++)
            if (grid [y][x]==0)
                lose=false;

    if (lose==true)
    {

        for (int y=0; y<=3; y++)        //compare on y axis
            for (int x=1; x<=2; x++)
            {

                if (grid [y][x] == grid [y][x-1] || grid [y][x] == grid [y][x+1])
                {
                    lose=false;
                }
            }

        for (int y=1; y<=2; y++)        //compare on x axis
            for (int x=0; x<=3; x++)
            {

                if (grid [y][x] == grid [y+1][x] || grid [y][x] == grid [y-1][x])
                {
                    lose=false;
                }
            }
    }

    if (lose==true)
        ui->ActIndicator->setText("Lose :C");

}

MainWindow::~MainWindow()
{
    delete ui;
}
