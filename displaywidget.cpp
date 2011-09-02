#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);

    m_enableDrag = false;
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
    painter.setPen(m_pen);
    int i;

    if (m_points.isEmpty()) {
        initialiseRect();
        /* Create circles at edges */
        for (i=0; i<m_points.count(); i++) {
            painter.drawEllipse(m_points.at(i), 4, 4);
        }
    }
    if (m_pathList.isEmpty()) {
        initialisePaths();
    }

    painter.drawEllipse(m_currentPoint, 4, 4);

    QPainterPath path;
    foreach (path, m_pathList) {
        painter.drawPath(path);
    }
    QPainterPath circlePath;
    foreach (circlePath, m_circleList) {
        painter.drawPath(circlePath);
    }
}

void DisplayWidget::initialiseRect()
{
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(10, 110);
}

void DisplayWidget::initialisePaths()
{
    int i;
    for (i=0; i<m_points.count(); i++) {
        QPainterPath linePath;
        m_pathList.append(linePath);
        m_pathList[i].moveTo(m_points.at(i));
    }
    for (i=0; i<m_points.count(); i++) {
        QPainterPath circlePath;
        m_circleList.append(circlePath);
        m_circleList[i].moveTo(m_points.at(i));
    }

    /* Create lines */
    for (i=0; i<m_points.count(); i++) {
        if (i == m_points.count() - 1) {
            m_pathList[i].lineTo(m_points.at(0));
        }
        else {
            m_pathList[i].lineTo(m_points.at(i+1));
        }
    }

    /* Create circles at edges */
    for (i=0; i<m_points.count(); i++) {
        m_circleList[i].addEllipse(m_points.at(i), 4, 4);
    }
}

void DisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_currentPoint = event->posF();
    if (m_enableDrag) {
        if (m_changedPathIndex != 0) {
            m_pathList[m_changedPathIndex-1].setElementPositionAt(1, m_currentPoint.x(), m_currentPoint.y());
            m_pathList[m_changedPathIndex].setElementPositionAt(0, m_currentPoint.x(), m_currentPoint.y());
        } else {    // 0th point is connected to the last in the list
            m_pathList[m_pathList.count() - 1].setElementPositionAt(1, m_currentPoint.x(), m_currentPoint.y());
            m_pathList[m_changedPathIndex].setElementPositionAt(0, m_currentPoint.x(), m_currentPoint.y());
        }
        QWidget::update();
    }
}

void DisplayWidget::mousePressEvent(QMouseEvent *event)
{
    int i;
    m_currentPoint = event->posF();
    for (i=0; i<m_circleList.count(); i++) {
        if (m_circleList.at(i).contains(m_currentPoint)) {
            m_enableDrag = true;
            m_changedPathIndex = i;
            m_circleList.removeAt(i);
        }
    }
    QWidget::update();
}
