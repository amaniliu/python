#include "graphicsview.h"
#include "ui_graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicsView)
{
    ui->setupUi(this);
    ui->view->setScroll(ui->horizontalScrollBar, ui->verticalScrollBar);
}

GraphicsView::~GraphicsView()
{
    delete ui;
}

void GraphicsView::addImage(QImage *image)
{
    ui->view->addImage(image);
}

void GraphicsView::addPolygons(const QVector<QVector<QPointF> > &polygons)
{
    ui->view->addPolygons(polygons);
}

void GraphicsView::zoomIn()
{
    ui->view->zoomIn();
}

void GraphicsView::zoomOut()
{
    ui->view->zoomOut();
}

void GraphicsView::zoomOrigin()
{
    ui->view->zoomOrigin();
}

void GraphicsView::zoomAdjust()
{
    ui->view->zoomAdjust();
}
