#pragma once

#include <QWidget>
#include "ui_customtitle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomTitleClass; };
QT_END_NAMESPACE

class CustomTitle : public QWidget
{
	Q_OBJECT

public:
	CustomTitle(QWidget *parent = nullptr);
	~CustomTitle();

	void mousePressEvent(QMouseEvent* event)override;
	void mouseMoveEvent(QMouseEvent* event)override;
signals:
	void settingsBtnClicked();
	void minBtnClicked();
	void maxBtnClicked(bool isMax);
	void closeBtnClicked();

private slots:
	void onMaxBtnClicked();

private:
	Ui::CustomTitleClass *ui;

	QPoint m_dragPosition;

	bool m_isMax;

};
