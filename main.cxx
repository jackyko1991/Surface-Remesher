#include "vtkSTLReader.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkvmtkPolyDataSurfaceRemeshing.h"
#include "vtkSTLWriter.h"

int main()
{
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName("D:/projects/surface_remeshing/surface/skin_marker.stl");
	reader->Update();

	vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing> remesher = vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing>::New();
	remesher->SetInputData(reader->GetOutput());
	remesher->SetMinArea(0.001);
	remesher->SetMaxArea(0.01);
	remesher->SetNumberOfIterations(10);
	remesher->Update();

	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName("D:/projects/surface_remeshing/surface/skin_marker_remesh.stl");
	writer->SetInputData(remesher->GetOutput());
	writer->Write();
}