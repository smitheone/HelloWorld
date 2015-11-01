#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#include <linux/kernel.h>
#include "memdev.h"

static int mem_major = MEMDEV_MAJOR;

module_param(mem_major,int,S_IRUGO);

struct mem_dev *mem_devp;

struct cdev cdev;

int mem_open(struct inode *inode,struct file *filp)
{
    struct mem_dev *dev;

    int num = MINOR(inode->i_rdev);

    if(num > MEMDEV_NR_DEVS)
	return -ENODEV;
    
    dev = &mem_devp[num];

    filp->private_data = dev;

    return 0;
}

int mem_release(struct inode *inode, struct file *filp)
{
      return 0;
}

static int memdev_mmap(struct file *filp,struct vm_area_struct *vma)
{
    struct mem_dev *dev = filp->private_data;

    vma->vm_flags |= VM_IO;
    vma->vm_flags |= VM_RESERVED;

    if(remap_pfn_range(vma,vma->vm_start,virt_to_phys(dev->data)>>PAGE_SHIFT,vma->end - vma->start,vma->vm_page_port))
    {
	return -EAGAIN;
    }
	
    return 0;
}

static const struct file_operations mem_fops =
{
      .owner = THIS_MODULE,
      .open = mem_open,
      .release = mem_release,
      .mmap = memdev_mmap,
};

static int memdev_init(void)
{
    int result;
    int i;
    
    dev_t devno = MKDEV(mem_major,0);

    if (mem_major)
	result = register_chrdev_region(devno,2,"memdev");
    else
    {
	result = alloc_chrdev_region(&devno,0,2,"memdev");
	mem_major = MAJOR(devno);
    }

    if(result)
	return result;

    cdev_init(&cdev,&mem_fops);
    cdev.owner = THIS_MODULE;
    cdev.ops = &mem_fops;

    cdev_add(&cdev,MKDEV(mem_major,0),MKDEV_NR_DEVS);

    mem_devp = kmalloc(MEMDEV_NR_DEVS *sizeof(struct mem_dev),GFP_KERNEL);
    if(!mem_devp)
    {
	result = -ENOMEM;
	goto fail_malloc;
    }

    memset(mem_devp,0,sizeof(struct mem_dev));

    for(i=0;i<MEMDEV_NR_DEVS;i++)
    {
	mem_devp[i].size = MEMDEV_SIZE;
	mem_devp[i].data = kmalloc(MEMDEV_SIZE, GFP_KERNEL);
	memset(mem_devp[i].data, 0, MEMDEV_SIZE);
    }

    return 0;

    fail_malloc: 
    unregister_chrdev_region(devno, 1);
        
    return result;
}

static void memdev_exit(void)
{
    cdev_del(&cdev);   /*注销设备*/
    kfree(mem_devp);     /*释放设备结构体内存*/
    unregister_chrdev_region(MKDEV(mem_major, 0), 2); /*释放设备号*/
}

MODULE_AUTHOR("David Xie");
MODULE_LICENSE("GPL");

module_init(memdev_init);
module_exit(memdev_exit);
