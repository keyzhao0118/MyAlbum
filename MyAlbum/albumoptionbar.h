#pragma once

#include <QWidget>
#include <qpushbutton.h>
#include <qcombobox.h>

class AlbumOptionBar : public QWidget
{
	Q_OBJECT

public:
	AlbumOptionBar(QWidget *parent = nullptr);
	~AlbumOptionBar();

	void setConfig(int sort);
	int curSortType()const;
	int activeAlbumID()const;
	void setActiveAlbumID(int albumID);

signals:
	void sortChanged();
	void deleteAlbums();
	void selectAll();

private:
	QPushButton* m_oneClickDeleteBtn;
	QPushButton* m_selectAllBtn;
	QComboBox* m_sortComboBox;

	int m_activeAlbumID;
};
