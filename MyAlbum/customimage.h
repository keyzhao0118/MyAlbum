#pragma once

#include <QWidget>
#include "ui_customimage.h"

enum class ViewSize
{
	Large,
	Medium,
	Small
};

class CustomImage : public QWidget
{
	Q_OBJECT

public:
	CustomImage(ViewSize viewSize, const QPixmap& pixmap, QWidget* parent = nullptr);
	~CustomImage();

	void paintEvent(QPaintEvent* event) override;

private:
	Ui::CustomImageClass ui;
	QPixmap m_pixmap;
};
