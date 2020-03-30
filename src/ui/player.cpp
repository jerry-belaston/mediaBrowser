#include "player.hpp"

#include <QMediaPlayer>
#include <QtWidgets>
#include <QVideoWidget>

namespace mediaBrowser::ui
{

Player::Player(QMediaPlayer& mediaPlayer, QWidget* parent)
	: QWidget{ parent }
	, _dummyController{ std::make_unique<core::Controller>() }
	, _controller{ _dummyController.get() }
	, _mediaPlayer{ mediaPlayer }
{
	QPalette p = palette();
	p.setColor(QPalette::Window, Qt::black);
	setPalette(p);

	auto* mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0, 0, 0, 0);

	// Video widget
	auto* videoWidget = new QVideoWidget;
	mainLayout->addWidget(videoWidget);

	auto* controlLayout = new QHBoxLayout;

	// Play button
	_playButton = new QPushButton(this);
	_playButton->setEnabled(false);
	_playButton->setSizePolicy({ QSizePolicy::Maximum, QSizePolicy::Fixed });
	_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	_playButton->setStyleSheet("height: 30px; width: 30px;");
	controlLayout->addWidget(_playButton);
	connect(_playButton, &QPushButton::clicked, this, [this](bool /*checked*/)
	{
		switch (_mediaPlayer.state()) 
		{
		case QMediaPlayer::PlayingState:
			_mediaPlayer.pause();
			break;
		default:
			_mediaPlayer.play();
			break;
		}
	});

	// Volume Slider
	_volumeSlider = new QSlider(Qt::Horizontal, this);
	_volumeSlider->setSizePolicy({ QSizePolicy::Preferred, QSizePolicy::Fixed });
	_volumeSlider->setRange(0, 100);
	_volumeSlider->setEnabled(false);
	controlLayout->addWidget(_volumeSlider);
	connect(_volumeSlider, &QSlider::valueChanged, this, [this](int value)
	{
		_mediaPlayer.setPosition(value);
	});

	// Layout
	mainLayout->addLayout(controlLayout);
	setLayout(mainLayout);

	// Init media player
	_mediaPlayer.setVideoOutput(videoWidget);
	connect(&_mediaPlayer, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state)
	{
		switch (state) 
		{
		case QMediaPlayer::StoppedState:
			_controller->onMediaStopped();
			break;
		case QMediaPlayer::PlayingState:
			_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
			_controller->onMediaPlaying();
			break;
		case QMediaPlayer::PausedState:
			_controller->onMediPaused();
		default:
			_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
			break;
		}
	});

	connect(&_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status)
	{
		switch (status)
		{
		case QMediaPlayer::LoadedMedia:

			break;
		default:
			break;
		}
	});

	connect(&_mediaPlayer, &QMediaPlayer::positionChanged, this, [this](qint64 position)
	{
		_volumeSlider->setValue(position);
	});
	connect(&_mediaPlayer, &QMediaPlayer::durationChanged, this, [this](qint64 duration)
	{
		_volumeSlider->setRange(0, duration);
	});
	connect(&_mediaPlayer, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, [this]()
	{
		_playButton->setEnabled(false);
		_volumeSlider->setEnabled(false);
		QString errorMessage = "Error #" + QString::number(int(_mediaPlayer.error())) + " - " + _mediaPlayer.errorString();
		_controller->onMediaError(errorMessage);
	});
	connect(&_mediaPlayer, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, [this]()
	{	
		if (!_mediaPlayer.isMetaDataAvailable())
		{
			_controller->onMetadataAvailable(false, "", {});
			return;
		}

		for (auto key : _mediaPlayer.availableMetaData())
		{
			_controller->onMetadataAvailable(true, key, _mediaPlayer.metaData(key));
		}
	});
}

void Player::setController(core::Controller& controller)
{
	_controller = &controller;
}

void Player::play(QUrl const& url)
{
	QMetaObject::invokeMethod(this, [this, url]
	{
		_playButton->setEnabled(true);
		_volumeSlider->setEnabled(true);
		_mediaPlayer.setMedia(url);
		_mediaPlayer.play();
	}, Qt::QueuedConnection);
}

} // namespace mediaBrowser::ui
