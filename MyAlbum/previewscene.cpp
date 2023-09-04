#include "previewscene.h"

//#include <QtSql/qsqlquery.h>

PreviewScene::PreviewScene(DatabaseManager& dbMgr, QWidget* parent)
	: m_dbMgr(dbMgr), QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.customTitle, SIGNAL(settingsBtnClicked()), this, SLOT(onSettingsBtnClicked()));
	connect(ui.customTitle, SIGNAL(minBtnClicked()), this, SLOT(showMinimized()));
	connect(ui.customTitle, SIGNAL(maxBtnClicked(bool)), this, SLOT(onMaxBtnClicked(bool)));
	connect(ui.customTitle, SIGNAL(closeBtnClicked()), this, SLOT(close()));
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