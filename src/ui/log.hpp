#pragma once

#include <Qwidget>
#include <QLabel>
#include <QTextEdit>
#include "core/viewInterface.hpp"

namespace mediaBrowser::ui
{

class Log 
	: public QWidget
	, public core::LogViewInterface
{
	Q_OBJECT

public:
	explicit Log(QWidget* parent = nullptr);

	// ViewInterface overrides
	void setController(core::Controller& controller) override;
	void addMessage(core::LogViewInterface::Level const level, QString const& message, QStringList const& details = {}) override;

private:
	// Controller
	std::unique_ptr<core::Controller> _dummyController;
	core::Controller* _controller{ nullptr };
	QTextEdit* _logTextEdit{ nullptr };
};

} // namespace mediaBrowser::ui