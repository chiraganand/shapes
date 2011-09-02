#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);

    m_x = m_y = 0;
    m_pen.setStyle(Qt::SolidLine);
    m_pen.setColor(QColor("Black"));
    m_pen.setWidth(1);
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QList<QPainterPath> pathList;
    int i;

    painter.setPen(m_pen);

    if (m_points.isEmpty())
        initialiseRect();

    for (i=0; i<m_points.count(); i++) {
        QPainterPath path;
        pathList.append(path);
        pathList[i].moveTo(m_points.at(i));
    }

    for (i=0; i<m_points.count(); i++) {
        if (i == m_points.count() - 1) {
            pathList[i].lineTo(m_points.at(0));
        }
        else {
            pathList[i].lineTo(m_points.at(i+1));
        }
    }

    qDebug()<<"Elements:"<<pathList.at(0).elementCount();
    pathList[0].setElementPositionAt(1, m_x, m_y);
    pathList[1].setElementPositionAt(0, m_x, m_y);

    QPainterPath path;
    foreach (path, pathList) {
        painter.drawPath(path);
    }

    /*
    QPainterPath path2(QPointF(150, 150));
    path2.moveTo(150, 150);
    path2.lineTo(200, 200);
    path2.moveTo(150, 150);
    path2.lineTo(100, 100);
    path2.setElementPositionAt(0, m_x, m_y);
    painter.drawPath(path2);
    */
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_x = event->x();
    m_y = event->y();
    QWidget::update();
}

void DisplayWidget::initialiseRect()
{
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(10, 110);
}
