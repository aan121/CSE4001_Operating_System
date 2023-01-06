TCP socket between central and external process

compilation: 

      gcc central.c -o central
      gcc external.c -o external
      
running: 

      ./central // on terminal 1
      ./external // on terminal 2

Open two terminals: 

On Terminal 1, run ./central on one terminal. It will wait until the message is sent by external client. 

On Terminal 2, run ./external // will send it's temperature to central server and wait for response.
