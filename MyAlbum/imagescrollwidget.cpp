#include "imagescrollwidget.h"
#include <QImageReader>
#include <QVBoxLayout>
#include "customimage.h"

ImageScrollWidget::ImageScrollWidget(QSqlQuery& query, int sortType, int view, QWidget* parent)
	: QWidget(parent)
{	
	QVBoxLayout* vLayout = new QVBoxLayout;
	while (query.next())
	{
		//ToDo：由缓存管理模块提供指定视图的缩略图Pixmap-------------------------------
		//CustomImage* customImage = new CustomImage(viewSize,
		//CacheManager::getCachePixmap(query.value("Path").toString(),viewSize), this);
		QImageReader imageReader(query.value("Path").toString());
		QSize originalSize = imageReader.size();
		QSize newSize;
		switch (view)
		{
		case 0:
			newSize = originalSize.scaled(QSize(100, 100), Qt::KeepAspectRatio);
			break;
		case 1:
			newSize = originalSize.scaled(QSize(150, 150), Qt::KeepAspectRatio);
			break;
		case 2:
			newSize = originalSize.scaled(QSize(200, 200), Qt::KeepAspectRatio);
			break;
		default:
			newSize = originalSize.scaled(QSize(100, 100), Qt::KeepAspectRatio);
		}
		imageReader.setScaledSize(newSize);
		//--------------------------------------------------------------------------
		CustomImage* customImage = new CustomImage(ViewSize(view),
			QPixmap::fromImageReader(&imageReader), this);
		vLayout->addWidget(customImage);
	}
	setLayout(vLayout);
}

ImageScrollWidget::~ImageScrollWidget()
{

}
