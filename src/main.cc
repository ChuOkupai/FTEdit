#include "FTEdit.hh"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QApplication::setStyle("fusion");
	MainWindow window;

	window.show();
	return app.exec();
}
