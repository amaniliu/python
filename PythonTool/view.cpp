#include "view.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QResizeEvent>
#include <QPaintEvent>
#if _DEBUG
#include <QDebug>
#endif

View::View(QWidget *parent) :
    QWidget(parent),
    m_image(nullptr),
    m_scale(1.0),
    m_scale_min(0.05),
    m_viewSize(this->size()),
    m_painter(this),
    m_b_pressed(false),
    m_mouse_offset(0.0, 0.0)
{
	installEventFilter(parent);
}

void View::addImage(QImage* image)
{
	if (m_image != nullptr)
	{
		delete m_image;
	}
	m_image = new QImage(image->copy());

	m_scale_min = qMin(static_cast<double>(m_viewSize.width() - 5) / static_cast<double>(m_image->width()),
		static_cast<double>(m_viewSize.height() - 5) / static_cast<double>(m_image->height()));
	m_scale = m_scale > m_scale_min ? m_scale : m_scale_min;
	updateParm();
}

void View::addPolygons(const QVector<QVector<QPointF>>& polygons)
{
	m_polygons = QVector<QVector<QPointF>>(polygons);

	updatePolygons_temp();
	updateParm();
}

void View::setScroll(QScrollBar* h, QScrollBar* v)
{
	m_scroll_h = h;
	m_scroll_v = v;
	m_scroll_h->setRange(0, 0);
	m_scroll_h->setVisible(false);
	m_scroll_v->setRange(0, 0);
	m_scroll_v->setVisible(false);

	connect(m_scroll_h, SIGNAL(sliderMoved(int)), this, SLOT(on_scroll_h_sliderMoved(int)));
	connect(m_scroll_v, SIGNAL(sliderMoved(int)), this, SLOT(on_scroll_v_sliderMoved(int)));
}

void View::zoomIn()
{
	if (m_image == nullptr)
	{
		return;
	}
	QPointF p(m_viewSize.width() / 2, m_viewSize.height() / 2);
	QPointF offset(m_roi.x + p.x() / m_scale, m_roi.y + p.y() / m_scale);
	m_scale *= 1.5;
	m_scale = qMin(m_scale, 16.0);
	offset = offset - p / m_scale;
	m_mouse_offset = QPointF(offset.x() - m_roi.x, offset.y() - m_roi.y);

	updatePolygons_temp();
	updateParm();
}

void View::zoomOut()
{
	if (m_image == nullptr)
	{
		return;
	}
	QPointF p(m_viewSize.width() / 2, m_viewSize.height() / 2);
	QPointF offset(m_roi.x + p.x() / m_scale, m_roi.y + p.y() / m_scale);
	m_scale /= 1.5;
	m_scale = qMax(m_scale, 0.05);
	offset = offset - p / m_scale;
	m_mouse_offset = QPointF(offset.x() - m_roi.x, offset.y() - m_roi.y);

	updatePolygons_temp();
	updateParm();
}

void View::zoomOrigin()
{
	if (m_image == nullptr)
	{
		return;
	}
	QPointF p(m_viewSize.width() / 2, m_viewSize.height() / 2);
	QPointF offset(m_roi.x + p.x() / m_scale, m_roi.y + p.y() / m_scale);
	m_scale = 1.0;
	offset = offset - p / m_scale;
	m_mouse_offset = QPointF(offset.x() - m_roi.x, offset.y() - m_roi.y);

	updatePolygons_temp();
	updateParm();
}

void View::zoomAdjust()
{
	if (m_image == nullptr)
	{
		return;
	}
	QPointF p(m_viewSize.width() / 2, m_viewSize.height() / 2);
	QPointF offset(m_roi.x + p.x() / m_scale, m_roi.y + p.y() / m_scale);
	m_scale = qMin(static_cast<double>(m_viewSize.width() - 5) / static_cast<double>(m_image->width()),
		static_cast<double>(m_viewSize.height() - 5) / static_cast<double>(m_image->height()));
	offset = offset - p / m_scale;
	m_mouse_offset = QPointF(offset.x() - m_roi.x, offset.y() - m_roi.y);

	updatePolygons_temp();
	updateParm();
}

static int xx = 0;
void View::on_scroll_h_sliderMoved(int value)
{
	m_mouse_offset.setX(value - xx);
	xx = value;
	updateParm();
}

static int yy = 0;
void View::on_scroll_v_sliderMoved(int value)
{
	m_mouse_offset.setY(value - yy);

	yy = value;
	updateParm();
}

static QPointF origin;
void View::mouseMoveEvent(QMouseEvent* e)
{
	if (!m_b_pressed || m_image == nullptr)
	{
		return;
	}
	m_mouse_offset = (origin - e->localPos()) / m_scale;
	origin = e->localPos();

	updateParm();
}

void View::mousePressEvent(QMouseEvent* e)
{
	if (e->button() != Qt::LeftButton || m_image == nullptr)
	{
		return;
	}
	m_b_pressed = true;
	origin = e->localPos();
}

void View::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() != Qt::LeftButton || !m_b_pressed || m_image == nullptr)
	{
		return;
	}

	m_b_pressed = false;
}

void View::paintEvent(QPaintEvent* e)
{
	QWidget::paintEvent(e);
	if (m_image == nullptr)
	{
		return;
	}

	Mat src(m_image->height(), m_image->width(), CV_8UC1, m_image->bits());
	Mat src_roi;
	Size dSize((static_cast<int>(m_roi.width * m_scale) + 3) / 4 * 4, static_cast<int>(m_roi.height * m_scale));
#if 0
	qDebug() << "roi" << m_roi.width << " " << m_roi.height;
	qDebug() << "dSize" <<dSize.width << " " << dSize.height;
#endif
	cv::resize(src(m_roi), src_roi, dSize, 0, 0, m_scale > 1 ? INTER_NEAREST  : INTER_LINEAR);

	QPixmap map = QPixmap::fromImage(QImage(src_roi.data, min(src_roi.cols, m_viewSize.width()), min(src_roi.rows, m_viewSize.height()), QImage::Format_Indexed8));

	m_painter.begin(this);
	m_painter.drawPixmap((m_viewSize.width() - map.width()) / 2, (m_viewSize.height() - map.height()) / 2, map.width(), map.height(), map, 0, 0, map.width(), map.height());

	m_painter.setPen(QColor(Qt::red));
	double offset_x = (m_viewSize.width() - map.width()) / 2 - m_roi.x * m_scale;
	double offset_y = (m_viewSize.height() - map.height()) / 2 - m_roi.y * m_scale;
	QPointF offset_p(offset_x, offset_y);
    for (size_t i = 0, length = static_cast<size_t>(m_polygons_temp.size()); i < length; i++)
	{
		QVector<QPointF> poly;
        for (size_t j = 0, count = static_cast<size_t>(m_polygons_temp[static_cast<int>(i)].size()); j < count; j++)
		{
            poly.append(m_polygons_temp[static_cast<int>(i)][static_cast<int>(j)] + offset_p);
		}
		m_painter.drawPolygon(QPolygonF(poly));
	}
	m_painter.end();
}

void View::wheelEvent(QWheelEvent* e)
{
	if (m_image == nullptr)
		return;

	QPointF offset(m_roi.x + e->posF().x() / m_scale, m_roi.y + e->posF().y() / m_scale);
	if (e->delta() > 0)
	{
		m_scale *= 1.5;
		m_scale = qMin(m_scale, 16.0);
	}
	else
	{
		m_scale /= 1.5;
		m_scale = qMax(m_scale, m_scale_min);
	}
	offset = offset - e->posF() / m_scale;
	m_mouse_offset = QPointF(offset.x() - m_roi.x, offset.y() - m_roi.y);

	updatePolygons_temp();
	updateParm();
}

void View::resizeEvent(QResizeEvent*)
{
	m_viewSize = size();
	if (m_image)
	{
		m_scale_min = qMin(static_cast<double>(m_viewSize.width() - 5) / static_cast<double>(m_image->width()),
				static_cast<double>(m_viewSize.height() - 5) / static_cast<double>(m_image->height()));
		m_scale = m_scale > m_scale_min ? m_scale : m_scale_min;
	}
	updatePolygons_temp();
	updateParm();
}

void View::updateParm()
{
	if (m_image == nullptr)
		return;

	m_roi.width = min(m_viewSize.width() / m_scale, static_cast<double>(m_image->width()));
	m_roi.height = min(m_viewSize.height() / m_scale, static_cast<double>(m_image->height()));

	m_roi.x = max(0.0, min(m_roi.x + m_mouse_offset.x(), m_image->width() - m_roi.width));
	m_roi.y = max(0.0, min(m_roi.y + m_mouse_offset.y(), m_image->height() - m_roi.height));

	m_mouse_offset = QPointF(0, 0);
	int max_h = static_cast<int>(m_image->width() - m_viewSize.width() / m_scale);
	if (max_h > 0)
	{
		m_scroll_h->setVisible(true);
		m_scroll_h->setRange(0, max(0, max_h));
		m_scroll_h->setPageStep(static_cast<int>(m_viewSize.width() / m_scale));
        m_scroll_h->setValue(static_cast<int>(m_roi.x));
	}
	else
	{
		m_scroll_h->setVisible(false);
	}

	int max_v = static_cast<int>(m_image->height() - m_viewSize.height() / m_scale);
	if (max_v > 0)
	{
		m_scroll_v->setVisible(true);
		m_scroll_v->setRange(0, max(0, max_v));
		m_scroll_v->setPageStep(static_cast<int>(m_viewSize.height() / m_scale));
        m_scroll_v->setValue(static_cast<int>(m_roi.y));
	}
	else
	{
		m_scroll_v->setVisible(false);
	}

#if _DEBUG
	qDebug() << "m_roi" << m_roi.x << " " << m_roi.y << " " << m_roi.width << " " << m_roi.height;
	qDebug() << "m_scroll_h" << m_scroll_h->maximum() << " m_scroll_v" << m_scroll_v->maximum();
#endif
	update();
}

void View::updatePolygons_temp()
{
	m_polygons_temp.clear();
    for (size_t i = 0, length = static_cast<size_t>(m_polygons.size()); i < length; i++)
	{
		QVector<QPointF> polygon;
        for (size_t j = 0, total = static_cast<size_t>(m_polygons[static_cast<int>(i)].size()); j < total; j++)
		{
            polygon.append(m_polygons[static_cast<int>(i)][static_cast<int>(j)] * m_scale);
		}
		m_polygons_temp.append(polygon);
	}
}
