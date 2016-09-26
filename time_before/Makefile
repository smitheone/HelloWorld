KERN_DIR = ~/stash/linux-sdk2.0
all:
		make -C $(KERN_DIR) M=`pwd` modules 

clean:
		make -C $(KERN_DIR) M=`pwd` modules clean
			rm -rf modules.order

obj-m	+= time_before.o
