#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPoint>
#include <iostream>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QScreen>
#include <QGuiApplication>
#define PI 3.1415926
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void singalDrawOver();
private:
    Ui::MainWindow *ui;
private:
    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;
    QPixmap tempPix;
private:
    QString runPath;
    QString hglpName;
    QString hglpPath;
private:
    bool isDrawing; //标志是否正在绘图
    bool bLeftClick;
    bool bMove;
    double area;//绘制图形的面积
    double length;//绘制直线的长度
private:
    QVector<QPoint> pointList;
    QPoint movePoint;

    typedef enum P_Mode
    {
        LINE,
        CIRCLE,
        OVAL,
        RECTANGLE,
        POLYGON,
        TRANS,
        PLOYLINE
    } Mode;

    Mode m;
private:
    void setMode(Mode m);
    void  draw_line();
    void  draw_rectangle();
    void  draw_polygon();
    void  draw_oval();
    void  draw_circle();
    void  draw_ployline();
protected:

    //绘图事件
    void paintEvent(QPaintEvent *);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent*);
    //鼠标双击事件
    void mouseDoubleClickEvent(QMouseEvent *);
private slots:
    void slotDrawOver();
    void on_actionrectangle_triggered();
    void on_actionline_triggered();
    void on_actionnew_file_triggered();
    void on_actionpolygon_triggered();
    void on_actionoval_triggered();
    void on_actioncircular_triggered();
    void on_actionchange_color_triggered();
    void on_actiontrans_triggered();
    void on_actionsave_triggered();
    void on_actionopen_triggered();
};
#endif // MAINWINDOW_H
