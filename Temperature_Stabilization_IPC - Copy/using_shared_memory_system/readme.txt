Shared memories between central and external processes

compilation: 

      gcc central.c -o central
      gcc external01.c -o external01
      gcc external02.c -o external02
      gcc external03.c -o external03
      gcc external04.c -o external04


running: 

      ./central // on terminal 1
      ./external01 & ./external02 & ./external03 & ./external04 // on terminal 2


Open two terminals: 

On Terminal 1, run ./central on one terminal. It will wait until it gets the temperature from all external processes. 

On Terminal 2, run ./external01 & ./external02 & ./external03 & ./external04 // will share their temperatures to central and start the process

you need to run the external processes at the same time as mentioned above after running the central in order to run it correctly and avoid errors.

it might take a couple of seconds for these processes to print their outputs and finish. 
