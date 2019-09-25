#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QScrollBar>
#include <opencv2/opencv.hpp>

using namespace cv;

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

	void addImage(QImage* image);

	void addPolygons(const QVector<QVector<QPointF>>& polygons);

	void setScroll(QScrollBar* h, QScrollBar* v);

	void zoomIn();

	void zoomOut();

	void zoomOrigin();

	void zoomAdjust();
protected:
    void mouseMoveEvent(QMouseEvent* e);

    void mousePressEvent(QMouseEvent* e);

    void mouseReleaseEvent(QMouseEvent* e);

    void paintEvent(QPaintEvent* e);

    void wheelEvent(QWheelEvent* e);

    void resizeEvent(QResizeEvent* e);

public slots:
	void on_scroll_h_sliderMoved(int value);

	void on_scroll_v_sliderMoved(int value);
private:
	void updateParm();
	void updatePolygons_temp();
private:
	QScrollBar* m_scroll_h;
	QScrollBar* m_scroll_v;
private:
    QImage* m_image;
    qreal m_scale;
	qreal m_scale_min;
    QSize m_viewSize;
	QPainter m_painter;
	bool m_b_pressed;
	QPointF m_mouse_offset;
	Rect_<double> m_roi;
	QVector<QVector<QPointF>> m_polygons;
	QVector<QVector<QPointF>> m_polygons_temp;
};

#endif // VIEW_H
