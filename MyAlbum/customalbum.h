#pragma once

#include <QWidget>

class CustomAlbum  : public QWidget
{
	Q_OBJECT

public:
	CustomAlbum(const QString& albumName, const QPixmap& pixmap, QWidget* parent = nullptr);
	~CustomAlbum();

	void paintEvent(QPaintEvent* event) override;

private:
	QPixmap m_pixmap;
};
