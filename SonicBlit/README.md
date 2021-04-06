SonicBlit Player
================

This is the 'player' component of SonicBlit; this (along with the audio assets
built with the tool) is the only thing that needs to go into your end project.

Usage
-----

* Copy this entire directory into your project.

* Add the following lines to your `CMakeLists.txt` file, *after* you define your
  project sources:

  ```
  include_directories(SonicBlit)
  set(PROJECT_SOURCE ${PROJECT_SOURCE} SonicBlit/SonicBlit.cpp)
  ```
* Create a new instance of `SonicBlit` (and optionally load data via `SonicBlit::load`)
 
* Call `SonicBlit::update` from your main `update` method.

* CMake and build as usual!
