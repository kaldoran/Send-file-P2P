# NetWork (Fr : Réseau ) Project - P2P Team a.

#### Before anything.
  Before starting anything, you could compile our source code.
  If you are on windows please be sure to Read the "Windows compatibility" File.
  Else you could use our makefile, or use CMake.
  
  Please be sure to compile the part which you want to start before tryingto starting it.
  
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
  You could now start the Generator by writing "./Bin/Boss". 
  
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

##### Understand what append :

If you don't understand a message, please refere here for the boss.


### How to stop programms ? 

To stop the programme, just hit "Enter" on the Boss, same on the Collector.
### How to change into debug mode ?

/!\ All part are in normal use mode by default.

To start the debug mode, you just need to change ( each ) makefile, switch the 
"DEBUG=no" line 2 by "DEBUG=yes", then recompile it and then you can see Debug message.

( Debug mode doesn't change how to use each part ).

If you want the debug mode on windows, please refere to "Windows Compatibility" file.
