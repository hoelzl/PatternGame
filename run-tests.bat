@ECHO ON

Set UE4EnginePath=C:\Program Files\Epic Games\4.10\Engine
Set ProjectPath=S:\Unreal\Projects\Tutorials\PG

start "Testing" "C:\Program Files\Epic Games\4.10\Engine\Build\BatchFiles\RunUAT.bat" BuildCookRun -project=%ProjectPath%\PG.uproject -run -RunAutomationTests -unattended -nullrhi -NoP4
