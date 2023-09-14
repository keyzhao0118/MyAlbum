#include "albumoptionbar.h"
#include <QHBoxLayout>
#include <QLabel>

AlbumOptionBar::AlbumOptionBar(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(50);
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->addWidget(new QLabel("相册集"));

	hLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Fixed, QSizePolicy::Minimum));
	hLayout->addSpacerItem(new QSpacerItem(
		50, 50, QSizePolicy::Expanding, QSizePolicy::Minimum));

	m_oneClickDeleteBtn = new QPushButton("一键删除", this);
	m_selectAllBtn = new QPushButton("全选按钮", this);
	m_sortComboBox = new QComboBox(this);
	m_sortComboBox->addItem("最近访问");
	m_sortComboBox->addItem("全部时间");
	hLayout->addWidget(m_oneClickDeleteBtn);
	hLayout->addWidget(m_selectAllBtn);
	hLayout->addWidget(m_sortComboBox);
	
	setLayout(hLayout);

	connect(m_sortComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(sortChanged()));
	connect(m_oneClickDeleteBtn, SIGNAL(clicked()), this, SIGNAL(deleteAlbums()));
	connect(m_selectAllBtn, SIGNAL(clicked()), this, SIGNAL(selectAll()));
}

AlbumOptionBar::~AlbumOptionBar()
{}

void AlbumOptionBar::setConfig(int sort)
{
	m_sortComboBox->setCurrentIndex(sort);
}

int AlbumOptionBar::curSortType() const
{
	return m_sortComboBox->currentIndex();
}

int AlbumOptionBar::activeAlbumID() const
{
	return m_activeAlbumID;
}

void AlbumOptionBar::setActiveAlbumID(int albumID)
{
	m_activeAlbumID = albumID;
}
