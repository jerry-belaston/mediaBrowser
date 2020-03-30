#pragma once

#include <memory>
#include <QVariant>
#include <QUrl>

namespace mediaBrowser::core
{

class FileSystemBrowserViewInterface;
class MetadataBrowserViewInterface;
class PlayerViewInterface;
class AnalysisViewInterface;
class LogViewInterface;
class Controller
{
public:

	Controller();

	// View initialization
	void setView(FileSystemBrowserViewInterface& fileSystemBrowserViewInterface);
	void setView(MetadataBrowserViewInterface& metadataBrowserView);
	void setView(PlayerViewInterface& playerView);
	void setView(AnalysisViewInterface& analysisView);
	void setView(LogViewInterface& logView);

	// Browser callback
	void onUrlSelected(QUrl const& url);
	void onUrlDoubleClicked(QUrl const& url);

	// Player callback
	void onPlayButtonClicked(bool const isEnabled);
	void onMediaStopped();
	void onMediaPlaying();
	void onMediPaused();
	void onMetadataAvailable(bool const isMetadataAvailable, QString const& key, QVariant const& value);
	void onMediaError(QString const& errorMessage);

private:
	std::unique_ptr<FileSystemBrowserViewInterface> _dummyFileSystemBrowserView;
	FileSystemBrowserViewInterface* _fileSystemBrowserView{ nullptr };
	std::unique_ptr<MetadataBrowserViewInterface> _dummyMetadataBrowserView;
	MetadataBrowserViewInterface* _metadataBrowserView{ nullptr };
	std::unique_ptr<PlayerViewInterface> _dummyPlayerView;
	PlayerViewInterface* _playerView{ nullptr };
	std::unique_ptr<AnalysisViewInterface> _dummyAnalysisView;
	AnalysisViewInterface* _analysisView{ nullptr };
	std::unique_ptr<LogViewInterface> _dummyLogView;
	LogViewInterface* _logView{ nullptr };

	// Model info
	QUrl _url;
	bool _mediaPlaying{ false };
	bool _metadataAvailableProcessed{ false };
};

} // mediaBrowser::core
