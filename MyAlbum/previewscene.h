#pragma once

#include <QtWidgets/QWidget>
#include "ui_previewscene.h"
#include <QSqlQuery>

class PreviewScene : public QWidget
{
	Q_OBJECT

public:
	typedef bool (*OpenDatabaseFunc)(const QString&);
	typedef void (*CloseDatabaseFunc)();
	typedef int (*InsertAlbumFunc)(const QString&, const QDateTime&, const QDateTime&);
	typedef int (*InsertImageFunc)(int, const QString&, const QString&, int,
		const QString&, const QDateTime&);
	typedef bool (*DeleteAlbumFunc)(int);
	typedef bool (*DeleteImageFunc)(int);
	typedef int (*SelectLastAccessedAlbumIDFunc)();
	typedef QSqlQuery (*SelectImagesWithAlbumIDFunc)(int, int, int);
	typedef QSqlQuery (*SelectAllAlbumsFunc)(int);

	PreviewScene(QWidget *parent = nullptr);
	~PreviewScene();

private slots:
	void onSettingsBtnClicked();
	void onMaxBtnClicked(bool isMax);

	void refreshAlbum();
	void refreshImage();

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
	SelectLastAccessedAlbumIDFunc m_selectLastAccessedAlbumIDFunc;
	SelectImagesWithAlbumIDFunc m_selectImagesWithAlbumIDFunc;
	SelectAllAlbumsFunc m_selectAllAlbumsFunc;
};
