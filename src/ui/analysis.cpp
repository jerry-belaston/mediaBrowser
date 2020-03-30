#include "analysis.hpp"
#include <QBoxLayout>
#include <QVideoProbe>
#include <QAudioProbe>

namespace mediaBrowser::ui
{

Analysis::Analysis(QMediaPlayer& mediaPlayer, QWidget* parent)
	: QWidget{ parent }
	, _dummyController{ std::make_unique<core::Controller>() }
	, _controller{ _dummyController.get() }
	, _mediaPlayer{ mediaPlayer }
{
	setMinimumHeight(300);
	_videoHistogram = new Histogram(this);
	_audioHistogram = new Histogram(this);
	auto* layout = new QVBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(_videoHistogram,5);
	layout->addWidget(_audioHistogram,1);

	_videoProbe = new QVideoProbe(this);
	connect(_videoProbe, &QVideoProbe::videoFrameProbed, _videoHistogram, &Histogram::processFrame);
	_videoProbe->setSource(&_mediaPlayer);

	_audioProbe = new QAudioProbe(this);
	connect(_audioProbe, &QAudioProbe::audioBufferProbed, _audioHistogram, &Histogram::processBuffer);
	_audioProbe->setSource(&_mediaPlayer);
}

void Analysis::setController(core::Controller& controller)
{
	_controller = &controller;
}

void Analysis::update()
{
}

} // namespace mediaBrowser::ui
