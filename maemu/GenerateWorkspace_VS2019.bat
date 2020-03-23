..\BuildTools\JamPlus\Bin\Win64\Jam.exe --workspace --gen=vs2019 -compiler=vs2019 --config=jamplus.config maemu.jam _Build

CALL _Build\_workspaces_\vs2019\maemu.sln
