#pragma once

#include <QScrollArea>

class AlbumScrollArea  : public QScrollArea
{
	Q_OBJECT

public:
	AlbumScrollArea(QWidget* parent = nullptr);
	~AlbumScrollArea();
};
