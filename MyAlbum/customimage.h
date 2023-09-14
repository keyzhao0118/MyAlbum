#pragma once

#include <QWidget>

enum class ViewSize
{
	Small,
	Medium,
	Large
};

class CustomImage : public QWidget
{
	Q_OBJECT

public:
	CustomImage(ViewSize viewSize, const QPixmap& pixmap, QWidget* parent = nullptr);
	~CustomImage();

	void paintEvent(QPaintEvent* event) override;

private:
	QPixmap m_pixmap;
};
