#include "toolbar.h"

#include <QVBoxLayout>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    vBoxLayout->setSizeConstraint(QLayout::SetFixedSize);

    m_triangle = new QPushButton("Create &triangle", this);
    connect(m_triangle, SIGNAL(clicked()), this, SLOT(createTriangle()));
    vBoxLayout->addWidget(m_triangle);

    m_square = new QPushButton("Create &square", this);
    connect(m_square, SIGNAL(clicked()), this, SLOT(createSquare()));
    vBoxLayout->addWidget(m_square);

    m_pentagon = new QPushButton("Create &pentagon", this);
    connect(m_pentagon, SIGNAL(clicked()), this, SLOT(createPentagon()));
    vBoxLayout->addWidget(m_pentagon);

    m_hexagon = new QPushButton("Create &hexagon", this);
    connect(m_hexagon, SIGNAL(clicked()), this, SLOT(createHexagon()));
    vBoxLayout->addWidget(m_hexagon);

    setLayout(vBoxLayout);
}

ToolBar::~ToolBar()
{
    delete m_triangle;
    delete m_square;
    delete m_pentagon;
    delete m_hexagon;
}

void ToolBar::createTriangle()
{
    emit createNewShape(3);
}

void ToolBar::createSquare()
{
    emit createNewShape(4);
}

void ToolBar::createPentagon()
{
    emit createNewShape(5);
}

void ToolBar::createHexagon()
{
    emit createNewShape(6);
}
