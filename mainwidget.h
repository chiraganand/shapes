#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>

#include "displaywidget.h"
#include "toolbar.h"

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        explicit MainWidget(QWidget *parent = 0);
        ~MainWidget();
};

#endif // MAINWIDGET_H
