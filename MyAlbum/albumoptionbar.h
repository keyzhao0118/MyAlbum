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

private:
	QPushButton* m_oneClickDeleteBtn;
	QPushButton* m_selectAllBtn;
	QComboBox* m_sortComboBox;
};
