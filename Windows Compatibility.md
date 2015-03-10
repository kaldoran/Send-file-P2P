# How to compile the program on Windows

## Requiered 
- First you will need to install [openSSL] (http://slproweb.com/download/Win32OpenSSL-1_0_1L.exe)
- You also need [Code::Blocks From SourceForge] ( http://sourceforge.net/projects/codeblocks/files/Binaries/13.12/Windows/codeblocks-13.12mingw-setup.exe )
- [Our projet] (https://github.com/UJM-INFO/p2p-a/archive/master.zip)

Please install openSSL in the default directory. 

## Code::Blocks version (Easy)
** Note :** if your hard drive don't have C: as name, please refered to the end of this tutorial.

### Prepare for Code::Blocks
After that, unzip our project, then copy all the SRC/* and INC/* into the directory that contains the *.cbp.
To do that you could use the "moveFile.bat" script

** Note :** You could also revert this action with "revertMoveFile.bat" script.

### Start with Code::Blocks
You can now open the *.cbp file.
You need then to click on the gears in the code::blocks toolbar.

** Note :** Be carefull, by default, you are in DEBUG version, so change into if you don't want to see all our debug message.

Wait a bit, then if it's good you are going to see a "bin" directory in your unzipped project.
Open it and go in "Release" you should see a ".exe" file.

** Note :** If You do not have change the version (Debug to Released then the directory going to be "Debug".

Congrate you can now start your program by double click on it :D
Have fun.


### My hard drive don't have the C: name.
You are in the good part, if this is the case, then you need to reconfigure the *.cpb file.
Let's see how.

## CMake version

If You want to use CMake you could, on linux just use our MakeFile. 
On windows you need to install CMake and run it.
Then you should need to compile.

Congrate you can now start your program by double click on it :D
Have fun.
