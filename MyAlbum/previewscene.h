#pragma once

#include <QtWidgets/QWidget>
#include "ui_previewscene.h"

class PreviewScene : public QWidget
{
	Q_OBJECT

public:
	typedef bool (*OpenDatabaseFunc)(const QString&);
	typedef void (*CloseDatabaseFunc)();
	typedef int (*InsertAlbumFunc)(const QString& name, const QDateTime& lastAccessed, const QDateTime& createdAt);
	typedef int (*InsertImageFunc)(int albumID, const QString& path, const QString& type, int size,
		const QString& resolution, const QDateTime& importedAt);
	typedef bool (*DeleteAlbumFunc)(int albumID);
	typedef bool (*DeleteImageFunc)(int imageID);

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
	InsertAlbumFunc m_insertAlbumFunc;
	InsertImageFunc m_insertImageFunc;
	DeleteAlbumFunc m_deleteAlbumFunc;
	DeleteImageFunc m_deleteImageFunc;
};
