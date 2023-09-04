#pragma once

#include <QtWidgets/QWidget>
#include "ui_previewscene.h"
#include "databasemanager.h"

class PreviewScene : public QWidget
{
	Q_OBJECT

public:
	PreviewScene(DatabaseManager& dbMgr ,QWidget *parent = nullptr);
	~PreviewScene();

private slots:
	void onSettingsBtnClicked();
	void onMaxBtnClicked(bool isMax);

private:
	Ui::PreviewSceneClass ui;
	QRect m_rect;

	DatabaseManager& m_dbMgr;
};
