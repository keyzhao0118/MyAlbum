#pragma once

#include <qpushbutton.h>

class CloseButton  : public QPushButton
{
	Q_OBJECT

public:
	CloseButton(QWidget *parent = nullptr);
	~CloseButton();

protected:
	void enterEvent(QEnterEvent* event)override;
	void leaveEvent(QEvent* event)override;
};
