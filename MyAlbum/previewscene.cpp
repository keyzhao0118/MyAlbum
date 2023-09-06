#include "previewscene.h"
#include <QDir>
#include <QLibrary>
#include <QMessageBox>

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

	//ToDo：展示Albums表中的全部的Album记录
	//ToDo：从Albums表查询最近访问的Album的ID，查询所有属于该Album的Images，展示这些Images

	//ToDo：查询结果传给另外一个线程，由专门的线程更新图片预览界面和相册预览界面

	//每次新建相册、
}

PreviewScene::~PreviewScene()
{
	if (!m_closeDatabaseFunc)
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
		m_addAlbumFunc = (AddAlbumFunc)myLibrary.resolve("AddAlbum");
		m_addImageFunc = (AddImageFunc)myLibrary.resolve("AddImage");
		return m_openDatabaseFunc && m_closeDatabaseFunc && m_addAlbumFunc && m_addImageFunc;
	}
	return false;
}