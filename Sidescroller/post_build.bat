:: Copy over all the necessary SDL2_mixer files to the output directory
Set SourceDir=%1
Set TargetDir=%2
xcopy /d /y %SourceDir%SDL2_mixer.lib %TargetDir%
xcopy /d /y %SourceDir%..\packages\sdl2_mixer.2.0.0\lib\SDL2_mixer.dll %TargetDir%