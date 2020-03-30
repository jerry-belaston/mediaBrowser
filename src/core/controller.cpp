#include "controller.hpp"
#include "viewInterface.hpp"

namespace mediaBrowser::core
{

Controller::Controller()
	: _dummyFileSystemBrowserView{ std::make_unique<FileSystemBrowserViewInterface>() }
	, _fileSystemBrowserView{ _dummyFileSystemBrowserView.get() }
	, _dummyMetadataBrowserView{ std::make_unique<MetadataBrowserViewInterface>() }
	, _metadataBrowserView{ _dummyMetadataBrowserView.get() }
	, _dummyPlayerView{ std::make_unique<PlayerViewInterface>() }
	, _playerView{ _dummyPlayerView.get() }
	, _dummyAnalysisView{ std::make_unique<AnalysisViewInterface>() }
	, _analysisView{ _dummyAnalysisView.get() }
	, _dummyLogView{ std::make_unique<LogViewInterface>() }
	, _logView{ _dummyLogView.get() }
{
}

void Controller::setView(FileSystemBrowserViewInterface& fileSystemBrowserView)
{
	// Backup view and set current controller
	_fileSystemBrowserView = &fileSystemBrowserView;
	_fileSystemBrowserView->setController(*this);

	// Initialize file filters
	auto const videoFilters = QString{ "*.3gp;*.aac;*.avi;*.flv;*.mkv;*.mov;*.mp4;*wmv" };
	auto const imageFilters = QString{ "*.bmp;*.dlib;*.gif;*.jpg;*.jpeg;*.jpe;*.jfif;*.png;*.tiff" };
	_fileSystemBrowserView->setImageVideosFileFilters(videoFilters.split(";") + imageFilters.split(";"));
}

void Controller::setView(MetadataBrowserViewInterface& metadataBrowserView)
{
	_metadataBrowserView = &metadataBrowserView;
	_metadataBrowserView->setController(*this);
}

void Controller::setView(PlayerViewInterface& playerView)
{
	_playerView = &playerView;
	_playerView->setController(*this);
}


void Controller::setView(AnalysisViewInterface& analysisView)
{
	_analysisView = &analysisView;
	_analysisView->setController(*this);
}

void Controller::setView(LogViewInterface& logView)
{
	_logView = &logView;
	_logView->setController(*this);
}

void Controller::onUrlSelected(QUrl const& url)
{
	_metadataBrowserView->clearMetadata();
}

void Controller::onUrlDoubleClicked(QUrl const& url)
{
	_url = url;
	_playerView->play(url);
}

void Controller::onPlayButtonClicked(bool const isEnabled)
{
}

void Controller::onMediaStopped()
{
	_mediaPlaying = false;
	_metadataAvailableProcessed = false;
	_logView->addMessage(LogViewInterface::Level::Info, "Stopped (" + _url.toLocalFile() + ")");
}

void Controller::onMediaPlaying()
{
	_mediaPlaying = true;
	_logView->addMessage(LogViewInterface::Level::Info, "Playing... (" + _url.toLocalFile() + ")");
}

void Controller::onMediPaused()
{
	_logView->addMessage(LogViewInterface::Level::Info, "Paused... (" + _url.toLocalFile() + ")");
}

void Controller::onMetadataAvailable(bool const isMetadataAvailable, QString const& key, QVariant const& value)
{
	if (!_mediaPlaying)
	{
		return;
	}

	if ((!_metadataAvailableProcessed) || !isMetadataAvailable)
	{
		auto const logLevel = isMetadataAvailable ? LogViewInterface::Level::Info : LogViewInterface::Level::Warning;
		auto const logPrefixMessage = isMetadataAvailable ? QString("Metadata loaded") : QString("Metadata not available");
		_logView->addMessage(logLevel, logPrefixMessage + " (" + _url.toLocalFile() + ")");
		_metadataAvailableProcessed = true;
	}
	_metadataBrowserView->setMetadata(key, value);
}

void Controller::onMediaError(QString const& errorMessage)
{
	_logView->addMessage(LogViewInterface::Level::Error, errorMessage + " (" + _url.toLocalFile() + ")");
}

} // namespace mediaBrowser::core
