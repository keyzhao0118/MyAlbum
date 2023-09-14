#include "albumscrollwidget.h"
#include <QHBoxLayout>
#include <QImageReader>
#include "customalbum.h"

AlbumScrollWidget::AlbumScrollWidget(QSqlQuery& query, int sortType, QWidget* parent)
	: QWidget(parent)
{
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	while (query.next())
	{
		QString coverPath = query.value("CoverPath").toString();
		if (coverPath.isEmpty())
			coverPath = ":/PreviewScene/image/文件夹缩略图图标.png";
		QImageReader imageReader(coverPath);
		QSize originalSize = imageReader.size();
		QSize newSize = originalSize.scaled(QSize(100, 100), Qt::KeepAspectRatio);
		imageReader.setScaledSize(newSize);
		CustomAlbum* customImage = new CustomAlbum(query.value("Name").toString(),
			QPixmap::fromImageReader(&imageReader), this);
		hLayout->addWidget(customImage);
	}
	setLayout(hLayout);
}

AlbumScrollWidget::~AlbumScrollWidget()
{}
