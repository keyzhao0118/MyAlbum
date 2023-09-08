#pragma once

#include <QWidget>
#include <QSqlQuery>

class AlbumScrollWidget : public QWidget
{
	Q_OBJECT

public:
	AlbumScrollWidget(QWidget* parent = nullptr);
	~AlbumScrollWidget();

public slots:
	void refresh(QSqlQuery& query);
};
