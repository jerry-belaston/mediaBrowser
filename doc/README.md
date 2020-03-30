# SDD Overview

Here a light **S**oftware **D**esign **D**ocument giving the main lines of the Media Browser architecture.

## External Dependencies

C++ based application only depending on Qt Framework (in addition of native standard library).

## Package/Component architecture

MVC based (Model-View-Controller) application organized as following:

- `core` namespace:
	- `Controller`: class managing the model and the view
	- `ViewInterface`: abstract interface of ui views (allowing to split ui/core dependencies)
- `ui` namespace:
	- Qt widgets concrete views implementing `ViewInterface`

## Areas of improvement

- Use several `QMediaPlayer` (in order to smooth the playing)
- Use another library for retrieving metadata (a lot of issues with `MediaObject::metadataChanged`)
- Create a real model to manage the player in the core
- Uses PImpl in core::Controller to increase compilation speed
- Make `ViewInterface` template in order to allow an easy insertion of new views (uggly code in `controller.hpp` :slightly_smiling_face:)
- Etc.

## License

Copyright (C) 2020, Jerry Belaston