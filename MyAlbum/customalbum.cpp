#include "customalbum.h"
#include <QPainter>
#include <QLabel>


CustomAlbum::CustomAlbum(const QString& albumName, const QPixmap& pixmap, QWidget* parent)
	: QWidget(parent), m_pixmap(pixmap)
{
	setFixedSize(QSize(100, 120));
	QLabel* nameLab = new QLabel(albumName, this);
	nameLab->setGeometry(0, 100, 100, 20);
	nameLab->setAlignment(Qt::AlignCenter);
}

CustomAlbum::~CustomAlbum()
{}

void CustomAlbum::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QSize pixmapSize = m_pixmap.size();
	painter.drawPixmap((100 - pixmapSize.width()) / 2,
		(100 - pixmapSize.height()) / 2,
		pixmapSize.width(), pixmapSize.height(), m_pixmap);
	QWidget::paintEvent(event);
}
