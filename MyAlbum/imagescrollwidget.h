#pragma once

#include <QWidget>
#include <QSqlQuery>

class ImageScrollWidget : public QWidget
{
	Q_OBJECT

public:
	ImageScrollWidget(QSqlQuery& query, int sortType, int view, QWidget* parent = nullptr);
	~ImageScrollWidget();

};
