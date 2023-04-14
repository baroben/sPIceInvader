#include <linux/version.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/time.h>

#define ULTRASONIC_PIN 6
#define LOW 0
#define HIGH 1

long duration(uint32_t timeout);
int __init my_driver_01_init (void)
{
	int err;
	int i;
	
	printk(KERN_INFO "%s:␣chargexxXment␣du␣module\n",THIS_MODULE->name);
	if((err = gpio_request(ULTRASONIC_PIN,THIS_MODULE->name)) != 0){
		return err;
	}
        if ((err = gpio_direction_input(ULTRASONIC_PIN)) != 0) {
               gpio_free(ULTRASONIC_PIN);
               return err;
        }

	//	for(i=0;i<10000;i++)	
//	printk(KERN_INFO "%d\n",gpio_get_value(ULTRASONIC_PIN));
	duration(1000);	

	return 0;
}
static void __exit my_driver_01_exit (void)
{
	printk(KERN_INFO "%s:retraitdumodule\n",THIS_MODULE->name);
}

long duration(uint32_t timeout) {

    int err;
    long duration;
    
    if ((err = gpio_direction_output(ULTRASONIC_PIN, 1)) != 0) {
    	gpio_free(ULTRASONIC_PIN);
    	return err;
    }
    
    gpio_set_value(ULTRASONIC_PIN, LOW);
    
    msleep(2);
    
    gpio_set_value(ULTRASONIC_PIN, HIGH);
    
    msleep(5);
    
    gpio_set_value(ULTRASONIC_PIN, LOW);
    
    if ((err = gpio_direction_input(ULTRASONIC_PIN)) != 0) {
    	gpio_free(ULTRASONIC_PIN);
    	return err;
    }
	
    duration = 1;// pulseIn(ULTRASONIC_GPIO, HIGH, timeout);
    return duration;
}

module_init(my_driver_01_init);
module_exit(my_driver_01_exit);

MODULE_LICENSE("GPL");
