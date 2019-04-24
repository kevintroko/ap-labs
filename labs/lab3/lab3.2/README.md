Lab 3.2 - Progress Notifier with Signals
========================================
Implement a program for encoding and decoding files by using the `Base64` [algorithm](https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64).
You're free to copy from  previous link's implementation (don't forget to reference to the author's page), the interesting part will be the implementation of signal handlers for progress status.

Add one or multiple signal handlers to catch the `SIGINFO` and `SIGINT`. Once a signal is catched, your program should dislay the current progress of the encoding or deconding tasks.

You will need the proper mechanisms for tracking the progress of any encoding/decoding task. You program must support plain text input files.

Compile
--------
````
make
````

Manual Compilation
--------
````
gcc base64.c logger.c -o base64
````

Encoding
--------
```
./base64 --encode input.txt
```
Your program should generate a new `encoded.txt` file with the result.

Decoding
--------
```
./base64 --decode encoded.txt
```
Your program will generate a `decoded.txt` file witg the result.

How to test?
------------
- Get process ID
```
ps aux | grep base64
```

- Send the signals
```
kill -SIGINT <PID>
kill -SIGINFO <PID>
```

Test files
----------
- [vgilante.txt](http://textfiles.com/stories/vgilante.txt)
- [sick-kid.txt](http://textfiles.com/stories/sick-kid.txt)
- [aesop11.txt](http://textfiles.com/stories/aesop11.txt)
- sgt-pepper.txt (I added this one)

to get the txt files you can simply run 
````
make text
````

Special Thanks 
---------------------------------------
https://en.wikibooks.org/wiki/Algorithm_Implementation/Miscellaneous/Base64