SET COMP_PATH=C:\workspace\LEDStateManager4port\build\src\Debug\

SET TARGET_EXE0="%COMP_PATH%LEDStateManager4portComp.exe

START "LEDStateManager4port_test" "%TARGET_EXE0%"

SET COMP_PATH=C:\workspace\ThresholdSwitch_ver2\build\src\Debug\
SET TARGET_EXE0="%COMP_PATH%ThresholdSwitch_ver2Comp.exe -f %COMP_PATH%rtc_0.conf"
SET TARGET_EXE1="%COMP_PATH%ThresholdSwitch_ver2Comp.exe -f %COMP_PATH%rtc_1.conf"
SET TARGET_EXE2="%COMP_PATH%ThresholdSwitch_ver2Comp.exe -f %COMP_PATH%rtc_2.conf"
SET TARGET_EXE3="%COMP_PATH%ThresholdSwitch_ver2Comp.exe -f %COMP_PATH%rtc_3.conf"

START "ThresholdSwitch_ver2_0" "%TARGET_EXE0%"
START "ThresholdSwitch_ver2_1" "%TARGET_EXE1%"
START "ThresholdSwitch_ver2_2" "%TARGET_EXE2%
START "ThresholdSwitch_ver2_3" "%TARGET_EXE3%


