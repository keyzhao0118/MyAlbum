#include "imagescrollwidget.h"
#include <QSqlQuery>
#include <QImageReader>
#include <QVBoxLayout>
#include "customimage.h"

ImageScrollWidget::ImageScrollWidget(QWidget *parent)
	: QWidget(parent)
{	
	
}

ImageScrollWidget::~ImageScrollWidget()
{

}

void ImageScrollWidget::refresh(QSqlQuery& query, int view, int sort)
{
	QVBoxLayout* vLayout = new QVBoxLayout;
	while (query.next())
	{
		//ToDo：由缓存管理模块提供指定视图的缩略图Pixmap-------------------------------
		//CustomImage* customImage = new CustomImage(viewSize,
		//CacheManager::getCachePixmap(query.value("Path").toString(),viewSize), this);
		QImageReader imageReader(query.value("Path").toString());
		QSize originalSize = imageReader.size();
		QSize newSize = originalSize.scaled(QSize(100, 100), Qt::KeepAspectRatio);
		imageReader.setScaledSize(newSize);
		//--------------------------------------------------------------------------
		CustomImage* customImage = new CustomImage(ViewSize::Small,
			QPixmap::fromImageReader(&imageReader), this);
		vLayout->addWidget(customImage);
	}
	setLayout(vLayout);
}
