#pragma once

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcombobox.h>

class AlbumOptionBar : public QWidget
{
	Q_OBJECT

public:
	AlbumOptionBar(QWidget *parent);
	~AlbumOptionBar();

private:
	QLabel* m_albumNameLab;
	QPushButton* m_setAlbumNameBtn;
	QPushButton* m_setAlbumCoverBtn;

	QPushButton* m_importPictureBtn;
	QPushButton* m_oneClickDeleteBtn;
	QPushButton* m_selectAllBtn;
	
	QComboBox* m_typeComboBox;
	QComboBox* m_sortComboBox;
	QComboBox* m_viewComboBox;
};
