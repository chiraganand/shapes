#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    DisplayWidget *displayWidget = new DisplayWidget(this);
    ToolBar *toolBar = new ToolBar(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    setMinimumSize(500, 500);
    hBoxLayout->addWidget(toolBar);
    hBoxLayout->addWidget(displayWidget);
    hBoxLayout->itemAt(0)->setGeometry(QRect(0, 0, 100, 500));
    hBoxLayout->itemAt(1)->setGeometry(QRect(110, 0, 400, 500));
    setLayout(hBoxLayout);

    connect(toolBar, SIGNAL(createNewShape(int)), displayWidget, SLOT(slotCreateShape(int)));
}

MainWidget::~MainWidget()
{
}
