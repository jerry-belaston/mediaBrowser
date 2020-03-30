#include "mainWindow.hpp"
#include <QBoxLayout>
#include <QSplitter>

namespace mediaBrowser::ui
{

MainWindow::MainWindow(QWidget* parent) 
	: QWidget{ parent }
{
	// Main window properties
	auto p = QPalette{};
	p.setColor(QPalette::Window, Qt::darkGray);
	setPalette(p);
	setContentsMargins(5, 5, 5, 5);

	auto* mainSplitter = new QSplitter{ Qt::Orientation::Horizontal, this };
	mainSplitter->setContentsMargins(0, 0, 0, 0);

	// Left widgets (wrapped into one in order to manage splitter)
	auto* leftWidget = new QWidget{ mainSplitter };
	mainSplitter->addWidget(leftWidget);

	auto* leftLayout = new QVBoxLayout{ leftWidget };
	leftLayout->setContentsMargins(0, 0, 0, 0);

	auto* leftSplitter = new QSplitter{ Qt::Orientation::Vertical, leftWidget };
	leftSplitter->setContentsMargins(0, 0, 0, 0);

	_fileSystemBrowser = new FileSystemBrowser(leftSplitter);
	leftSplitter->addWidget(_fileSystemBrowser);

	_metadataBrowser = new MetadataBrowser(leftSplitter);
	leftSplitter->addWidget(_metadataBrowser);

	leftLayout->addWidget(leftSplitter);

	// Central widgets
	_player = new Player(_mediaPlayer, this);
	mainSplitter->addWidget(_player);

	// Right widgets
	auto* rightWidget = new QWidget{ mainSplitter };
	mainSplitter->addWidget(rightWidget);

	auto* rightLayout = new QVBoxLayout{ rightWidget };
	rightLayout->setContentsMargins(0, 0, 0, 0);

	auto* rightSplitter = new QSplitter{ Qt::Orientation::Vertical, rightWidget };
	rightSplitter->setContentsMargins(0, 0, 0, 0);

	_analysis = new Analysis(_mediaPlayer, rightSplitter);
	rightSplitter->addWidget(_analysis);

	_log = new Log(rightSplitter);
	rightSplitter->addWidget(_log);

	rightSplitter->setStretchFactor(0, 2);
	rightSplitter->setStretchFactor(1, 1);

	rightLayout->addWidget(rightSplitter);

	// Layouting
	auto* mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->addWidget(mainSplitter);

	// Update widget stretech factor
	mainSplitter->setStretchFactor(0, 1);
	mainSplitter->setStretchFactor(1, 5);
	mainSplitter->setStretchFactor(2, 2);
}

FileSystemBrowser* MainWindow::getFileSystemBrowser() const
{
	return _fileSystemBrowser;
}

MetadataBrowser* MainWindow::getMetadataBrowser() const
{
	return _metadataBrowser;
}

Player* MainWindow::getPlayer() const
{
	return _player;
}

Analysis* MainWindow::getAnalysis() const
{
	return _analysis;
}

Log* MainWindow::getLog() const
{
	return _log;
}

} // namespace mediaBrowser::ui
