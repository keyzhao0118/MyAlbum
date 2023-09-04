#include "previewscene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PreviewScene w;
	w.setWindowFlags(Qt::CustomizeWindowHint);
	w.show();
	return a.exec();
}
