#include "imagescrollwidget.h"
#include <QLabel>
#include <QImageReader>
#include <QHboxLayout>

ImageScrollWidget::ImageScrollWidget(QWidget *parent)
	: QWidget(parent)
{	
	QImage image("C:\\Users\\wps\\Pictures\\Saved Pictures\\物理寻址.kk");
}

ImageScrollWidget::~ImageScrollWidget()
{

}
