# asd-ve-platform
[*A 3D Virtual Environment Development Platform for ASD Therapy Tools*](http://scholar.sun.ac.za/handle/10019.1/2634) is the title of my MSc (computer science) thesis (2008-2009, [Stellenbosch University](http://www.sun.ac.za)). This repository contains the source code for the project.

The abstract of the thesis:

> The aim of this thesis is to develop a generic 3D virtual environment development platform
> for autism spectrum disorder (ASD) therapy tools. The potential of using computerised
> therapy tools for ASD therapy is well known. However, the development of such tools is
> expensive and time-consuming, and is language and culture specific. This work intends
> to alleviate these problems.
> 
> The design of the platform is based on known game engine designs, but adapted for the
> requirements of ASD therapy tools. It supports standard features such as 3D rendering,
> animation and audio output. Specific features, aimed at ASD therapy tools and educational
> games, included in our engine are: replays, data capturing, remote monitoring over
> a network and language localisation. We also implemented an input hardware abstraction
> layer to allow support for non-standard input peripherals in the future, without modifying
> existing game implementations. Furthermore, to separate the development of games and
> tools from the engine, we include wrapper libraries in our engine for Lua and Java.

This project essentially implemented a 3D virtual environment engine (or a video game engine) with certain added tools aimed at ASD therapy.

This project has only been built and tested as 32-bit with 32-bit redistributables. 

The engine was built using the following notable 3rd party libraries:
  * OGRE (http://ogre3d.org)
  * MyGUI (http://mygui.info)
  * Boost (http://boost.org)
  * NxOgre (http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Nxogre)
  * Lua (http://lua.org)
  * POCO (http://pocoproject.org)
  * Ogg / Vorbis
  * SQLite (http://www.sqlite.org)
  * DirectX SDK (March 2009 http://www.microsoft.com/en-us/download/confirmation.aspx?id=3035)
  * PhysX SDK 2.8.0 (http://www.nvidia.com/object/physx_archives.html)
  * Nvidia CG 2.2 (http://http.developer.nvidia.com/Cg/cg_2_2_0010.html)
  * JDK8 (32-bit) (http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html)
  * OpenAL SDK 1.1 (http://www.openal.org/creative-installers/)
  
Source code of the third-party libraries are available as an archive on the releases page of the project. You'll need this to build the project from source.
  
Required redistributables:
  * DirectX March 2009 or newer (http://www.microsoft.com/en-us/download/details.aspx?id=19743)
  * Microsoft Visual C++ Redistributable (http://www.microsoft.com/en-za/download/details.aspx?id=40784)
  * PhysX System Software 8.04.25+ (or an NVidia driver that includes it) (http://www.nvidia.com/object/physx_archives.html)
  * Nvidia CG 2.2 (http://http.developer.nvidia.com/Cg/cg_2_2_0010.html)
  * OpenAL 1.1 (http://www.openal.org/creative-installers/)
  
The project includes some samples:
  * SampleCubes: basic cubes-based physics demo
  * SampleCharacter: basic character controller demo
  * SampleDotScene: basic .scene demo (scenes exported from Blender)
  * SampleGameLog: demo using the SQL-based activity logging features of the engine
  * SampleLua: demo using Lua as the game-logic scripting language
  * SampleNetwork: example showing the basic networking features of the engine
  * RoadtotheMoon: a basic educational narrative game implemented with the engine
  * SocialSkills: an example of a basic ASD therapy tool implemented with the engine

## Installing
Download the *resources* and *binaries* archives from the releases page and extract them into a directory. Executables for the samples are in the *binaries* archive.

## Building from source
Currently this project is only tested on Windows. It was originally developed in Windows Vista with Visual Studio 2008 and recently compiled in Windows 8.1 with Visual Studio 2013.

The build system uses premake 3.7 (http://premake.sourceforge.net/). 

To build the project:
  1. clone the repo
  2. download and extract the 3rdparty archive to the source directory
  3. download and extract the resources archive to the source directory
  4. install the required redistributables mentioned above
  5. run premake (something like premake --target vs2008)
  6. open the solution file in Visual Studio (upgrade the solution file if required)
  7. build the entire solution

Binaries will be in the bin/windows directory of the source tree. For each of the samples you'll have to copy the base engine binaries (bin/windows in the root of the source tree) to the bin/windows directory of the sample.

## License
This project is released under a modified version of the LGPL version 3 (non-commercial use only). Please see the [LICENSE](LICENSE) file for more details.
