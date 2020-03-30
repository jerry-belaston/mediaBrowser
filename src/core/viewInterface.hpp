#pragma once

#include "controller.hpp"

namespace mediaBrowser::core
{

class ViewInterface
{
public:
	virtual void setController(Controller& /*controller*/) {}
};

class FileSystemBrowserViewInterface : public ViewInterface
{
public:
	virtual void setImageVideosFileFilters(QStringList const& filters) {}
};

class MetadataBrowserViewInterface : public ViewInterface
{
public:
	virtual void setMetadata(QString const& key, QVariant const& value) {}
	virtual void clearMetadata() {}
};

class PlayerViewInterface : public ViewInterface
{
public:
	virtual void setUrl(QUrl const& url) {}
	virtual void play(QUrl const& url) {}
};

class AnalysisViewInterface : public ViewInterface
{
public:
	virtual void update() {}
};

class LogViewInterface : public ViewInterface
{
public:
	enum class Level
	{
		Info,
		Warning,
		Error
	};
	virtual void addMessage(core::LogViewInterface::Level const level, QString const& message, QStringList const& details = {}) {}
};

} // namespace mediaBrowser::core
