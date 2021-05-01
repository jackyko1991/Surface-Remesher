#include <QApplication>
#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QDir>

#include <surfaceRemesher.h>
#include <remesh_core.h>

#include <iostream>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char** argv)
{

	// qapplication
	QApplication app(argc, argv);
	QApplication::setApplicationName("Surface Remesher");
	QApplication::setApplicationVersion("1.0");

	if (argc == 1)
	{
		SurfaceRemesher surfaceRemesher;
		surfaceRemesher.show();
		return app.exec();
	}

	QCommandLineParser parser;
	parser.setApplicationDescription("Resample STL with provided triangle size");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to process."));
	parser.addPositionalArgument("output", QCoreApplication::translate("main", "Output file location."));

	//// A boolean option with a single name (-p)
	//QCommandLineOption showProgressOption("p", QCoreApplication::translate("main", "Show progress during copy"));
	//parser.addOption(showProgressOption);

	//// A boolean option with multiple names (-f, --force)
	//QCommandLineOption forceOption(QStringList() << "f" << "force",
	//	QCoreApplication::translate("main", "Overwrite existing files."));
	//parser.addOption(forceOption);

	////// An option with a value
	//QCommandLineOption targetDirectoryOption(QStringList() << "t" << "target-directory",
	//	QCoreApplication::translate("main", "Copy all source files into <directory>."),
	//	QCoreApplication::translate("main", "directory"));
	//parser.addOption(targetDirectoryOption);

	// option for min cell area
	QCommandLineOption minCellAreaOption(QStringList() << "m" << "min",
		QCoreApplication::translate("main", "Minimum triangel area (default=0.01)"),
		QCoreApplication::translate("main", "min_area"),
		"0.01");
	parser.addOption(minCellAreaOption);

	QCommandLineOption maxCellAreaOption(QStringList() << "M" << "max",
		QCoreApplication::translate("main", "Maximum triangel area (default=0.01)"),
		QCoreApplication::translate("main", "max_area"),
		"0.01");
	parser.addOption(maxCellAreaOption);

	QCommandLineOption iterationOption(QStringList() << "i" << "iter",
		QCoreApplication::translate("main", "Number of iteration (default=10)"),
		QCoreApplication::translate("main", "iter"),
		"10");
	parser.addOption(iterationOption);

	// Process the actual command line arguments given by the user
	parser.process(app);

	const QStringList args = parser.positionalArguments();

	if (args.size() < 2)
	{
		std::cerr << "Source/output file not provided. Use \"-h\" to see usage." << std::endl;
	}

	// need to check existence of input file and output directory folder
	if (!QFileInfo::exists(args.at(0)))
	{
		std::cerr << "Input file not exists" << std::endl;
	}
	QDir d = QFileInfo(args.at(1)).absoluteDir();
	d.mkpath(d.absolutePath());

	RemeshCore remeshCore;
	remeshCore.SetInputStlPath(args.at(0));
	remeshCore.SetOutputStlPath(args.at(1));
	remeshCore.SetMinArea(parser.value(minCellAreaOption).toDouble());
	remeshCore.SetMaxArea(parser.value(maxCellAreaOption).toDouble());
	remeshCore.SetNumberOfIterations(parser.value(iterationOption).toDouble());
	remeshCore.Run();
}