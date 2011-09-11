#include "toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent)
{
    m_button = new QPushButton("&Create Shape", this);
    connect(m_button, SIGNAL(clicked()), this, SLOT(createShape()));
}

ToolBar::~ToolBar()
{
    delete m_button;
}

void ToolBar::createShape()
{
    emit createNewShape();
}
