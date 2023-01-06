Passing messages between central and external processes

compilation: 

      gcc central.c -o central
      gcc external01.c -o external01
      gcc external02.c -o external02
      gcc external03.c -o external03
      gcc external04.c -o external04


running: 

      ./central // on terminal 1
      ./external01 // on terminal 2
      ./external02 // on terminal 3
      ./external03 // on terminal 4
      ./external04 // on terminal 5



Open five terminals: 

On Terminal 1, run ./central on one terminal. It will wait until the message is sent by all external processes. 

On Terminal 2, run ./external01 // will send it's temperature to central and wait for response
On Terminal 3, run ./external02 // --
On Terminal 4, run ./external03 // --
On Terminal 5, run ./external04 // --
