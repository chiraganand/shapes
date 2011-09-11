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
        void createShape();

    signals:
        void createNewShape();

    private:
        QPushButton *m_button;
};

#endif
