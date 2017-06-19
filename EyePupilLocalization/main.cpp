#include "eyepupillocalization.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EyePupilLocalization w;
	w.show();
	return a.exec();
}
