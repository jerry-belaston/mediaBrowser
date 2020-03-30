# SDD Overview

Here a light Software Design Document giving the main key points regarding the Media Browser code architecture

## External Dependencies

C++ based application only depending on Qt Framework (in addition of native standard library)

## Package/Component architecture

MVC based (Model-View-Controller) application organized as following:

* **core** namespace : in charge of model and controller
	* **Controller** class in charge of the model and view management
	* **ViewInterface** abstract interface for ui views (allowing to split ui/core dependencies)
* **ui** namespace : in charge of the view
	* Qt widgets implementing ViewInterface views

## Axis of improvement
* Use several QMediaPlayer (in order to smooth the playing)
* Uses another library for retrieving metadata (A lot of issues with QMediaObject::metadataChanged)
* Create a real model to manage the player in the core
* Uses PImpl in core::Controller to increase compilation speed
* Template ViewInterface in order to allow an easy insertion of new views (uggly code in controller.hpp ;-) 
* etc.

## License

Copyright (C) 2020, Jerry Belaston