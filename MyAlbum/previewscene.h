﻿#pragma once

#include <QtWidgets/QWidget>
#include "ui_previewscene.h"

class PreviewScene : public QWidget
{
	Q_OBJECT

public:
	typedef bool (*OpenDatabaseFunc)(const QString&);
	typedef void (*CloseDatabaseFunc)();
	typedef int (*AddAlbumFunc)(const QString&);
	typedef int (*AddImageFunc)(int, const QString&);
	PreviewScene(QWidget *parent = nullptr);
	~PreviewScene();

private slots:
	void onSettingsBtnClicked();
	void onMaxBtnClicked(bool isMax);

private:
	Ui::PreviewSceneClass ui;
	QRect m_rect;

	bool loadLibrary();
	OpenDatabaseFunc m_openDatabaseFunc;
	CloseDatabaseFunc m_closeDatabaseFunc;
	AddAlbumFunc m_addAlbumFunc;
	AddImageFunc m_addImageFunc;
};
