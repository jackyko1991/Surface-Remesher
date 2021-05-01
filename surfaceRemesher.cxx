#include "surfaceRemesher.h"
#include "ui_surface_remesher.h"

#include "QPushButton"
#include "QFileDialog"
#include "QFile"

#include "iostream"

#include "remesh_core.h"

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
		std::cout << "File not exist!!!" << std::endl;
		return;
	}

	// check max size > min size
	if (this->ui->doubleSpinBoxMaxCellArea < this->ui->doubleSpinBoxMinCellArea)
	{
		std::cout << "Max cell area < Min cell area, abort" << std::endl;
		return;
	}
		

	// set output location
	QString outputFileName = QFileDialog::getSaveFileName(this,
		tr("Remeshed Surface Output Location"), "",
		tr("STL Files (*.stl)"));

	if (outputFileName == "")
		return;

	// lock ui
	this->enableUi(false);

	RemeshCore remeshCore;
	remeshCore.SetInputStlPath(this->ui->textEdit->toPlainText());
	remeshCore.SetOutputStlPath(outputFileName);
	remeshCore.SetMinArea(this->ui->doubleSpinBoxMinCellArea->value());
	remeshCore.SetMaxArea(this->ui->doubleSpinBoxMaxCellArea->value());
	remeshCore.SetNumberOfIterations(this->ui->spinBoxIterations->value());
	remeshCore.Run();

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

