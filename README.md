# Engine
 
A C++ static library engine. The engine handles core systems (platform, rendering, game framework) for my various projects.
 
## Prerequisites
 
- VS 2022
- Written for C++23

## Generating the Solution
 
Run `GenerateProject.bat` from the root of the repo. This will generate the project files.
 
## Building
 
Open `Engine.sln` in Visual Studio, select a configuration (`Debug`, `Development`, or `Shipping`), and build.

All configurations have debug symbols enabled.

- `Debug` - No optimization (/MTd, /ZI, _DEBUG)
- `Development` - Partial optimization (/MT, /Zi, NDEBUG)
- `Shipping` - Full optimization (/GL, /MT, /Zi, NDEBUG)
 
## Cleaning
 
Run `Clean.bat` to remove all generated project and build output files.
