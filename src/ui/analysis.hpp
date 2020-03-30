#pragma once

#include <Qwidget>
#include <QMediaPlayer>
#include "core/viewInterface.hpp"
#include "histogram.hpp"

class Histogram;
class QVideoProbe;
class QAudioProbe;
namespace mediaBrowser::ui
{

class Analysis 
	: public QWidget
	, public core::AnalysisViewInterface
{
	Q_OBJECT

public:
	explicit Analysis(QMediaPlayer& mediaPlayer, QWidget* parent = nullptr);

	// ViewInterface overrides
	void setController(core::Controller& controller) override;
	void update() override;

private:
	// Controller
	std::unique_ptr<core::Controller> _dummyController;
	core::Controller* _controller{ nullptr };
	QMediaPlayer& _mediaPlayer;
	Histogram* _videoHistogram{ nullptr };
	Histogram* _audioHistogram{ nullptr };
	QVideoProbe* _videoProbe{ nullptr };
	QAudioProbe* _audioProbe{ nullptr };
};

} // namespace mediaBrowser::ui