#pragma once

#include <QScrollArea>

class ImageScrollArea  : public QScrollArea
{
	Q_OBJECT

public:
	ImageScrollArea(QWidget *parent = nullptr);
	~ImageScrollArea();
};
