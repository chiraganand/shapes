#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
    class DisplayWidget;
}

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayWidget(QWidget *parent = 0);
    ~DisplayWidget();

    void paintEvent(QPaintEvent *);
    void initialiseRect();
    void initialisePaths();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::DisplayWidget *ui;
    QPen m_pen;
    QPointF m_currentPoint;
    QList<QPainterPath> m_pathList;
    QList<QPainterPath> m_circleList;
    QVector<QPointF> m_points;
    bool m_enableDrag;
    int m_changedPathIndex;
};

#endif // DISPLAYWIDGET_H
