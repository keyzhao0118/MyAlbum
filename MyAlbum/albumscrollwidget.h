#pragma once

#include <QWidget>
#include <QSqlQuery>

class AlbumScrollWidget : public QWidget
{
	Q_OBJECT

public:
	AlbumScrollWidget(QSqlQuery& query, int sortType, QWidget* parent = nullptr);
	~AlbumScrollWidget();
};
