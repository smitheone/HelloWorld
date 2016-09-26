#include <linux/device.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>

static ssize_t ftm_alarm_show(struct device *dev,
			      struct device_attribute *attr,
			      char *buf)
{
	printk("###%s,%d###\n",__func__, __LINE__);

	return sprintf(buf, "%u\n", val);
}

static ssize_t ftm_alarm_store(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	printk("###%s,%d###\n",__func__, __LINE__);
}

static struct device_attribute ftm_alarm_attributes = __ATTR(ftm_alarm, 0644,
			ftm_alarm_show, ftm_alarm_store);

static int ftm_alarm_probe(struct platform_device *pdev)
{
	ret = device_create_file(&pdev->dev, &ftm_alarm_attributes);
	if (ret) {
		dev_err(&pdev->dev, "create sysfs fail.\n");
		return ret;
	}

	return ret;
}

static const struct of_device_id ftm_alarm_match[] = {
	{ .compatible = "fsl,time_before", },
	{ },
};

static struct platform_driver ftm_alarm_driver = {
	.probe		= ftm_alarm_probe,
	.driver		= {
		.name	= "time_before",
		.owner	= THIS_MODULE,
		.of_match_table = ftm_alarm_match,
	},
};

static int __init ftm_alarm_init(void)
{
	return platform_driver_register(&ftm_alarm_driver);
}

module_init(ftm_alarm_init);
