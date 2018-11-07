#include "surfaceRemesher.h"
#include "ui_surface_remesher.h"

#include "QPushButton"
#include "QFileDialog"
#include "QFile"

#include "vtkSTLReader.h"
#include "vtkSmartPointer.h"
#include "vtkPolyData.h"
#include "vtkvmtkPolyDataSurfaceRemeshing.h"
#include "vtkSTLWriter.h"


SurfaceRemesher::SurfaceRemesher()
{
	this->ui = new Ui_MainWindow;
	this->ui->setupUi(this);

	connect(this->ui->pushButtonBrowse, SIGNAL(clicked()), this, SLOT(pushButtonBrowseClicked()));
	connect(this->ui->pushButtonCompute, SIGNAL(clicked()), this, SLOT(pushButtonComputeClicked()));
}

SurfaceRemesher::~SurfaceRemesher() 
{

}

void SurfaceRemesher::pushButtonComputeClicked()
{
	// check input file existence
	if (!QFile::exists(this->ui->textEdit->toPlainText()))
	{
		return;
	}

	// check max size > min size
	if (this->ui->doubleSpinBoxMaxCellArea < this->ui->doubleSpinBoxMinCellArea)
		return;

	// set output location
	QString outputFileName = QFileDialog::getSaveFileName(this,
		tr("Remeshed Surface Output Location"), "",
		tr("STL Files (*.stl)"));

	if (outputFileName == "")
		return;

	// lock ui
	this->enableUi(false);

	// actual computation
	vtkSmartPointer<vtkSTLReader> reader = vtkSmartPointer<vtkSTLReader>::New();
	reader->SetFileName(this->ui->textEdit->toPlainText().toStdString().c_str());
	reader->Update();

	vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing> remesher = vtkSmartPointer<vtkvmtkPolyDataSurfaceRemeshing>::New();
	remesher->SetInputData(reader->GetOutput());
	remesher->SetMinArea(this->ui->doubleSpinBoxMinCellArea->value());
	remesher->SetMaxArea(this->ui->doubleSpinBoxMaxCellArea->value());
	remesher->SetNumberOfIterations(this->ui->spinBoxIterations->value());
	remesher->Update();

	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();
	writer->SetFileName(outputFileName.toStdString().c_str());
	writer->SetInputData(remesher->GetOutput());
	writer->Write();

	// unlock ui
	this->enableUi(true);
}

void SurfaceRemesher::enableUi(bool enable)
{
	this->ui->pushButtonBrowse->setEnabled(enable);

	if (enable)
	{
		this->ui->pushButtonCompute->setText("Compute and Save");
		this->ui->pushButtonCompute->setEnabled(enable);
	}
	else 
	{
		this->ui->pushButtonCompute->setText("Computing...");
		this->ui->pushButtonCompute->setEnabled(enable);
	}
	
	this->ui->textEdit->setEnabled(enable);
	this->ui->doubleSpinBoxMaxCellArea->setEnabled(enable);
	this->ui->doubleSpinBoxMinCellArea->setEnabled(enable);
	this->ui->spinBoxIterations->setEnabled(enable);
}

void SurfaceRemesher::pushButtonBrowseClicked()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Select Surface File"), this->ui->textEdit->toPlainText(), tr("STL Files (*.stl)"));
	if (fileName != "")
	{
		std::cout << fileName.toStdString() << std::endl;
		this->ui->textEdit->setText(fileName);
	}
}

