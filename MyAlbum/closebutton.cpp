#include "closebutton.h"

CloseButton::CloseButton(QWidget *parent)
	: QPushButton(parent)
{
	setIcon(QIcon(":/PreviewScene/image/按钮-关闭.svg"));
}

CloseButton::~CloseButton()
{}

void CloseButton::enterEvent(QEnterEvent* event)
{
	setIcon(QIcon(":/PreviewScene/image/按钮-关闭-selected.svg"));
	QPushButton::enterEvent(event);
}

void CloseButton::leaveEvent(QEvent* event)
{
	setIcon(QIcon(":/PreviewScene/image/按钮-关闭.svg"));
	QPushButton::leaveEvent(event);
}
