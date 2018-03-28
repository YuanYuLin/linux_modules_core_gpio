#
## Makefile for kernel test
#
MODULE_NAME  = iopc_core_gpio

obj-m      := $(MODULE_NAME).o

EXTRA_CFLAGS += -I$(KERNEL_MODULE_DIR)/include/

all:
	make CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) -C $(LINUXKERNELROOT) M=$(KERNEL_MODULE_DIR)
clean:
	make CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) -C $(LINUXKERNELROOT) M=$(KERNEL_MODULE_DIR) clean

