#ifndef IOPC_CORE_GPIO_H
#define IOPC_CORE_GPIO_H

struct iopc_gpio_t {
	spinlock_t		lock;
	struct gpio_chip	gc;
};

extern int register_gpio_list(int count, struct iopc_gpio_t* list);
extern int unregister_gpio_list(int count, struct iopc_gpio_t* list);

#endif
