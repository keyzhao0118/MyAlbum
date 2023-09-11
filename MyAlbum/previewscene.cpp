#include "previewscene.h"
#include <QDir>
#include <QLibrary>
#include <QMessageBox>

PreviewScene::PreviewScene(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.albumscrollArea->setFixedHeight(150);

	//自定义标题栏上的信号处理
	connect(ui.customTitle, SIGNAL(settingsBtnClicked()), this, SLOT(onSettingsBtnClicked()));
	connect(ui.customTitle, SIGNAL(minBtnClicked()), this, SLOT(showMinimized()));
	connect(ui.customTitle, SIGNAL(maxBtnClicked(bool)), this, SLOT(onMaxBtnClicked(bool)));
	connect(ui.customTitle, SIGNAL(closeBtnClicked()), this, SLOT(close()));

	//ToDo：图片选项卡上的信号处理
	
	//ToDo：图片显示窗口的信号处理

	//ToDo

	if (!loadLibrary())
	{
		QMessageBox::warning(this, "数据库", "DatabaseManager.dll加载失败");
		return;
	}
	if (!m_openDatabaseFunc(QCoreApplication::applicationDirPath() +
		QDir::separator() + "mydatabase.db"))
	{
		QMessageBox::warning(this, "数据库", "数据库初始化失败");
		return;
	}

	//ToDo：从数据库的配置文件中读取配置，设定初始选项：图片格式、图片排序方式、图片视图尺寸、相册排序方式
	int imageFormat = 0;
	int imageSortType = 0;
	int imageView = 0;
	int albumSortType = 0;

	//根据配置读取结果设置下拉框选项，注意先不要连接信号，初始化时设置下拉框避免画面更新。
	ui.imageOptionBar->setConfig(imageFormat, imageSortType, imageView);
	ui.albumOptionBar->setConfig(albumSortType);
	



	QSqlQuery albumQuery = m_selectAllAlbumsFunc(imageSortType);
	ui.albumScrollWidget->refresh(albumQuery);

	int albumID = m_selectLastAccessedAlbumIDFunc();
	QSqlQuery imageQuery = m_selectImagesWithAlbumIDFunc(albumID, 0);
	ui.imageScrollWidget->refresh(imageQuery, 0, 0);
}

PreviewScene::~PreviewScene()
{
	if (m_closeDatabaseFunc)
		m_closeDatabaseFunc();
}

void PreviewScene::onSettingsBtnClicked()
{

}

void PreviewScene::onMaxBtnClicked(bool isMax)
{
	if (isMax)
		setGeometry(m_rect);
	else
	{
		m_rect = geometry();
		showMaximized();
	}
}

bool PreviewScene::loadLibrary()
{
	QLibrary myLibrary(QCoreApplication::applicationDirPath() +
		QDir::separator() + "DatabaseManager.dll");

	if (myLibrary.load())
	{
		m_openDatabaseFunc = (OpenDatabaseFunc)myLibrary.resolve("OpenDatabase");
		m_closeDatabaseFunc = (CloseDatabaseFunc)myLibrary.resolve("CloseDatabase");
		m_insertAlbumFunc = (InsertAlbumFunc)myLibrary.resolve("InsertAlbum");
		m_insertImageFunc = (InsertImageFunc)myLibrary.resolve("InsertImage");
		m_deleteAlbumFunc = (DeleteAlbumFunc)myLibrary.resolve("DeleteAlbum");
		m_deleteImageFunc = (DeleteImageFunc)myLibrary.resolve("DeleteImage");
		m_selectLastAccessedAlbumIDFunc = (SelectLastAccessedAlbumIDFunc)myLibrary.resolve("SelectLastAccessedAlbumID");
		m_selectImagesWithAlbumIDFunc = (SelectImagesWithAlbumIDFunc)myLibrary.resolve("SelectImagesWithAlbumID");
		m_selectAllAlbumsFunc = (SelectAllAlbumsFunc)myLibrary.resolve("SelectAllAlbums");
		return m_openDatabaseFunc && m_closeDatabaseFunc &&
			m_insertAlbumFunc && m_insertImageFunc &&
			m_deleteAlbumFunc && m_deleteImageFunc &&
			m_selectLastAccessedAlbumIDFunc &&
			m_selectImagesWithAlbumIDFunc &&
			m_selectAllAlbumsFunc;
	}
	return false;
}