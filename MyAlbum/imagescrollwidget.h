#pragma once

#include <QWidget>
#include <QSqlQuery>

class ImageScrollWidget : public QWidget
{
	Q_OBJECT

public:
	ImageScrollWidget(QWidget *parent = nullptr);
	~ImageScrollWidget();

public slots:
	void refresh(QSqlQuery& query, int view, int sort);

};
