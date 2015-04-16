rd /s /q temp

mkdir temp\VE\bin\windows
mkdir temp\VE\config
mkdir temp\VE\Resources
mkdir temp\VE\Myoushu\Wrappers\MyoushuJava\dist

mkdir "temp\VE\RoadtotheMoon\bin\windows"
mkdir "temp\VE\RoadtotheMoon\config"
mkdir "temp\VE\RoadtotheMoon\Resources"

mkdir "temp\VE\SocialSkills\bin\windows"
mkdir "temp\VE\SocialSkills\config"
mkdir "temp\VE\SocialSkills\Resources"

for %%s in (SampleCubes SampleCharacter SampleCollada SampleDotScene SampleLua SampleNetwork SampleGameLog MyoushuJava\SampleCubes) do (
	mkdir "temp\VE\Myoushu\Samples\%%s\bin\windows" ;
	mkdir "temp\VE\Myoushu\Samples\%%s\config" ;
	mkdir "temp\VE\Myoushu\Samples\%%s\Resources" ;
)

robocopy /E bin\windows\ temp\VE\bin\windows *.dll
del temp\VE\bin\windows\*_d.*
robocopy /E bin\windows\ temp\VE\bin\windows *.cfg
copy redist\cg*.dll temp\VE\bin\windows
copy redist\glut32.dll temp\VE\bin\windows
copy redist\OpenAL32.dll temp\VE\bin\windows
robocopy /E config\ temp\VE\config *.*
robocopy /E Resources\ temp\VE\Resources *.*
robocopy /E Myoushu\Wrappers\MyoushuJava\dist temp\VE\Myoushu\Wrappers\MyoushuJava\dist *.jar
copy bin\windows\mygui_layouteditor.exe temp\VE\bin\windows

robocopy /E "RoadtotheMoon\bin\windows" "temp\VE\RoadtotheMoon\bin\windows" "RoadToTheMoon.exe"
robocopy /E temp\VE\bin\windows temp\VE\RoadtotheMoon\bin\windows *.dll
robocopy /E "RoadtotheMoon\Resources\\" "temp\VE\RoadtotheMoon\Resources" *.*
robocopy /E "RoadtotheMoon\config\\" "temp\VE\RoadtotheMoon\config" *.*

robocopy /E "SocialSkills\bin\windows" "temp\VE\SocialSkills\bin\windows" "SocialSkills.exe"
robocopy /E temp\VE\bin\windows temp\VE\SocialSkills\bin\windows *.dll
robocopy /E "SocialSkills\Resources\\" "temp\VE\SocialSkills\Resources" *.*
robocopy /E "SocialSkills\config\\" "temp\VE\SocialSkills\config" *.*

for %%s in (SampleCubes SampleCharacter SampleCollada SampleDotScene SampleLua SampleNetwork SampleGameLog MyoushuJava\SampleCubes) do (
	robocopy /E "Myoushu\Samples\%%s\bin\windows\\" "temp\VE\Myoushu\Samples\%%s\bin\windows" "%%s.exe" ;
	robocopy /E temp\VE\bin\windows "temp\VE\Myoushu\Samples\%%s\bin\windows" *.dll ;
	robocopy /E "Myoushu\Samples\%%s\config\\" "temp\VE\Myoushu\Samples\%%s\config" *.* ;
	robocopy /E "Myoushu\Samples\%%s\Resources\\" "temp\VE\Myoushu\Samples\%%s\Resources" *.* ;
)

robocopy /E "Myoushu\Samples\MyoushuJava\SampleCubes\dist\\" "temp\VE\Myoushu\Samples\MyoushuJava\SampleCubes\bin\windows" *.*
	
cd temp
for /d /r . %%d in (.svn) do ( if exist "%%d" ( rd /s/q "%%d" ) )
rd /s /q VE\Resources\OgreSamples
cd ..
