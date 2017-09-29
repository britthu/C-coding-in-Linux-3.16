#commands to run module pid_info.c
make
sudo insmod pid_info.ko pid_var=2 #install module and sets global variable pid_var to 2; you'll see that 2 is the parent of a lot of processes and has a parent 0;
dmesg
sudo rmmod pid_info.ko #removes module
