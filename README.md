# NetWork (Fr : Réseau ) Project - P2P Team a.

#### Before anything.
  Before starting anything, you could compile our source code.
  If you are on windows please be sure to Read the "Windows compatibility" File.
  Else you could use our makefile, or use CMake.
  
  Please be sure to compile the part which you want to start before tryingto starting it.
  
  If you are a bit lazy, and you are on linux,
  you could use the ./Scripts_Automatisation/make_all.sh" script.
  
  You juste need to write : "./make_all.sh".
  
  Ps : you could use every compilation option by adding it at end of "./make_all.sh".
  Ex : ./make_all.sh rebuild
  	That's going to rebuild each program.

### Compile option 

Here is the list of all compile option which you can use with our makefile.
 - make ( Create an executable program )
 - make all ( same as make )
 - make clean ( Clean the project )
 - make rebuild (Same as make clean followed by make )
 - make dir ( Create OBJ and BIn dir , this on is included in make / make all / make rebuild )
 

### How to use it / test it ?

#### Generator 
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
  
#### Boss  
  First ( after compile that ) a new "Bin" directory appear.
  You could now start the Generator by writing "./Bin/Server". 
  
  Exemple of use :
  
  ```
  > ./BIN/Server 
  [IMPORTANT] : Press Enter to Stop the Boss
  ```
  
##### Understand what append :

If you don't understand a message, please refere here for the boss.

**/!\ Here we are not going to cover the debug mode.**

----------------

###### New Client 


```
[INFO] New client [6]
 - Ip : 127.0.0.1
 - File : moveFile.bat
 - Port : 42450
```
Here a new client came on the Boss.
We can see is Ip, for which file he came, and on which port Others Collector need to connect to.

As you may see the number of the client does not start at "1", 6 is the socket number.
Please refere to that for all message.

If the client does not respond in time we've got this message : 
```
[INFO] New client [21]
	 - Ip : 127.0.0.1
[ERROR] Client 21 does not send information in time
```
By default, the client need to send information in less that 500 ms.

----------------

###### List Of Collector

```
[INFO] (18) message recu 'ListOfCollectors' [Client : 6]
```
Here the Client 6 ask for "ListOfCollectors" according to convention we need to send him back a message.
```
[INFO] Client 6 is alone
```
Here as he is alone we send him "aloneCollector". We can know that thanks to the previous message.

----------------

###### PING / PONG

Every 5 minutes, we send a "ping" message ( which is not ping but we identify it by "ping" )
```
[PING] Let send the ping test !
```
After 1 minute we check if Collectors respond.
```
[PONG] Let check the pong result 
```
If all client respond in time, nothing should be print under the [PONG] message. (  We do not print something to avoid flood )
```
[INFO] Client 6 do not respond to ping in time.
[INFO] Client 6 disconnect
```
Here our dear Client 6 does not respond in time, we kick him.

----------------

###### Server Stop
When you hit "Enter" the Boss will stop, you should get this message : 
```
[BYE] Server stop
```

But if there is still some collector, we kick them, and add a message for each kicked Collectors.
These message look like that : 
```
[KICK] Stop socket of client 22
```
Here we kick the client with the 22th socket.

----------------

#### Collector
  First ( after compile that ) a new "Bin" directory appear.
  You could now start the Generator by writing "./Bin/Collector". 
  
  Then you just need to answer to Question. 
  
  Exemple of use : 
```
Which .ndex do you want to use ?
../Generator/Makefile.ndex

[Q] On which port do you want to start the collector ?
47777

[Q] What is your sharing repository ? [Be carefull, if it doesn't exists we'll create it !]
Share

[IMPORTANT] : Press Enter to Stop the Collector
```
##### A bit of configuration :
We are aware that's this is boring to always fill the "Saring path" so you could configure it by using
"./Collector/INC/configuration.h"

You just need to read the content of this file.
Don't forget to "make rebuild" at the end.

##### Understand what append :

---------------------------------------------------------

###### Start an index
```
[INFO] Check if we've got the file to download.
[ERROR] 'Makefile' does not exist.
	 Then we create it

[INFO] Ask for other collectors.
[INFO] We are alone for the moment.
```
Here we haven't the file in the sharing repository. So the program creates a file temporary filled by '#' characters in the waiting of the real volumes.

If we have the file complete, the program says:
```
[INFO] Check if we've got the file to download.
	 - we've got all volume
```

If the file exists, but is not complete, the program says:
```
[INFO] Check if we've got the file to download.
	 - Some volumes are missing

[INFO] Ask for other collectors.
```

--------------------------------------------------------------------------------

###### List of Volumes and List of Collectors

The program notify its request for a list of Collector by:
```
[INFO] Ask for other collectors.
```

If there is no Collector which has the file:
```
[INFO] We are alone for the moment.
```

Else :
```
	 - Collector : 1 [127.0.0.1:47788]
	[INFO] Ask the list of volume [Socket : 21].
		 - 21 got them all.
	 - Collector : 0 [127.0.0.1:47789]
[ERROR] Can't connect to collector.
```
Here, two Collectors have the file, one has the complete file, the other is not reachable (maybe disconnected).

When the program recieve a request for tis list of volumes it notify by
```
[INFO] (14) message recu 'ListOfVolumes' [Client : 24].
```

----------------------------------------------------------------------------------------------------------------

###### Asking volumes

After the program has filled the collectors list it start to ask volumes.
```
[INFO] Ask volume 0 to Client 21
```

If the collector is not reachable, the program says:
```
[ERROR] Client 21 does not send information in time
```

Then if there is too much collectors unreachable, the program asks a new colectors list to the boss:
```
[ERROR] To much people are useless.We're going to change the list.
```

When the program recieve a volume request it notify it by:
```
[INFO] (9) message recu 'Vol0' [Client : 22].
	 - Send volume 0 to 22
```

----------------------------------------------------------------------------------------------------------------

###### PING/PONG

Every 5 minutes the boss asks if the collector is still connected and has the file.
The program notify the reception of the ping request by:
```
[INFO] Received ping from Boss.
```


### How to stop programms ? 

To stop the programme, just hit "Enter" on the Boss, same on the Collector.


### How to change into debug mode ?

/!\ All part are in normal use mode by default.

To start the debug mode, you just need to change ( each ) makefile, switch the 
"DEBUG=no" line 2 by "DEBUG=yes", then recompile it and then you can see Debug message.

When debug mode is on, you could use each program with argument of the program.
That's avoid to get all questions !

/!\ If You want to try / use script that test automatically things you need to use debug mode !

If you want the debug mode on windows, please refere to "Windows Compatibility" file.
