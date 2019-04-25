# system-v-message-queues

## Get List of all IPC on the machine
    $ ipcs
## Compile
    $ gcc svmsg_send.c -o svmsg_send.out ../lib/error_functions.c ../lib/get_num.c
    $ gcc svmsg_create.c -o svmsg_create.out ../lib/error_functions.c ../lib/get_num.c
    $ gcc svmsg_receive.c -o svmsg_receive.out ../lib/error_functions.c ../lib/get_num.c

## Run
    $ ./svmsg_create.out -p
    32769                                           ID of message queue
    $ ./svmsg_send 32769 20 "I hear and I forget."
    $ ./svmsg_send.out 32769 10 "I see and I remember."
    $ ./svmsg_send.out 32769 30 "I do and I understand."

    $ ./svmsg_receive.out  -t -20 32769
    Received: type=10; length=22; body=I see and I remember.
    $ ./svmsg_receive.out  -t -20 32769
    Received: type=20; length=21; body=I hear and I forget.
    $ ./svmsg_receive.out  32769
    Received: type=30; length=23; body=I do and I understand.

Done :) !