#pragma once

#include <QWidget>
#include "core/viewInterface.hpp"

class QCheckBox;
class QLabel;
class QTreeView;
class QFileSystemModel;
namespace mediaBrowser::ui
{

class FileSystemBrowser
	: public QWidget
	, public core::FileSystemBrowserViewInterface
{
	Q_OBJECT

public:
	explicit FileSystemBrowser(QWidget* parent = nullptr);

	// ViewInterface overrides
	void setController(core::Controller& controller) override;
	void setImageVideosFileFilters(QStringList const& filters) override;

private:
	// Controller
	std::unique_ptr<core::Controller> _dummyController;
	core::Controller* _controller{ nullptr };

	// Widgets
	QLabel* _filterLabel{ nullptr };
	QCheckBox* _filterCheckBox{ nullptr };
	QTreeView* _treeView{ nullptr };
	QFileSystemModel* _fileSystemModel{ nullptr };
	QStringList _imageVideosFilters;
};

} // namespace mediaBrowser::ui
