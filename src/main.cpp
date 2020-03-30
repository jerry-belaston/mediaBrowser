#include <QApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>
#include "core/controller.hpp"
#include "ui/mainWindow.hpp"

int main(int argc, char *argv[])
{
	// Create Qt application
	QApplication application(argc, argv);

	// Create view
	auto mainWindow = mediaBrowser::ui::MainWindow{};
	mainWindow.setWindowTitle("Media Browser");
	auto const availableGeometry = QApplication::desktop()->availableGeometry(&mainWindow);
	mainWindow.resize(availableGeometry.width() / 1.5f, availableGeometry.height() / 1.5f);
	mainWindow.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, mainWindow.size(), QApplication::desktop()->availableGeometry()));
	mainWindow.setMinimumSize(900, 300);


	// Create controller with created view
	auto controller = mediaBrowser::core::Controller{};
	controller.setView(*mainWindow.getFileSystemBrowser());
	controller.setView(*mainWindow.getMetadataBrowser());
	controller.setView(*mainWindow.getPlayer());
	controller.setView(*mainWindow.getAnalysis());
	controller.setView(*mainWindow.getLog());

	// Display view
	mainWindow.show();

	// Enter the QApplication main event loop and wait until exit is called
	return application.exec();
}