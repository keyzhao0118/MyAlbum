#include "previewscene.h"
#include <QDir>
#include <QLibrary>
#include <QMessageBox>
#include <QImageReader>

PreviewScene::PreviewScene(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.customTitle, SIGNAL(settingsBtnClicked()), this, SLOT(onSettingsBtnClicked()));
	connect(ui.customTitle, SIGNAL(minBtnClicked()), this, SLOT(showMinimized()));
	connect(ui.customTitle, SIGNAL(maxBtnClicked(bool)), this, SLOT(onMaxBtnClicked(bool)));
	connect(ui.customTitle, SIGNAL(closeBtnClicked()), this, SLOT(close()));

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

	QSqlQuery albumQuery = m_selectAllAlbumsFunc(0);//默认排序类型应该通过配置中心管理
	refreshAlbumScrollWidget(albumQuery);

	int albumID = m_selectLastAccessedAlbumIDFunc();
	QSqlQuery imageQuery = m_selectImagesWithAlbumIDFunc(albumID, 0);
	refreshImageScrollWidget(imageQuery);
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

void PreviewScene::refreshImageScrollWidget(QSqlQuery& query)
{
	QVBoxLayout* vLayout = new QVBoxLayout;
	while (query.next())
	{
		QImageReader reader(query.value("Path").toString());
		QSize originalSize = reader.size();
		QSize newSize = originalSize.scaled(300, 300, Qt::KeepAspectRatio);
		reader.setScaledSize(newSize);

		QLabel* lab = new QLabel;
		lab->setPixmap(QPixmap::fromImageReader(&reader));
		vLayout->addWidget(lab);
	}
	ui.imageScrollWidget->setLayout(vLayout);
}

void PreviewScene::refreshAlbumScrollWidget(QSqlQuery& query)
{
	
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