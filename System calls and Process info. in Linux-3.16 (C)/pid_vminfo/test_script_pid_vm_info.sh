make
sudo insmod pid_vminfo.ko
dmesg
cat /proc/pid_vminfo #print from file to screen
sudo rmmod pid_vminfo.ko
