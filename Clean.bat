@echo off
REM Delete specific folders
rd /s /q .vs
rd /s /q bin
rd /s /q int

REM Delete sln and vcxproj* files in base folder
del /q *.sln
del /q *.vcxproj*

REM Remove empty folders recursively inside src
robocopy src\ src\ /S /MOVE