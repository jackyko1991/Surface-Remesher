#include "remesh_core.h"

#include "vtkSTLReader.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkvmtkPolyDataSurfaceRemeshing.h"
#include "vtkSTLWriter.h"

RemeshCore::RemeshCore()
{


}

RemeshCore::~RemeshCore()
{

}

void RemeshCore::SetInputStlPath(QString path)
{
	m_inputStlPath = path;
}

void RemeshCore::SetOutputStlPath(QString path)
{
	m_outputStlPath = path;
}

void RemeshCore::SetMinArea(double minArea)
{
	m_minArea = minArea;
}

void RemeshCore::SetMaxArea(double maxArea)
{
	m_maxArea = maxArea;
}

void RemeshCore::SetNumberOfIterations(int itr)
{
	m_itr = itr;
}


void RemeshCore::Run()
{
	std::cout << "Resample surface " << m_inputStlPath.toStdString() << std::endl;
	std::cout << "min area: " << m_minArea << std::endl;
	std::cout << "max area: " << m_maxArea << std::endl;

	// actual computation
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(m_inputStlPath.toStdString().c_str());
	reader->Update();

	vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing> remesher = vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing>::New();
	remesher->SetInputData(reader->GetOutput());
	remesher->SetMinArea(m_minArea);
	remesher->SetMaxArea(m_maxArea);
	remesher->SetNumberOfIterations(m_itr);
	remesher->Update();

	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(m_outputStlPath.toStdString().c_str());
	writer->SetInputData(remesher->GetOutput());
	writer->Write();
	std::cout << "Resampled surface saved at " << m_outputStlPath.toStdString() << std::endl;
}
