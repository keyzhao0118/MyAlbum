#include "customimage.h"
#include <QPainter>

CustomImage::CustomImage(ViewSize viewSize, const QPixmap& pixmap, QWidget* parent)
	: QWidget(parent), m_pixmap(pixmap)
{
	ui.setupUi(this);
	QSize size;
	switch (viewSize)
	{
	case ViewSize::Large:
		size = QSize(200, 200);
		break;
	case ViewSize::Medium:
		size = QSize(150, 150);
		break;
	case ViewSize::Small:
		size = QSize(100, 100); 
		break;
	default:
		size = QSize(100, 100);
	}
	setFixedSize(size);
	m_pixmap.scaled(size, Qt::KeepAspectRatio);
}

CustomImage::~CustomImage()
{}

void CustomImage::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QSize pixmapSize = m_pixmap.size();
	painter.drawPixmap((size().width() - pixmapSize.width()) / 2,
		(size().height() - pixmapSize.height()) / 2,
		pixmapSize.width(), pixmapSize.height(), m_pixmap);
	QWidget::paintEvent(event);
}
