


### Setup
```
Default in RPI3
$ cat /boot/cmdline.txt
dwc_otg.lpm_enable=0 console=serial0,115200 consoleblank=0 console=tty1 root=PARTUUID=85e72df7-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait quiet splash plymouth.ignore-serial-consoles
```
-->
```
$ cat /boot/cmdline.txt
dwc_otg.lpm_enable=0 console=serial0,115200 consoleblank=0 console=tty1 root=PARTUUID=85e72df7-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait quiet splash plymouth.ignore-serial-consoles enable_uart=1
```

### References
```
https://www.raspberrypi.org/forums/viewtopic.php?t=155559
```

