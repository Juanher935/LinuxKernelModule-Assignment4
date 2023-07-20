KBUILD_CFLAGS += -w
obj-m += Project4.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
unload:
	sudo rmmod Project4
load:
	sudo insmod Project4.ko
clear:
	sudo dmesg -c
view:
	dmesg