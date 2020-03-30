#pragma once

#include <memory>
#include <Qwidget>
#include "fileSystemBrowser.hpp"
#include "metadataBrowser.hpp"
#include "player.hpp"
#include "analysis.hpp"
#include "log.hpp"

namespace mediaBrowser::ui
{

class MainWindow 
	: public QWidget
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);

	FileSystemBrowser* getFileSystemBrowser() const;
	MetadataBrowser* getMetadataBrowser() const;
	Player* getPlayer() const;
	Analysis* getAnalysis() const;
	Log* getLog() const;

private:
	// Widgets
	FileSystemBrowser* _fileSystemBrowser{ nullptr };
	Player* _player{ nullptr };
	MetadataBrowser* _metadataBrowser{ nullptr };
	Analysis* _analysis{ nullptr };
	Log* _log{ nullptr };

	QMediaPlayer _mediaPlayer{ this, QMediaPlayer::VideoSurface }; // Quick ack really not clean (should not be done here)
};

} // namespace mediaBrowser::ui
