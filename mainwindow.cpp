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




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->LeftButton, SIGNAL(clicked()), this, SLOT(MoveLeft()));
    QObject::connect(ui->RightButton, SIGNAL(clicked()), this, SLOT(MoveRight()));
    QObject::connect(ui->UpButton, SIGNAL(clicked()), this, SLOT(MoveUp()));
    QObject::connect(ui->DownButton, SIGNAL(clicked()), this, SLOT(MoveDown()));


    kostyl=0;
    score=0;
    scorePlus=0;
    MakeGrid();


}

void MainWindow::MakeGrid()
{
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
                           this->repaint();
                           Sleep (30);
                           RefreshGrid();

                    }

                    if (grid[y][x-1]==grid[y][x])
                    {
                           grid[y][x-1]=grid[y][x]*2;
                           scorePlus=(grid[y][x])*2;
                           grid[y][x]=0;
                           moved=true;
                           AllowDefine=true;
                           this->repaint();
                           Sleep (30);
                           RefreshGrid();
                    }
                 }
            }
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
                       this->repaint();
                       Sleep (30);
                       RefreshGrid();
                   }

                   if (grid[y+1][x]==grid[y][x])
                   {
                       grid[y+1][x]=grid[y][x]*2;
                       scorePlus=(grid[y][x])*2;
                       grid[y][x]=0;
                       moved=true;
                       AllowDefine=true;
                       this->repaint();
                       Sleep (30);
                       RefreshGrid();
                   }

                }

            }
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
                   this->repaint();
                   Sleep (30);
                   RefreshGrid();
               }

               if (grid[y-1][x]==grid[y][x])
               {
                   grid[y-1][x]=grid[y][x]*2;
                   scorePlus=(grid[y][x])*2;
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   this->repaint();
                   Sleep (30);
                   RefreshGrid();
               }

            }
        }
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
                   this->repaint();
                   Sleep (30);
                   RefreshGrid();
               }

               if (grid[y][x+1]==grid[y][x])
               {
                   grid[y][x+1]=grid[y][x]*2;
                   scorePlus=(grid[y][x])*2;
                   grid[y][x]=0;
                   moved=true;
                   AllowDefine=true;
                   this->repaint();
                   Sleep (30);
                   RefreshGrid();
               }

            }

        }
    }

    RefreshGrid();
    if (AllowDefine==true)
    Define2();
    RefreshGrid();
}


void MainWindow::RefreshGrid()
{

    if (kostyl==0) // if first start
    {
            for (int i=0; i<=3; i++)
                for (int j=0; j<=3; j++)
                    grid[i][j]=0;

            Define2AtStart();
            kostyl=1;
    }

    ui->Cell_0_0->setText(" ");
    ui->Cell_0_1->setText(" ");
    ui->Cell_0_2->setText(" ");
    ui->Cell_0_3->setText(" ");

    ui->Cell_1_0->setText(" ");
    ui->Cell_1_1->setText(" ");
    ui->Cell_1_2->setText(" ");
    ui->Cell_1_3->setText(" ");

    ui->Cell_2_0->setText(" ");
    ui->Cell_2_1->setText(" ");
    ui->Cell_2_2->setText(" ");
    ui->Cell_2_3->setText(" ");

    ui->Cell_3_0->setText(" ");
    ui->Cell_3_1->setText(" ");
    ui->Cell_3_2->setText(" ");
    ui->Cell_3_3->setText(" ");



    if (grid [0][0]!=0)
    ui->Cell_0_0->setText((QString::number(grid[0][0])));
    if (grid [0][1]!=0)
    ui->Cell_0_1->setText((QString::number(grid[0][1])));
    if (grid [0][2]!=0)
    ui->Cell_0_2->setText((QString::number(grid[0][2])));
    if (grid [0][3]!=0)
    ui->Cell_0_3->setText((QString::number(grid[0][3])));

    if (grid [1][0]!=0)
    ui->Cell_1_0->setText((QString::number(grid[1][0])));
    if (grid [1][1]!=0)
    ui->Cell_1_1->setText((QString::number(grid[1][1])));
    if (grid [1][2]!=0)
    ui->Cell_1_2->setText((QString::number(grid[1][2])));
    if (grid [1][3]!=0)
    ui->Cell_1_3->setText((QString::number(grid[1][3])));

    if (grid [2][0]!=0)
    ui->Cell_2_0->setText((QString::number(grid[2][0])));
    if (grid [2][1]!=0)
    ui->Cell_2_1->setText((QString::number(grid[2][1])));
    if (grid [2][2]!=0)
    ui->Cell_2_2->setText((QString::number(grid[2][2])));
    if (grid [2][3]!=0)
    ui->Cell_2_3->setText((QString::number(grid[2][3])));

    if (grid [3][0]!=0)
    ui->Cell_3_0->setText((QString::number(grid[3][0])));
    if (grid [3][1]!=0)
    ui->Cell_3_1->setText((QString::number(grid[3][1])));
    if (grid [3][2]!=0)
    ui->Cell_3_2->setText((QString::number(grid[3][2])));
    if (grid [3][3]!=0)
    ui->Cell_3_3->setText((QString::number(grid[3][3])));


    score+=scorePlus;
    ui->ScoreLabel->setText(QString::number(score)+"  +"+QString::number(scorePlus));
    scorePlus=0;

    CheckLose();

}

void MainWindow::Define2AtStart()
{
   
    int x1,x2,y1,y2;

    x1=rand()%3;
    y1=rand()%3;
    x2=rand()%3;
    y2=rand()%3;

    grid[y1][x1]=2;
    grid[y2][x2]=2;

}

void MainWindow::Define2()
{
    this->repaint();
    Sleep (500);
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
        ui->ActIndicator->setText("Lose :c");

}

MainWindow::~MainWindow()
{
    delete ui;
}
