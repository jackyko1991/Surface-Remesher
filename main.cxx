#include <QApplication>

#include <surfaceRemesher.h>

int main(int argc, char** argv)
{
	// qapplication
	QApplication app(argc, argv);
	SurfaceRemesher surfaceRemesher;
	surfaceRemesher.show();

	return app.exec();
}