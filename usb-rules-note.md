
## rules for WCHLink ICSP

`/etc/udev/rules.d/50-wchlink.rules`:
```
# 1a86:8010 WCH Link
SUBSYSTEM=="usb", ATTR{idVendor}=="1a86", ATTR{idProduct}=="8010", OWNER="ajit"
```


`/etc/udev/rules.d/50-usb-serial.rules`:
```
SUBSYSTEM=="tty", SUBSYSTEMS=="usb", OWNER="ajit"
```

