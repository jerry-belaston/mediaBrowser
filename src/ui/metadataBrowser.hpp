#pragma once

#include <memory>
#include <map>
#include <Qwidget>
#include <qtpropertybrowser/qttreepropertybrowser.h>
#include <qtpropertybrowser/qtpropertymanager.h>
#include "core/viewInterface.hpp"


class QtVariantPropertyManager;
namespace mediaBrowser::ui
{

class MetadataBrowser 
	: public QtTreePropertyBrowser
	, public core::MetadataBrowserViewInterface
{
	Q_OBJECT

public:
	explicit MetadataBrowser(QWidget* parent = nullptr);

	// ViewInterface overrides
	void setController(core::Controller& controller) override;
	void setMetadata(QString const& key, QVariant const& value) override;
	void clearMetadata() override;

private:
	void createStructure();
	void destroyStructure();

private:
	// Controller
	std::unique_ptr<core::Controller> _dummyController;
	core::Controller* _controller{ nullptr };

	std::unique_ptr<QtVariantPropertyManager> _variantManager;
	std::unique_ptr<QtGroupPropertyManager> _groupPropertyManager;
	struct PropertyInfo
	{
		QtProperty* property{ nullptr };
		QtProperty* groupProperty{ nullptr };
	};
	using PropertyKey = QString;
	using PropertyInfoMap = std::map<PropertyKey, PropertyInfo>;
	PropertyInfoMap _propertyInfoMap;
};

} // namespace mediaBrowser::ui
