:: Run this script to load the current path into %DSCENGINE% environment variable
:: This is required in order to compile DSC projects

@echo off
SET engine_path=%~dp0
SET engine_path=%engine_path:~0,-1%
echo Setting DSCENGINE path environment variable: %engine_path%

setx /s %ComputerName% /u %USERNAME% DSCENGINE %engine_path%
