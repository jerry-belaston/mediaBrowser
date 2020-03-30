#include "metadataBrowser.hpp"

#include <qtpropertybrowser/qteditorfactory.h>
#include <qtpropertybrowser/qtvariantproperty.h>
#include <QMediaMetadata>

namespace mediaBrowser::ui
{

MetadataBrowser::MetadataBrowser(QWidget* parent)
	: QtTreePropertyBrowser{ parent }
	, _dummyController{ std::make_unique<core::Controller>() }
	, _controller{ _dummyController.get() }
{
	createStructure();
}

void MetadataBrowser::setController(core::Controller& controller)
{
	_controller = &controller;
}

void MetadataBrowser::setMetadata(QString const& key, QVariant const& value)
{
	QMetaObject::invokeMethod(this, [this, key, value]
	{
		if (_propertyInfoMap.count(key) == 1)
		{
			auto const& [property, groupProperty] = _propertyInfoMap.at(key);
			if (!groupProperty->subProperties().contains(property))
			{
				groupProperty->addSubProperty(property);
			}
			_variantManager->setValue(property, value);
		}
	}, Qt::QueuedConnection);
}

void MetadataBrowser::clearMetadata()
{
	QMetaObject::invokeMethod(this, [this]
	{
		destroyStructure();
		createStructure();
	}, Qt::QueuedConnection);
}

void MetadataBrowser::createStructure()
{
	_variantManager = std::make_unique<QtVariantPropertyManager>();
	setFactoryForManager(_variantManager.get(), new QtVariantEditorFactory{});

	auto addProp = [this](auto* groupProperty, auto const propertyType, auto const& propertyName)
	{
		auto* property = _variantManager->addProperty(propertyType, propertyName);
		_propertyInfoMap[propertyName] = { property, groupProperty };
	};

	_groupPropertyManager = std::make_unique<QtGroupPropertyManager>();
	auto* groupPoperty = _groupPropertyManager->addProperty("General");
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Title);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::SubTitle);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Author);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Comment);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Description);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Category);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Genre);
	addProp(groupPoperty, QVariant::Date, QMediaMetaData::Date);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::UserRating);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Keywords);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Language);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Publisher);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Copyright);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::ParentalRating);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::RatingOrganization);
	addProperty(groupPoperty);
	
	groupPoperty = _groupPropertyManager->addProperty("Media");
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::Size);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::MediaType);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::Duration);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Audio");
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::AudioBitRate);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::AudioCodec);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::AverageLevel);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::ChannelCount);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::PeakValue);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::SampleRate);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Music");
	addProp(groupPoperty, QVariant::String, QMediaMetaData::AlbumTitle);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::AlbumArtist);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::ContributingArtist);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Composer);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Conductor);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Mood);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::TrackNumber);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::TrackCount);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::CoverArtUrlSmall);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::CoverArtUrlLarge);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Image and Video");
	addProp(groupPoperty, QVariant::Size, QMediaMetaData::Resolution);
	addProp(groupPoperty, QVariant::Size, QMediaMetaData::PixelAspectRatio);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::Orientation);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Video");
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::VideoFrameRate);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::VideoBitRate);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::VideoCodec);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::PosterUrl);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Movie");
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::ChapterNumber);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Director);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::LeadPerformer);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Writer);
	addProperty(groupPoperty);

	groupPoperty = _groupPropertyManager->addProperty("Photo");
	addProp(groupPoperty, QVariant::String, QMediaMetaData::CameraManufacturer);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::CameraModel);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Event);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::Subject);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::ExposureTime);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::FNumber);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::ExposureProgram);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::ISOSpeedRatings);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::ExposureBiasValue);
	addProp(groupPoperty, QVariant::DateTime, QMediaMetaData::DateTimeOriginal);
	addProp(groupPoperty, QVariant::DateTime, QMediaMetaData::DateTimeDigitized);
	addProp(groupPoperty, QVariant::DateTime, QMediaMetaData::SubjectDistance);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::MeteringMode);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::LightSource);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::Flash);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::FocalLength);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::ExposureMode);
	addProp(groupPoperty, QVariant::Int, QMediaMetaData::WhiteBalance);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::DigitalZoomRatio);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::FocalLengthIn35mmFilm);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::SceneCaptureType);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GainControl);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::Contrast);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::Saturation);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::Sharpness);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::DeviceSettingDescription);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSLatitude);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSLongitude);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSAltitude);
	addProp(groupPoperty, QVariant::DateTime, QMediaMetaData::GPSTimeStamp);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSSatellites);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSStatus);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSDOP);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSSpeed);
	addProp(groupPoperty, QVariant::Double, QMediaMetaData::GPSTrack);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSTrackRef);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSImgDirection);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSImgDirectionRef);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSMapDatum);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSProcessingMethod);
	addProp(groupPoperty, QVariant::String, QMediaMetaData::GPSAreaInformation);
	addProperty(groupPoperty);
}

void MetadataBrowser::destroyStructure()
{
	_variantManager.reset();
	_groupPropertyManager.reset();
}

} // namespace mediaBrowser::ui
