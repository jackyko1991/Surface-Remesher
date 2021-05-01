#ifndef SURFACEREMESHER_H
#define SURFACEREMESHER_H

#include <QMainWindow>
#include <ui_surface_remesher.h>

class Ui_MainWindow;

class SurfaceRemesher : public QMainWindow
{
	Q_OBJECT
public:
	SurfaceRemesher();
	~SurfaceRemesher();


public slots:
	void pushButtonBrowseClicked();
	void pushButtonComputeClicked();

private:
	// Designer form
	Ui_MainWindow *ui;
	void enableUi(bool);
};

#endif // ! SURFACEREMESHER_H
