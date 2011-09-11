#include "displaywidget.h"

DisplayWidget::DisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    m_enableDrag = false;
    m_pen.setStyle(Qt::SolidLine);
    m_pen.setColor(QColor("Black"));
    m_pen.setWidth(1);
    setStyleSheet("background-color: white");
}

DisplayWidget::~DisplayWidget()
{
}

void DisplayWidget::paintEvent(QPaintEvent *)
{
    QStyleOption options;
    options.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &options, &painter, this);
    painter.setPen(m_pen);
    int i;

    if (!m_points.isEmpty()) {
//        initialiseRect();
        /* Create circles at edges */
        for (i=0; i<m_points.count(); i++) {
            painter.drawEllipse(m_points.at(i), 4, 4);
        }
    if (m_enableDrag) {
        painter.drawEllipse(m_currentPoint, 4, 4);
    }

    if (m_pathList.isEmpty()) {
        initialisePaths();
    }

    QPainterPath path;
    foreach (path, m_pathList) {
        painter.drawPath(path);
    }
    QPainterPath circlePath;
    foreach (circlePath, m_circleList) {
        painter.drawPath(circlePath);
    }
    }
}

void DisplayWidget::initialiseRect()
{
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(10, 110);
}

void DisplayWidget::initialiseTriangle()
{
    if (!m_points.isEmpty()) {
        m_points.clear();
    }
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(50, 110);
}

void DisplayWidget::initialiseSquare()
{
    if (!m_points.isEmpty()) {
        m_points.clear();
    }
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(10, 110);
}

void DisplayWidget::initialisePentagon()
{
    if (!m_points.isEmpty()) {
        m_points.clear();
    }
    m_points << QPoint(10, 10);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(50, 160);
    m_points << QPoint(10, 110);
}

void DisplayWidget::initialiseHexagon()
{
    if (!m_points.isEmpty()) {
        m_points.clear();
    }
    m_points << QPoint(10, 10);
    m_points << QPoint(50, 60);
    m_points << QPoint(110, 10);
    m_points << QPoint(110, 110);
    m_points << QPoint(50, 160);
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
        } else {
            /* 0th point is connected to the last in the list XXX: use a circular list? */
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
            /* Replace the initial path with an empty one before a drag operation, so that it
             * can be replaced by the new path at the end of the operation.
             */
            m_circleList[i] = QPainterPath();
        }
    }
    QWidget::update();
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_currentPoint = event->posF();

    if (m_enableDrag) {
        QPainterPath path;
        path.addEllipse(m_currentPoint, 4, 4);
        m_circleList[m_changedPathIndex] = path;

        m_enableDrag = false;
        QWidget::update();
    }
}

void DisplayWidget::slotCreateShape(int sides)
{
    switch (sides) {
        case 3:
            initialiseTriangle();
            break;

        case 4:
            initialiseSquare();
            break;

        case 5:
            initialisePentagon();
            break;

        case 6:
            initialiseHexagon();
            break;
    }
}
