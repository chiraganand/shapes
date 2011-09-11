#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    DisplayWidget *displayWidget = new DisplayWidget(this);
    ToolBar *toolBar = new ToolBar(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    hBoxLayout->addWidget(toolBar);
    hBoxLayout->addWidget(displayWidget);
    setLayout(hBoxLayout);

    connect(toolBar, SIGNAL(createNewShape()), displayWidget, SLOT(slotCreateShape()));
}

MainWidget::~MainWidget()
{
}
