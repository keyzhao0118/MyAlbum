#include "albumoptionbar.h"
#include <qlayout.h>

AlbumOptionBar::AlbumOptionBar(QWidget *parent)
	: QWidget(parent)
{
	m_albumNameLab = new QLabel("默认相册", this);
	m_setAlbumNameBtn = new QPushButton("设置相册名称", this);
	m_setAlbumCoverBtn = new QPushButton("设置相册封面",this);
	QHBoxLayout* hboxLayout = new QHBoxLayout(this);
	hboxLayout->addWidget(m_albumNameLab);
	hboxLayout->addWidget(m_setAlbumNameBtn);
	hboxLayout->addWidget(m_setAlbumCoverBtn);

	hboxLayout->addSpacerItem(new QSpacerItem(
		40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

	m_importPictureBtn = new QPushButton("导入图片", this);
	m_oneClickDeleteBtn = new QPushButton("一键删除", this);
	m_selectAllBtn = new QPushButton("全选按钮", this);
	hboxLayout->addWidget(m_importPictureBtn);
	hboxLayout->addWidget(m_oneClickDeleteBtn);
	hboxLayout->addWidget(m_selectAllBtn);

	hboxLayout->addSpacerItem(new QSpacerItem(
		40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

	m_typeComboBox = new QComboBox(this);
	m_typeComboBox->addItem("全部类型");
	m_typeComboBox->addItem("JPG");
	m_typeComboBox->addItem("PNG");
	m_typeComboBox->addItem("GIF");
	m_typeComboBox->addItem("其他格式");

	m_sortComboBox = new QComboBox(this);
	m_sortComboBox->addItem("最近访问");
	m_sortComboBox->addItem("全部时间");

	m_viewComboBox = new QComboBox(this);
	m_viewComboBox->addItem("小视图");
	m_viewComboBox->addItem("中视图");
	m_viewComboBox->addItem("大视图");

	hboxLayout->addWidget(m_typeComboBox);
	hboxLayout->addWidget(m_sortComboBox);
	hboxLayout->addWidget(m_viewComboBox);

	setLayout(hboxLayout);
}

AlbumOptionBar::~AlbumOptionBar()
{}
