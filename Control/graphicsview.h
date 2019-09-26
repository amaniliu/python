#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QWidget>

namespace Ui {
class GraphicsView;
}

class QImage;
class GraphicsView : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsView(QWidget *parent = nullptr);
    ~GraphicsView();

    void addImage(QImage* image);

    void addPolygons(const QVector<QVector<QPointF>>& polygons);

public slots:
    void zoomIn();

    void zoomOut();

    void zoomOrigin();

    void zoomAdjust();

private:
    Ui::GraphicsView *ui;
};

#endif // GRAPHICSVIEW_H
