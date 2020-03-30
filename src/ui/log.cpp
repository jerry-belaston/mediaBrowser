#include "log.hpp"
#include <QBoxLayout>
#include <QDateTime>

namespace mediaBrowser::ui
{

Log::Log(QWidget* parent)
	: QWidget{ parent }
	, _dummyController{ std::make_unique<core::Controller>() }
	, _controller{ _dummyController.get() }
{
	// Logger
	_logTextEdit = new QTextEdit(this);
	auto palette = _logTextEdit->palette();
	palette.setColor(QPalette::Base, Qt::gray);
	_logTextEdit->setPalette(palette);

	// Layout
	auto* layout = new QVBoxLayout{ this };
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addWidget(_logTextEdit);

	// Initialize text editor
	addMessage(core::LogViewInterface::Level::Info, "Media Browser started!");
}

void Log::setController(core::Controller& controller)
{
	_controller = &controller;
}

void Log::addMessage(core::LogViewInterface::Level const level, QString const& message, QStringList const& details)
{
	QMetaObject::invokeMethod(this, [this, level, message, details]
	{
		// Format
		auto const stringTime = "[" + QDateTime::currentDateTime().toString("yyyy-MM-dd  HH:mm:ss") + "]";
		auto htmlStartFormat = QString{};
		auto htmlEndFormat = QString{};
		auto stringLevel = QString{};

		switch(level)
		{
		case core::LogViewInterface::Level::Info:
			stringLevel = "[Info]";
			break;
		case core::LogViewInterface::Level::Warning:
			htmlStartFormat = "<font color = \"darkSlateGray\">";
			htmlEndFormat = "</font>";
			stringLevel = "[Warn]";
			break;
		case core::LogViewInterface::Level::Error:
			htmlStartFormat = "<font color = \"maroon\">";
			htmlEndFormat = "</font>";
			stringLevel = "[Error]";
			break;
		default:
			assert(false && "LogViewInterface level not managed");
			break;
		}

		// Add message
		auto const formattedMessage = htmlStartFormat + stringTime + stringLevel + " " + message + htmlEndFormat;
		_logTextEdit->append(formattedMessage);

		// Add detatils
		if (!details.isEmpty())
		{
			for (auto const& detail : details)
			{
				_logTextEdit->append("                        " + htmlStartFormat +  detail + htmlEndFormat); // hummmm uggly space... but that makes the job ;-)
			}
		}
	}, Qt::QueuedConnection);
}

} // namespace mediaBrowser::ui
