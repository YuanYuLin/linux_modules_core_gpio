#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include "iopc_core_gpio.h"

static int iopc_gpio_request(struct gpio_chip* gc, unsigned gpio_pin)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x, %x, %s\n", gpio_pin, gc->base, gc->label);
	return 0;
}

static int iopc_gpio_get_direction(struct gpio_chip* gc, unsigned offset)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x\n", offset);
	return 0;
}

static int iopc_gpio_direction_input(struct gpio_chip* gc, unsigned offset)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x\n", offset);
	return 0;
}

static int iopc_gpio_direction_output(struct gpio_chip* gc, unsigned offset, int value)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x, %x\n", offset, value);
	return 0;
}

static int iopc_gpio_get(struct gpio_chip* gc, unsigned offset)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x\n", offset);
	return 0;
}

static void iopc_gpio_set(struct gpio_chip* gc, unsigned offset, int value)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x, %x\n", offset, value);
}

static void iopc_gpio_set_multiple(struct gpio_chip* gc, unsigned long *mask, unsigned long *bits)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
}

static int iopc_gpio_set_debounce(struct gpio_chip* gc, unsigned offset, unsigned debounce)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x, %x\n", offset, debounce);
	return 0;
}

static int iopc_gpio_to_irq(struct gpio_chip* gc, unsigned offset)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x\n", offset);
	return 0;
}

static void iopc_gpio_dbg_show(struct seq_file *s, struct gpio_chip* gc)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
}

static void iopc_gpio_free(struct gpio_chip* gc, unsigned offset)
{
	printk(KERN_DEBUG "%s %s %d\n", __FILE__, __func__, __LINE__);
	printk(KERN_DEBUG "%x\n", offset);
}

int register_gpio_list(int count, struct iopc_gpio_t* list)
{
	struct iopc_gpio_t* gpio = NULL;
	struct gpio_chip* gc = NULL;
	int ret = -1;
	int i = 0;
	for(i=0; i<count; i++) {
		gpio = &list[i];
		gc = &gpio->gc;
		spin_lock_init(&gpio->lock);

		if(!gc->request)
			gc->request = iopc_gpio_request;

		if(!gc->get_direction)
			gc->get_direction = iopc_gpio_get_direction;

		if(!gc->direction_input)
			gc->direction_input = iopc_gpio_direction_input;

		if(!gc->direction_output)
			gc->direction_output = iopc_gpio_direction_output;

		if(!gc->get)
			gpio->gc.get = iopc_gpio_get;

		if(!gc->set)
			gc->set = iopc_gpio_set;

		if(!gc->set_multiple)
			gc->set_multiple = iopc_gpio_set_multiple;

		if(!gc->set_debounce)
			gc->set_debounce = iopc_gpio_set_debounce;

		if(!gc->to_irq)
			gc->to_irq = iopc_gpio_to_irq;

		if(!gc->dbg_show)
			gc->dbg_show = iopc_gpio_dbg_show;

		if(!gc->free)
			gc->free = iopc_gpio_free;

		ret = gpiochip_add(gc);
		printk(KERN_INFO "register %s %d\n", gc->label, ret);
	}
	return 0;
}
EXPORT_SYMBOL_GPL(register_gpio_list);

int unregister_gpio_list(int count, struct iopc_gpio_t* list)
{
	struct iopc_gpio_t* gpio = NULL;
	struct gpio_chip* gc = NULL;
	int i = 0;
	for(i=0; i<count; i++) {
		gpio = &list[i];
		gc = &gpio->gc;
		//spin_lock_init(&gpio->lock);
		gpiochip_remove(gc);
		printk(KERN_INFO "unregister %s\n", gc->label);
		if(gpio)
			kfree(gpio);
	}
	return 0;
}
EXPORT_SYMBOL_GPL(unregister_gpio_list);

static const struct file_operations iopc_gpio_miscdev_ops = {
	.owner		= THIS_MODULE,
};

static struct miscdevice iopc_gpio_miscdev = {
	.nodename	= "iopc_gpio",
	.name		= "iopc_gpio",
	.fops		= &iopc_gpio_miscdev_ops,
};

static int iopc_gpio_init(void)
{
	printk(KERN_INFO "IOPC Core GPIO init.\n");

	misc_register(&iopc_gpio_miscdev);

	return 0;
}

static void iopc_gpio_exit(void)
{
	printk(KERN_INFO "IOPC Core GPIO destroy\n");

	misc_deregister(&iopc_gpio_miscdev);
}

module_init(iopc_gpio_init);
module_exit(iopc_gpio_exit);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("YuanYu Lin <yuanyu.lin@gmail.com>");
MODULE_DESCRIPTION("IOPC Core GPIO driver");
