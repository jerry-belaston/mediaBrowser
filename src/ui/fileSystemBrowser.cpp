#include "fileSystemBrowser.hpp"
#include <QStandardPaths>
#include <QFileSystemModel>
#include <QTreeView>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>

namespace mediaBrowser::ui
{

FileSystemBrowser::FileSystemBrowser(QWidget* parent)
	: _dummyController{ std::make_unique<core::Controller>() }
	, _controller{ _dummyController.get() }
{
	// Update treeview properties
	auto sizePolicy = QSizePolicy{ QSizePolicy::Preferred, QSizePolicy::Preferred };
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
	setSizePolicy(sizePolicy);

	// filter widget (a class should be done for that....)
	auto* filterWidget = new QWidget{ this };
	filterWidget->setStyleSheet("min-height: 14px;font: bold;");
	auto* filterLayout = new QHBoxLayout{ filterWidget };
	filterLayout->setContentsMargins(3, 0, 0, 0);
	// Label
	_filterLabel = new QLabel{};
	_filterLabel->setText("only images/videos: ");
	filterLayout->addWidget(_filterLabel);
	// CheckBox
	_filterCheckBox = new QCheckBox{};
	_filterCheckBox->setCheckable(true);
	filterLayout->addWidget(_filterCheckBox, Qt::AlignLeft);
	connect(_filterCheckBox, &QCheckBox::stateChanged, this, [this](int state)
	{
		if (state == Qt::CheckState::Checked)
		{
			_fileSystemModel->setNameFilters(_imageVideosFilters);
			_fileSystemModel->setNameFilterDisables(false);
		}
		else
		{
			_fileSystemModel->setNameFilters({});
		}
	});

	// Custom model
	_fileSystemModel = new QFileSystemModel(this);
	_fileSystemModel->setReadOnly(true);

	// Set model to treeview & custom treeview
	_treeView = new QTreeView(this);
	_treeView->setModel(_fileSystemModel);
	_treeView->setRootIndex(_fileSystemModel->setRootPath(QString()));
	auto const index{ _fileSystemModel->index(QDir::currentPath()) };
	_treeView->setCurrentIndex(index);
	_treeView->scrollTo(index, QTreeView::ScrollHint::PositionAtTop);

	/*if (auto const standardMoviesPaths = QStandardPaths::standardLocations(QStandardPaths::StandardLocation::MoviesLocation); !standardMoviesPaths.empty())
	{
		auto const index{ _fileSystemModel->index(standardMoviesPaths.at(0)) };
		_treeView->setCurrentIndex(index);
		_treeView->scrollTo(index, QTreeView::ScrollHint::PositionAtTop);
	}*/

	// Hide all columns except the first
	for (auto i = 1; i < _fileSystemModel->columnCount(); ++i)
	{
		_treeView->hideColumn(i);
	}

	// Connections
	connect(_treeView, &QTreeView::clicked, this, [this](const QModelIndex& modelIndex)
	{
		_controller->onUrlSelected(QUrl::fromLocalFile(_fileSystemModel->filePath(modelIndex)));
	});
	connect(_treeView, &QTreeView::doubleClicked, this, [this](const QModelIndex& modelIndex)
	{
		if (!_fileSystemModel->isDir(modelIndex))
		{
			_controller->onUrlDoubleClicked(QUrl::fromLocalFile(_fileSystemModel->filePath(modelIndex)));
		}
	});
	connect(_treeView, &QTreeView::expanded, this, [this](const QModelIndex& modelIndex)
	{
		_treeView->resizeColumnToContents(0);
	});
	connect(_treeView, &QTreeView::collapsed, this, [this](const QModelIndex& modelIndex)
	{
		_treeView->resizeColumnToContents(0);
	});

	auto layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(filterWidget);
	layout->addWidget(_treeView);
}

void FileSystemBrowser::setController(core::Controller& controller)
{
	_controller = &controller;
}

void FileSystemBrowser::setImageVideosFileFilters(QStringList const& filters)
{
	_imageVideosFilters = filters;
}

} // namespace mediaBrowser::ui
