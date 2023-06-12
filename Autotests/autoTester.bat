@echo off
setlocal enabledelayedexpansion

set appPath=..\CourseworkOnKINPO\ClassificationOfRecordsByRule\release\ClassificationOfRecordsByRule.exe

for /L %%i in (1, 1, 43) do (
    set "inputPathRecord=.\inputRecordsTest\recodTest%%i.txt"
    set "inputPathRule=.\inputRulesTest\ruleTest%%i.txt"
	set "outputPath=.\outputTest\resultTest%%i.txt"

    echo Running test case %%i

    "%appPath%" "!inputPathRecord!" "!inputPathRule!" "!outputPath!"    

	echo.
    echo Test case %%i completed.
    echo.
)

echo All test cases completed.
pause