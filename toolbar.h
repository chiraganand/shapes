#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>

class ToolBar : public QWidget
{
    Q_OBJECT

    public:
        explicit ToolBar(QWidget *parent);
        ~ToolBar();

    public slots:
        void createTriangle();
        void createSquare();
        void createPentagon();
        void createHexagon();

    signals:
        void createNewShape(int);

    private:
        QPushButton *m_triangle;
        QPushButton *m_square;
        QPushButton *m_pentagon;
        QPushButton *m_hexagon;
};

#endif
