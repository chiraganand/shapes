#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    DisplayWidget *displayWidget = new DisplayWidget(this);
    QHBoxLayout *hBoxLayout = new QHBoxLayout;

    hBoxLayout->addWidget(displayWidget);
    setLayout(hBoxLayout);
}

MainWidget::~MainWidget()
{
    delete ui;
}
