#include "previewscene.h"
#include <QDir>
#include <QLibrary>

PreviewScene::PreviewScene(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.customTitle, SIGNAL(settingsBtnClicked()), this, SLOT(onSettingsBtnClicked()));
	connect(ui.customTitle, SIGNAL(minBtnClicked()), this, SLOT(showMinimized()));
	connect(ui.customTitle, SIGNAL(maxBtnClicked(bool)), this, SLOT(onMaxBtnClicked(bool)));
	connect(ui.customTitle, SIGNAL(closeBtnClicked()), this, SLOT(close()));

	if (loadLibrary())
	{
		m_openDatabaseFunc(QCoreApplication::applicationDirPath() +
			QDir::separator() + "mydatabase.db");
	}
}

PreviewScene::~PreviewScene()
{}

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
		m_addAlbumFunc = (AddAlbumFunc)myLibrary.resolve("AddAlbum");
		
		return m_openDatabaseFunc && m_addAlbumFunc;
	}
	return false;
}