#include "imageoptionbar.h"
#include <QLayout>

ImageOptionBar::ImageOptionBar(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(50);
	m_albumNameEdit = new AlbumNameEdit(this);
	m_albumNameEdit->setReadOnly(true);
	m_setAlbumNameBtn = new QPushButton(this);
	m_setAlbumNameBtn->setIcon(QIcon(":/PreviewScene/image/编辑相册名字.svg"));
	m_setAlbumCoverBtn = new QPushButton("设置相册封面",this);
	//m_setAlbumCoverBtn->setEnabled(false);
	QHBoxLayout* hboxLayout = new QHBoxLayout(this);
	hboxLayout->addWidget(m_albumNameEdit);
	hboxLayout->addWidget(m_setAlbumNameBtn);
	hboxLayout->addWidget(m_setAlbumCoverBtn);

	hboxLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Fixed, QSizePolicy::Minimum));
	hboxLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Expanding, QSizePolicy::Minimum));

	m_importImageBtn = new QPushButton("导入图片", this);
	m_oneClickDeleteBtn = new QPushButton("一键删除", this);
	//m_oneClickDeleteBtn->setEnabled(false);
	m_selectAllBtn = new QPushButton("全选按钮", this);
	hboxLayout->addWidget(m_importImageBtn);
	hboxLayout->addWidget(m_oneClickDeleteBtn);
	hboxLayout->addWidget(m_selectAllBtn);

	hboxLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Fixed, QSizePolicy::Minimum));
	hboxLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Expanding, QSizePolicy::Minimum));

	m_formatComboBox = new QComboBox(this);
	m_formatComboBox->addItem("全部格式");
	m_formatComboBox->addItem("JPG");
	m_formatComboBox->addItem("PNG");
	m_formatComboBox->addItem("GIF");
	m_formatComboBox->addItem("其他格式");

	m_sortComboBox = new QComboBox(this);
	m_sortComboBox->addItem("最近访问");
	m_sortComboBox->addItem("全部时间");

	m_viewComboBox = new QComboBox(this);
	m_viewComboBox->addItem("小视图");
	m_viewComboBox->addItem("中视图");
	m_viewComboBox->addItem("大视图");

	hboxLayout->addWidget(m_formatComboBox);
	hboxLayout->addWidget(m_sortComboBox);
	hboxLayout->addWidget(m_viewComboBox);

	setLayout(hboxLayout);

	connect(m_setAlbumNameBtn, SIGNAL(clicked()), this, SLOT(setAlbumNameBtnClicked()));
	connect(m_albumNameEdit, SIGNAL(returnPressed()), this, SLOT(changeAlbumName()));
	
	connect(m_albumNameEdit, SIGNAL(textChanged(const QString&)), this, 
		SIGNAL(albumNameChanged(const QString&)));

	connect(m_setAlbumCoverBtn, SIGNAL(clicked()), this, SIGNAL(albumCoverChanged()));
	connect(m_importImageBtn, SIGNAL(clicked()), this, SIGNAL(importImages()));
	connect(m_oneClickDeleteBtn, SIGNAL(clicked()), this, SIGNAL(deleteImages()));
	connect(m_selectAllBtn, SIGNAL(clicked()), this, SIGNAL(selectAll()));

	connect(m_formatComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(formatChanged(int)));
	connect(m_sortComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(sortChanged(int)));
	connect(m_viewComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(viewChanged(int)));
}

ImageOptionBar::~ImageOptionBar()
{}

void ImageOptionBar::setConfig(int sort, int format, int view)
{
	m_sortComboBox->setCurrentIndex(sort);
	m_formatComboBox->setCurrentIndex(format);
	m_viewComboBox->setCurrentIndex(view);
}

void ImageOptionBar::setAlbumNameBtnClicked()
{
	m_albumNameEdit->setReadOnly(false);
	m_albumNameEdit->setFocus();
}

void ImageOptionBar::changeAlbumName()
{
	QString name = m_albumNameEdit->text();
	m_albumNameEdit->clearFocus();
	m_albumNameEdit->setText(name);
}

//-------Class AlbumNameEdit-------------

AlbumNameEdit::AlbumNameEdit(QWidget* parent /*= nullptr*/)
{}

AlbumNameEdit::~AlbumNameEdit()
{}

void AlbumNameEdit::focusInEvent(QFocusEvent* event)
{
	m_originAlbumName = text();
	QLineEdit::focusInEvent(event);
}

void AlbumNameEdit::focusOutEvent(QFocusEvent* event)
{
	//当焦点离开，设为不可编辑，并且恢复原始文本
	setReadOnly(true);
	setText(m_originAlbumName);
	QLineEdit::focusOutEvent(event);
}
