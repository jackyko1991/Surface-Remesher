#ifndef __REMESH_CORE_H__
#define __REMESH_CORE_H__

#include "QObject"

class RemeshCore : public QObject
{
	Q_OBJECT

public:
	RemeshCore();
	~RemeshCore();

	void SetInputStlPath(QString);
	void SetOutputStlPath(QString);
	void SetMinArea(double minArea);
	void SetMaxArea(double maxArea);
	void SetNumberOfIterations(int itr);
	void Run();

private:

	QString m_inputStlPath;
	QString m_outputStlPath;
	double m_minArea = 0.01;
	double m_maxArea = 0.01;
	int m_itr = 10;
};

#endif // ! __REMESH_CORE_H__
