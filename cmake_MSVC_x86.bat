REM A simple batch script that will create solution files for MSVC 12.
REM All third party dll files will also be copied to all possible
REM MSVC run modes.

cmake -G "Visual Studio 14 2015" -DCMAKE_LIBRARY_ARCHITECTURE=MSVC_x86

for %%D in (Debug Release MinSizeRel RelWithDebInfo) do (
	if not exist %%D (
		mkdir %%D
	)
	for %%L in (lib\MSVC_x86\*.dll) do (
		copy %%L %%D
	)
)