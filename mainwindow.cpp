#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer* timer = new QTimer;
    connect (timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(1000);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    QTime time = QTime::currentTime();

    QPainter paint;
    paint.begin(this);

    paint.setBackground(Qt::red);


    paint.translate(width()/2, height()/2);
    paint.setRenderHint(QPainter::Antialiasing);

    int R = 0.85 * qMin(width()/2, height()/2);

    paint.drawImage(QRect(0 - R + 30, 0 - R + 30, 2 * (R - 15), 2 * (R - 30)), QImage(":/img/rock4.gif"));

    paint.drawEllipse(0 - R, 0 - R, 2 * R, 2 * R);

    for(int i = 0 ; i < 60 ; i++){
        if(i % 15 == 0){
            QPolygon line;
            paint.setBrush(Qt::red);
            line << QPoint(0, R) << QPoint(10 , R) << QPoint (0 , R - 25) << QPoint (10, R - 25);
            paint.drawPolygon(line);
            //paint.drawLine(0, R, 0, R - 20);
        }else if (i % 5 == 0){
            QPolygon line2;
            paint.setBrush(Qt::green);
            line2 << QPoint(0, R) << QPoint(8 , R) << QPoint (8 , R - 12) << QPoint(4, R - 20) << QPoint (0, R - 12);
            paint.drawPolygon(line2);
            //paint.drawLine(0, R, 0, R - 12);
        }else{
            QPolygon line3;
            paint.setBrush(Qt::black);
            line3 << QPoint(0, R) << QPoint(5 , R) << QPoint (5 , R - 6) << QPoint (0, R - 6);
            paint.drawPolygon(line3);
            //paint.drawLine(0, R, 0, R - 6);
        }
        paint.rotate(6.0);
    }

    paint.save();

    QPolygon pol;

    pol << QPoint(-0.05 * R, 0) << QPoint(0.05 * R, 0) << QPoint(0, -0.4 * R);
    paint.rotate(30 * (time.hour() + time.minute() / 60));
    paint.setBrush(Qt::black);
    paint.drawPolygon(pol);

    paint.restore();

    paint.save();

    QPolygon pol2;

    pol2 << QPoint(-0.05 * R, 0) << QPoint(0.05 * R, 0) << QPoint(0, -0.6 * R);
    paint.rotate(6.0 * (time.minute() + time.second() / 60));
    paint.setBrush(Qt::black);
    paint.drawPolygon(pol2);

    paint.restore();

    paint.save();

    QPolygon pol3;

    pol3 << QPoint(-0.02 * R, 0) << QPoint(0.02 * R, 0) << QPoint(0, -0.8 * R);
    paint.rotate(6.0 * time.second());
    paint.setBrush(Qt::red);
    paint.drawPolygon(pol3);

    paint.restore();


    paint.setBrush(Qt::black);
    paint.drawEllipse(0 - 13, 0 - 13 , 26, 26);

    paint.end();
}

