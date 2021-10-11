#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QIcon>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setNativeMenuBar(false);
    this->setWindowTitle("简单绘图系统");
    isDrawing = false;
    bLeftClick = false;
    setMouseTracking(true);
    runPath = QCoreApplication::applicationDirPath();       //获取exe路径
    hglpName = "photo";
    hglpPath = QString("%1/%2").arg(runPath).arg(hglpName);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::slotDrawOver()
{
    qDebug() << "结束绘画";
    ui->actionpolygon->setChecked(false);
}
void MainWindow::setMode(Mode m)
{

    this->m = m;
    QPoint lastP(0,0);
    QPoint endP(0,0);
    lastPoint = lastP;
    endPoint = endP;
    for (int i = 0; i<pointList.size(); ++i) {
        pointList.clear();
    }
    ui->actionline->setChecked(false);
    ui->actionrectangle->setChecked(false);
    ui->actionpolygon->setChecked(false);
    ui->actionoval->setChecked(false);
    ui->actioncircular->setChecked(false);
    ui->actionchange_color->setChecked(false);
    ui->actiontrans->setChecked(false);
    switch (m)
    {
    case LINE:
        ui->actionline->setChecked(true);
        break;
    case RECTANGLE:
        ui->actionrectangle->setChecked(true);
        break;
    case POLYGON:
        ui->actionpolygon->setChecked(true);
        break;
    case OVAL:
        ui->actionoval->setChecked(true);
        break;
    case CIRCLE:
        ui->actioncircular->setChecked(true);
        break;
    case PLOYLINE:
        ui->actionchange_color->setChecked(false);
        break;
    case TRANS:
        ui->actiontrans->setChecked(true);
        break;
    }
}
void  MainWindow::draw_line()
{
    int x1 = lastPoint.x();
    int y1 = lastPoint.y();
    int x2 = endPoint.x();
    int y2 = endPoint.y();
    length = sqrt(pow(abs(x2-x1),2)+pow(abs(y2-y1),2));
    QPoint p1(x1,y1);
    QPoint p2(x2,y2);

    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    painter.setPen(pen); //添加画笔

//    if(isDrawing)
//    {
//        QPainter pp;
//        pp.setPen(pen);
//        pp.drawLine(x1,y1,x2,y2);
//    }
//    else
//    {
//        painter.drawLine(x1,y1,x2,y2);
//    }
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.drawLine(x1,y1,x2,y2);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.drawLine(x1,y1,x2,y2);
        painter.drawPixmap(0,0,pix);
    }
}

void  MainWindow::draw_rectangle()
{
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    area = w*h;//计算面积

    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    QBrush brush(Qt::green); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷

    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,pix);
    }
}

void  MainWindow::draw_polygon()
{
    QVector<QLine> lines;
    for(int i = 0; i<pointList.size()-1; i++)
    {
        QLine line(QPoint(pointList[i].x(), pointList[i].y()), QPoint(pointList[i+1].x(), pointList[i+1].y()));
        lines.push_back(line);
    }
    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    QBrush brush(Qt::green); //画刷
    painter.setPen(pen);
    painter.setBrush(brush);
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawLines(lines);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawLines(lines);
        painter.drawPixmap(0,0,pix);
    }
}

void  MainWindow::draw_oval()
{
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    area = PI *(w/2)*(h/2);
    QRectF r1=QRectF(x,y,w,h);  	//椭圆的外接矩形

    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    QBrush brush(Qt::green); //画刷
    painter.setPen(pen);
    painter.setBrush(brush);
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawEllipse(r1);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawEllipse(r1);
        painter.drawPixmap(0,0,pix);
    }

}
void  MainWindow::draw_circle()
{
    int x,y,r;
    x = lastPoint.x();
    y = lastPoint.y();
    r = endPoint.x() - x;
    area = PI *(r/2)*(r/2);
    QRectF r1=QRectF(x,y,r,r);  	//椭圆的外接矩形
    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    QBrush brush(Qt::green); //画刷
    painter.setPen(pen);
    painter.setBrush(brush);
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawEllipse(r1);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawEllipse(r1);
        painter.drawPixmap(0,0,pix);
    }
}
void  MainWindow::draw_ployline()
{
    QVector<QLine> lines;
    //QLine line;
    for(int i = 0; i<pointList.size()-1; i++)
    {
        QLine line(QPoint(pointList[i].x(), pointList[i].y()), QPoint(pointList[i+1].x(), pointList[i+1].y()));
        lines.push_back(line);
    }
    // int number = lines.size();
    QPainter painter(this);
    QPen pen(Qt::red,2); //画笔
    QBrush brush(Qt::green); //画刷
    painter.setPen(pen);
    painter.setBrush(brush);
    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawLines(lines);
        painter.drawPixmap(0,0,pix);
    }
    else
    {
        QPainter pp(&pix);
        pp.setPen(pen);
        pp.setBrush(brush);
        pp.drawLines(lines);
        painter.drawPixmap(0,0,pix);
    }
}
//绘图事件
void MainWindow::paintEvent(QPaintEvent *)
{
    qDebug() << "开始画画";
    qDebug() << m;
    switch (m)
    {
    case LINE:
        draw_line();
        break;
    case RECTANGLE:
        //用鼠标拖出一个矩形
        draw_rectangle();
        break;
    case POLYGON:
        draw_polygon();
        break;
    case OVAL:
        draw_oval();
        break;
    case CIRCLE:
        draw_circle();
        break;
    case PLOYLINE:
        draw_ployline();
        break;
    case TRANS:
        break;
    }
}

//鼠标按下事件
void MainWindow:: mousePressEvent(QMouseEvent *event)
{
    switch (m)
    {
    case LINE:
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;
    case RECTANGLE:
        //用鼠标拖出一个矩形
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;

    case POLYGON:
        //        qDebug() << "开始画多边形";
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;
    case OVAL:
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;
    case CIRCLE:
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;
    case PLOYLINE:
        if(event->button()==Qt::LeftButton) //鼠标左键按下
        {
            lastPoint = event->pos();
            isDrawing = true;
            bMove = true;
        }
        break;
    case TRANS:
        break;
    }


}
//鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    switch (m)
    {
    case LINE:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update(); //进行绘制
        }
        break;
    case RECTANGLE:
        //用鼠标拖出一个矩形
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update(); //进行绘制
        }
        break;
    case POLYGON:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update();
        }
        break;
    case OVAL:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update(); //进行绘制
        }
        break;
    case CIRCLE:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update(); //进行绘制
        }
        break;
    case PLOYLINE:
        if(event->buttons()&Qt::LeftButton) //鼠标左键按下的同时移动鼠标
        {
            endPoint = event->pos();
            update();
        }
        break;
    case TRANS:
        break;
    }

}

//鼠标释放事件
void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    switch (m)
    {
    case LINE:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            endPoint = event->pos();
            isDrawing = false;
            bMove = false;
            update();
        }
        else if(event->button() == Qt::RightButton){
            QMessageBox::information(this, QWidget::tr("Info"), "线段长度 = " + QString::number(length, 'g', 6));
        }

        break;
    case RECTANGLE:
        //用鼠标拖出一个矩形
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            endPoint = event->pos();
            isDrawing = false;
            bMove = false;
            update();
        }
        else if(event->button() == Qt::RightButton)
        {
            QMessageBox::information(this, QWidget::tr("Info"), "矩形面积 = " + QString::number(area, 'g', 6));
        }

        break;

    case POLYGON:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            //pointList.push_back(lastPoint);
            endPoint = event->pos();
            pointList.push_back(endPoint);
            isDrawing = false;
            bMove = false;
            update();
        }
        break;

    case OVAL:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            endPoint = event->pos();
            isDrawing = false;
            bMove = false;
            update();
        }
        else if(event->button() == Qt::RightButton)
        {
            QMessageBox::information(this, QWidget::tr("Info"), "椭圆面积 = " + QString::number(area, 'g', 6));
        }
        break;
    case CIRCLE:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            endPoint = event->pos();
            isDrawing = false;
            bMove = false;
            update();
        }
        else if(event->button() == Qt::RightButton)
        {
            QMessageBox::information(this, QWidget::tr("Info"), "圆的面积 = " + QString::number(area, 'g', 6));
        }
        break;
    case PLOYLINE:
        if(event->button() == Qt::LeftButton) //鼠标左键释放
        {
            endPoint = event->pos();
            pointList.push_back(endPoint);
            isDrawing = false;
            bMove = false;
            update();
        }
        break;
    case TRANS:
        break;
    }

}

//鼠标双击事件
void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    //int x,y;
    switch (m)
    {
    case LINE:
        break;
    case RECTANGLE:
        break;
    case PLOYLINE:
        for(int i =0;i<pointList.size()-1;++i)
        {
            length += sqrt(pow(abs(pointList[i+1].x() - pointList[i].x()),2)+pow(abs(pointList[i+1].y() - pointList[i].y()),2));
        }
        QMessageBox::information(this, QWidget::tr("Info"), "折线的长度 = " + QString::number(length, 'g', 6));
        break;
    case OVAL:
        break;
    case CIRCLE:
        break;
    case POLYGON:
    {
        double tmp =0;
        pointList.push_back(pointList[0]);
        update();
        for(int i =0;i<pointList.size()-1;++i)
        {
            tmp += pointList[i].x()*pointList[i+1].y()-pointList[i+1].x()*pointList[i].y();
        }
        tmp += pointList[pointList.size()-1].x()*pointList[0].y() - pointList[0].x()*  pointList[pointList.size()-1].y();
        area = abs(tmp)/2;
        QMessageBox::information(this, QWidget::tr("Info"), "多边形的面积 = " + QString::number(area, 'g', 6));
    }
    }
    qDebug() <<"左键双击";
}
void MainWindow::on_actionnew_file_triggered()
{
    pix = QPixmap(1200, 1000);
    pix.fill(Qt::white);
    //设置画布大小
    qDebug() <<"创建新的画布";
    isDrawing = false;
}

void MainWindow::on_actionrectangle_triggered()
{
    qDebug() << "开始画矩形";
    setMode(RECTANGLE);

}

void MainWindow::on_actionline_triggered()
{
    qDebug() << "开始画线";
    setMode(LINE);
}

void MainWindow::on_actionpolygon_triggered()
{
    qDebug() << "开始画多边形";
    setMode(POLYGON);
}

void MainWindow::on_actionoval_triggered()
{
    qDebug() << "开始椭圆";
    setMode(OVAL);
}

void MainWindow::on_actioncircular_triggered()
{
    qDebug() << "开始画圆形";
    setMode(CIRCLE);
}

void MainWindow::on_actionchange_color_triggered()
{
    setMode(PLOYLINE);
}

void MainWindow::on_actiontrans_triggered()
{
    setMode(TRANS);
}

void MainWindow::on_actionsave_triggered()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    pix.save(filename1,Q_NULLPTR,100);
}

void MainWindow::on_actionopen_triggered()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg)"));
    if(filename.isEmpty())
        return;
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        pix.load(filename);
    }
}
