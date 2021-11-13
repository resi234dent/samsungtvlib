# samsungtvlib
Simple C++ library to remotely control Samsung TV (2016). Currently, it's a draft version and it's only built on MacOS.

Dependencies
============
On MacOS, next prerequisites have to be met:

- C++ 14 and higher
- CMake
- **boost** (you can install it using **brew** as follows `brew install boost` 

Build
============
One way is to just open it in your IDE and build it.

Usage
============
Locate the built file **samsunglibtv** and run

`./samsungtvlib --help`

This will print currently supported options:

    Options:
      --help                Help screen
      --ip arg              TV IP Address
      --port arg (=8002)    TV port number
      --command arg         TV command name

For example, to turn down the TV volume on a TV with an IP `192.168.1.110`, run the following command:

    ./samsungtvlib --ip 192.168.1.110 --command KEY_VOLDOWN


Reference
============
https://github.com/Ape/samsungctl
