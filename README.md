# NetWork (Fr : Réseau ) Project - P2P Team a.

#### How start with it ?

##### Before anything.
  Before starting anything, you could compile our source code.
  If you are on windows please be sure to Read the "Windows compatibility" File.
  Else you could use our makefile, or use CMake.
  
  Please be sure to compile the part which you want to start before tryingto starting it.
  
#### How to use it / test it ?

##### Generator 
  First ( after compile that ) a new "Bin" directory appear.
  You could now start the Generator by writing "./Bin/Generator". 
  
  Then you just need to answer to Question. 
  
  Exemple of use : 
  ```
  > ./Bin/Generator
  [INFO] Welcome to this awesome Generator

  [Q] On which file do you want to create the '.ndex' file ?
  moveFile.bat
  
  [Q] What is the IP adress of the boss ?
  127.0.0.1

  [Q] What is the port to connect to ?
  (From 1024 to 65536)
  42000
  
  [Q] What size do you want the volumes to be ?
  (Size in ko from 8 to 64, both included)
  16
  
  [INFO] Boss : 127.0.0.1
  [INFO] Port : 42100
  [INFO] File : moveFile.bat
  [INFO] Size : 62
  [INFO] PackSize : 16000
  [INFO] NbVolume : 1
  [INFO] Volume 0
	  Sha1 : b4bcdca75363cb7e604db97dc9585f93f3bfe7a9

  [INFO] : File 'moveFile.bat.ndex' had been generate
  ```
  
  Now you can give the output file to our Collector. We will see how in Collector part.
  
##### Boss  

##### Collector

#### How to change into debug mode ?

/!\ All part are in normal use mode by default.

To start the debug mode, you just need to change ( each ) makefile, switch the 
"DEBUG=no" line 2 by "DEBUG=yes", then recompile it and then you can see Debug message.

( Debug mode doesn't change how to use each part ).

If you want the debug mode on windows, please refere to "Windows Compatibility" file.
