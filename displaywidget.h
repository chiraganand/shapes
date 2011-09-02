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
    void mouseMoveEvent(QMouseEvent *);
    void initialiseRect();

private:
    Ui::DisplayWidget *ui;
    QPen m_pen;
    int m_x;
    int m_y;
    QPainterPath m_path;
    QVector<QPointF> m_points;
};

#endif // DISPLAYWIDGET_H
