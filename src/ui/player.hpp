#pragma once

#include <QWidget>
#include "core/viewInterface.hpp"

class QMediaPlayer;
class QPushButton;
class QSlider;

namespace mediaBrowser::ui
{

class Player 
	: public QWidget
	, public core::PlayerViewInterface
{
	Q_OBJECT

public:
	explicit Player(QMediaPlayer& mediaPlayer, QWidget* parent = nullptr);

	// ViewInterface overrides
	void setController(core::Controller& controller) override;
	void play(QUrl const& url) override;

private:
	// Controller
	std::unique_ptr<core::Controller> _dummyController;
	core::Controller* _controller{ nullptr };

	// Widgets
	QMediaPlayer& _mediaPlayer;
	QPushButton* _playButton{ nullptr };
	QSlider* _volumeSlider{ nullptr };

};

} // namespace mediaBrowser::ui
