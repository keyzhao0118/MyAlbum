#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QFocusEvent>

class AlbumNameEdit : public QLineEdit
{
	Q_OBJECT

public:
	AlbumNameEdit(QWidget* parent = nullptr);
	~AlbumNameEdit();

protected:
	void focusInEvent(QFocusEvent* event)override;
	void focusOutEvent(QFocusEvent* event)override;

private:
	QString m_originAlbumName;
};

class ImageOptionBar : public QWidget
{
	Q_OBJECT

public:
	ImageOptionBar(QWidget* parent = nullptr);
	~ImageOptionBar();

	void setConfig(int sort, int format, int view);

	int curFormat()const;
	int curSortType()const;
	int curView()const;

signals:
	void albumNameChanged(const QString&);
	void albumCoverChanged();
	void importImages();
	void deleteImages();
	void selectAll();
	void formatChanged(int);
	void sortChanged(int);
	void viewChanged(int);


public slots:
	void setAlbumNameBtnClicked();
	void changeAlbumName();

private:
	AlbumNameEdit* m_albumNameEdit;
	QPushButton* m_setAlbumNameBtn;
	QPushButton* m_setAlbumCoverBtn;

	QPushButton* m_importImageBtn;
	QPushButton* m_oneClickDeleteBtn;
	QPushButton* m_selectAllBtn;
	
	QComboBox* m_formatComboBox;
	QComboBox* m_sortComboBox;
	QComboBox* m_viewComboBox;
};
