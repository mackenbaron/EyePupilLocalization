#include "eyepupillocalization.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon("./Resources/eye.ico"));
	EyePupilLocalization w;
	w.show();
	return a.exec();
}
