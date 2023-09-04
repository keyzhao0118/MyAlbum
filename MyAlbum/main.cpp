#include "previewscene.h"
#include <QtWidgets/QApplication>
#include "databasemanager.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString databaseFilePath = QCoreApplication::applicationDirPath() +
		QDir::separator() + "mydatabase.db";
	DatabaseManager dbMgr(databaseFilePath);
	if (!dbMgr.initDatabase())
	{
		QMessageBox::warning(nullptr, "数据库", "数据库初始化失败");
		return -1;
	}
	PreviewScene w(dbMgr);
	w.setWindowFlags(Qt::CustomizeWindowHint);
	
	w.show();
	return a.exec();
}
