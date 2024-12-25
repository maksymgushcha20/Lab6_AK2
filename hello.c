#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/bug.h>
#include <linux/timekeeping.h>
#include <linux/moduleparam.h>

struct time_data {
    struct timespec64 start_time;
    struct list_head list;
};

static LIST_HEAD(time_list);
static int kmalloc_counter = 0;
#define KMALLOC_FAIL_ON 5
static int some_param = 0;
module_param(some_param, int, 0644);
MODULE_PARM_DESC(some_param, "An example integer parameter");

static int __init hello_init(void) {
    struct time_data *time_data;
    int ret = 0;

    if (some_param < 0) {
        BUG_ON(1);
    }

    kmalloc_counter++;
    if (kmalloc_counter == KMALLOC_FAIL_ON) {
        time_data = NULL;
    } else {
        time_data = kmalloc(sizeof(*time_data), GFP_KERNEL);
    }
    BUG_ON(!time_data);

    ktime_get_real_ts64(&time_data->start_time);
    list_add_tail(&time_data->list, &time_list);

    printk(KERN_INFO "hello: Module loaded successfully\n");
    return ret;
}

static void __exit hello_exit(void) {
    struct time_data *entry, *tmp;

    list_for_each_entry_safe(entry, tmp, &time_list, list) {
        list_del(&entry->list);
        kfree(entry);
    }

    printk(KERN_INFO "hello: Module unloaded successfully\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module with BUG_ON and kmalloc simulation");
MODULE_AUTHOR("Maksym Hushcha");

