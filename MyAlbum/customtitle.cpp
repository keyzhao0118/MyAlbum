#include "customtitle.h"
#include <qevent.h>

CustomTitle::CustomTitle(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::CustomTitleClass())
	, m_isMax(false)
{
	ui->setupUi(this);
	setFixedHeight(30);

	ui->logoLab->setPixmap(QPixmap(":/PreviewScene/image/logo.svg"));
	ui->appNameLab->setText("我的相册");
	ui->settingsBtn->setIcon(QIcon(":/PreviewScene/image/按钮-设置.svg"));
	ui->minBtn->setIcon(QIcon(":/PreviewScene/image/按钮-最小化.svg"));
	ui->maxBtn->setIcon(QIcon(":/PreviewScene/image/按钮-最大化.svg"));
	
	connect(ui->settingsBtn, SIGNAL(clicked()), this, SIGNAL(settingsBtnClicked()));
	connect(ui->minBtn, SIGNAL(clicked()), this, SIGNAL(minBtnClicked()));
	connect(ui->maxBtn, SIGNAL(clicked()), this, SLOT(onMaxBtnClicked()));
	connect(ui->closeBtn, SIGNAL(clicked()), this, SIGNAL(closeBtnClicked()));
}

CustomTitle::~CustomTitle()
{
	delete ui;
}

void CustomTitle::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_dragPosition = event->globalPos() - parentWidget()->geometry().topLeft();
		event->accept();
	}
}
void CustomTitle::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		parentWidget()->move(event->globalPos() - m_dragPosition);
		event->accept();
	}
}

void CustomTitle::onMaxBtnClicked()
{
	emit maxBtnClicked(m_isMax);
	m_isMax = !m_isMax;
	if (m_isMax)
		ui->maxBtn->setIcon(QIcon(":/PreviewScene/image/按钮-恢复.svg"));
	else
		ui->maxBtn->setIcon(QIcon(":/PreviewScene/image/按钮-最大化.svg"));
	
}
