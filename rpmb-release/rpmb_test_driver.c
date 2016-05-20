/*
* AMD RPMB test driver code, by Vincent Wan <vincent.wan@amd.com>
* FCH Linux driver team demo driver code, V1.0.
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <asm/io.h>
#include <asm/ioctl.h>
#include <asm/uaccess.h>
#include <uapi/linux/mmc/ioctl.h>
#include <linux/device.h>
#include <linux/netdevice.h>
#include <linux/mmc/ioctl.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>

#define simple_MAJOR 201
#define SIMP_BLKDEV_DEVICEMAJOR 220
#define SIMP_BLKDEV_BYTES (4*1024*1024)

#define RPMB_REQUEST_READ	4
#define RPMB_REQUEST_KEY	1
/* Request codes */
#define RPMB_REQUEST_KEY	1
#define RPMB_REQUEST_WCOUNTER	2
#define RPMB_REQUEST_WRITE_DATA	3
#define RPMB_REQUEST_READ_DATA	4
#define RPMB_REQUEST_STATUS	5

/* Response code */
#define RPMB_RESPONSE_KEY	0x0100
#define RPMB_RESPONSE_WCOUNTER	0x0200
#define RPMB_RESPONSE_WRITE	0x0300
#define RPMB_RESPONSE_READ	0x0400

static struct class *mem_class;
struct device *pri_dev;
struct block_device *simplebdev;
struct block_device *rpmb_bdev;
struct mmc_blk_ioc_data {
	struct mmc_ioc_cmd ic;
	unsigned char *buf;
	u64 buf_bytes;
};

extern int rpmb_access(struct mmc_blk_ioc_data *idata);
extern int mmc_blk_card_get(struct block_device *bdev);
extern int mmc_card_blk_put(struct block_device *bdev);

//extern struct mmc_ioc_cmd;
/* Structure of RPMB data frame. */
struct rpmb_frame {
	u8 stuff_bytes[196];
	u8 mac[32];
	u8 data[256];
	u8 nonce[16];
	u32 write_counter;
	u16 address;
	u16 block_count;
	u16 result;
	u16 request;
};

struct rpmb_frame *rpmb;
struct mmc_card *mmc_card;

static const char *const rpmb_result_message[] = {
	"Operation OK",
	"General failure",
	"Authentication failure (MAC comparison not matching, MAC calculation failure) ",
	"Counter failure (counters not matching in comparison, counter incrementing failure) ",
	"Address failure (address out of range, wrong address alignment)",
	"Write failure (data/counter/result write failure)",
	"Read failure (data/counter/result read failure)",
	"Authentication Key not yet programmed",
};

static const struct file_operations simple_fops={
	.owner=THIS_MODULE,
};

static struct mmc_blk_ioc_data *mmc_alloc_idata(struct rpmb_frame *rpmb_frame, struct mmc_ioc_cmd *ic)
{
	struct mmc_blk_ioc_data *idata;

	idata = kzalloc(sizeof(*idata), GFP_KERNEL);
	if (!idata)
		return NULL;

	memcpy(&idata->ic, ic, sizeof(idata->ic));

	idata->buf_bytes = 512;

	idata->buf = (unsigned char *)rpmb_frame;

	return idata;
}

int rmpb_request(struct rpmb_frame *s_rpmb, int reliable_write)
{
	int ret = 0;
	struct mmc_ioc_cmd ic;
	struct mmc_blk_ioc_data *idata;
#ifdef __DEBUG__
	u8 *buffer ;
	int i, j;
#endif
	memset(&ic, 0, sizeof(ic));

	ic.write_flag = 1;
	ic.reliable_write_flag = reliable_write;
	ic.opcode = MMC_WRITE_MULTIPLE_BLOCK;
	ic.arg = 0;
	ic.flags = MMC_RSP_R1;
	ic.blksz = 512;
	ic.blocks = 1;

	idata = mmc_alloc_idata(s_rpmb, &ic);
	if (idata < 0) {
		printk("---rmpb_request---mmc_alloc_idata error!!!----------\n");
		return -1;
	}

#ifdef __DEBUG__
	buffer = (u8*)(s_rpmb);

	for (i = 0; i < 512; i = i + 16) {
		for (j = 0; j < 16; j++) {
			printk("%x ", buffer[i+j]);
		}
		printk("\n");
	}

#endif
	ret = rpmb_access(idata);
	if (ret) {

		printk("-----------rmpb_request---------error:%d-------!!\n",ret);
		return ret;
	}

	printk("-----------rmpb_request---------ok-------!!\n");
	return ret;
}

int rmpb_response(struct rpmb_frame *s_rpmb, unsigned short expect_resp)
{
	int ret = 0, request, result;
	struct mmc_ioc_cmd ic;
	struct mmc_blk_ioc_data *idata;

#ifdef __DEBUG__
	u8 *buffer;
	int i, j;
#endif
	memset(&ic, 0, sizeof(ic));
	memset(s_rpmb, 0, sizeof(struct rpmb_frame));

	ic.write_flag = 0;
	ic.reliable_write_flag = 0;
	ic.opcode = MMC_READ_MULTIPLE_BLOCK;
	ic.arg = 0;
	ic.flags = MMC_RSP_R1;
	ic.blksz = 512;
	ic.blocks = 1;

	idata = mmc_alloc_idata(s_rpmb, &ic);
	if (idata < 0) {
		printk("---rmpb_request---mmc_alloc_idata error!!!----------\n");
		return -1;
	}

	printk("Before s_rpmb->request : 0x%x\n", s_rpmb->request);

	ret = rpmb_access(idata);
	if (ret) {

		printk("-----------rmpb_response---------error:%d-------!!\n",ret);
		return ret;
	}

	printk("After s_rpmb->request : 0x%x\n", s_rpmb->request);
#ifdef __DEBUG__
	buffer = (u8*)(s_rpmb);

	for (i = 0; i < 512; i = i + 16) {
		for (j = 0; j < 16; j++) {
			printk("%x ", buffer[i+j]);
		}
		printk("\n");
	}
#endif
	request = be16_to_cpu(s_rpmb->request);

	if (request != expect_resp) {
		printk("-----------rmpb_response error----s_rpmb->request:0x%x, expect_resp:0x%x---!!\n",request, expect_resp);
	}

	result = be16_to_cpu(s_rpmb->result);

	printk("-------rmpb_response result:%s---Write counter expired:%s------------\n", rpmb_result_message[result & 0x07], (result & 0x80)?"Yes":"No");

	return result;
}

/*Here, is basic interface to be accessory for access interface*/
int get_status(unsigned short expect) {

	int ret =0;

	memset(rpmb, 0, sizeof(struct rpmb_frame));

	rpmb->request = cpu_to_be16(RPMB_REQUEST_STATUS);

	ret = rmpb_request(rpmb, 0);
	if (ret) {
		printk("--------get_status---rmpb_request---error:%d-------!!\n",ret);
		return ret;
	}

	ret = rmpb_response(rpmb, expect);
	if (ret) {
		printk("--------get_status---rmpb_response---error:%d-------!!\n",ret);
		return ret;
	}

	return 0;
}

int rpmb_read_counter(unsigned int *pcounter) {

	int ret = 0;

	memset(rpmb, 0, sizeof(struct rpmb_frame));
	rpmb->request = cpu_to_be16(RPMB_REQUEST_WCOUNTER);

	mmc_blk_card_get(rpmb_bdev);

	ret = rmpb_request(rpmb, 0);
	if (ret) {
		printk("--------rpmb_read_counter---rmpb_request---error:%d-------!!\n",ret);
		mmc_card_blk_put(rpmb_bdev);
		return ret;
	}

	ret = rmpb_response(rpmb, RPMB_RESPONSE_WCOUNTER);
	if (ret) {
		printk("--------rpmb_read_counter---rmpb_response---error:%d-------!!\n",ret);
		mmc_card_blk_put(rpmb_bdev);
		return ret;
	}

	mmc_card_blk_put(rpmb_bdev);

	*pcounter = be32_to_cpu(rpmb->write_counter);
	printk("--------rpmb_read_counter, val = %d------!!\n", *pcounter);

	return ret;
}

/*From here, Start to be access interface, Vincent*/

int rpmb_read(void *destbuf, unsigned short start_block, 
		unsigned short block_count, unsigned char *key) {

	int i,ret = 0;

	for (i = 0; i < block_count; i++) {
		memset(rpmb, 0, sizeof(struct rpmb_frame));
		rpmb->request = cpu_to_be16(RPMB_REQUEST_READ);
		rpmb->address = cpu_to_be16(start_block + i);

		mmc_blk_card_get(rpmb_bdev);

		ret = rmpb_request(rpmb, 0);
		if (ret) {
			printk("--------rpmb_read---rmpb_request---error:%d-------!!\n",ret);
			mmc_card_blk_put(rpmb_bdev);
			break;
		}

		ret = rmpb_response(rpmb, RPMB_RESPONSE_READ);
		if (ret) {
			printk("--------rpmb_read---rmpb_response---error:%d-------!!\n",ret);
			mmc_card_blk_put(rpmb_bdev);
			break;
		}

		get_status(RPMB_RESPONSE_READ);

		mmc_card_blk_put(rpmb_bdev);

		memcpy(destbuf + i*256, rpmb->data, 256);

	}

	return i;
}

unsigned char key_data[32];

int rpmb_program_key(void *key) {

	int ret = 0;

	memset(rpmb, 0, sizeof(struct rpmb_frame));
	rpmb->request = cpu_to_be16(RPMB_REQUEST_KEY);
	memcpy(rpmb->mac, key, sizeof(rpmb->mac));

	mmc_blk_card_get(rpmb_bdev);

	ret = rmpb_request(rpmb, 1);
	if (ret) {
		printk("--------rpmb_program_key---rmpb_request---error:%d-------!!\n",ret);
		goto cmd_error;
	}

	ret = get_status(RPMB_RESPONSE_KEY);

cmd_error:
	mmc_card_blk_put(rpmb_bdev);

	return ret;
}

int rpmb_write(void *srcbuf, unsigned short start_block, 
		unsigned short block_count, unsigned char *key) {

	int i,ret = 0;
	unsigned int wcount;

	for (i = 0; i < block_count; i++) {

		if (rpmb_read_counter(&wcount)) {
			printk("---error!!!----Can not read counter-----\n");
			break;			
		}		

		memset(rpmb, 0, sizeof(struct rpmb_frame));
		memcpy(rpmb->data, srcbuf + i*256, 256);
		rpmb->request = cpu_to_be16(RPMB_REQUEST_WRITE_DATA);
		rpmb->address = cpu_to_be16(start_block + i);
		rpmb->block_count = cpu_to_be16(1);
		rpmb->write_counter = cpu_to_be16(wcount);

		mmc_blk_card_get(rpmb_bdev);

		ret = rmpb_request(rpmb, 1);
		if (ret) {
			printk("--------rpmb_write---rmpb_request---error:%d-------!!\n",ret);
			mmc_card_blk_put(rpmb_bdev);
			break;
		}

		ret = rmpb_response(rpmb, RPMB_RESPONSE_WRITE);
		if (ret) {
			printk("--------rpmb_write---rmpb_response---error:%d-------!!\n",ret);
			mmc_card_blk_put(rpmb_bdev);
			break;
		}

		mmc_card_blk_put(rpmb_bdev);
	}

	return i;
}
/*
* Here below: call function, test triger function in user side, Vincent Wan.
* write_blk: no use.
* program_key, read_counter, write_data, read_data: used to test rpmb basic API.
* eg: "cat /sys/class/testdriver/testdriver0/readcounter" is to triger 'read_counter'
*/
static ssize_t
write_blk(struct device *dev, struct device_attribute *devattr, const char *buf, size_t count)
{
	unsigned long val;
	if (kstrtoul(buf, 16, &val))
		return -EINVAL;

	return count;
}

static ssize_t
program_key(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int val;
	val = 0x1;
	memset(key_data, 0, 32);
	key_data[0] = 0x11;
	key_data[1] = 0x22;
	key_data[2] = 0x33;
	key_data[3] = 0x44;

	rpmb_program_key(key_data);

	return sprintf(buf, "0x%x\n", val);
}

static ssize_t
read_counter(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int val;

	rpmb_read_counter(&val);

	return sprintf(buf, "0x%x\n", val);
}

static ssize_t
write_data(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int val;
	unsigned char data[256];
	memset(data, 0xaa, 256);
	val = rpmb_write(data, 0, 1, 0);

	return sprintf(buf, "0x%x\n", val);
}

static ssize_t
read_data(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int val = 0;
	unsigned char data[256];
	
	rpmb_read(data, 0, 1, 0);

	return sprintf(buf, "0x%x\n", val);
}

static DEVICE_ATTR(setkey, S_IROTH | S_IRUSR, program_key, NULL);
static DEVICE_ATTR(writeblk, S_IWOTH | S_IWUSR, NULL, write_blk);
static DEVICE_ATTR(readcounter, S_IROTH | S_IRUSR, read_counter, NULL);
static DEVICE_ATTR(readdata, S_IROTH | S_IRUSR, read_data, NULL);
static DEVICE_ATTR(writedata, S_IROTH | S_IRUSR, write_data, NULL);

void simple_cleanup_module(void){
	device_remove_file(pri_dev, &dev_attr_setkey);
	device_remove_file(pri_dev, &dev_attr_readdata);
	device_remove_file(pri_dev, &dev_attr_writedata);
	device_remove_file(pri_dev, &dev_attr_readcounter);
	device_remove_file(pri_dev, &dev_attr_writeblk);
	device_destroy(mem_class, MKDEV(simple_MAJOR, 0));
	class_destroy(mem_class);
	unregister_chrdev(simple_MAJOR,"testdriver");

	kfree(rpmb);

	printk("simple_cleanup_module!\n");
}

int simple_init_module(void){
	int ret;

	ret = register_chrdev(simple_MAJOR,"testdriver",&simple_fops);
	if(ret<0){
		printk("Unable to register character device %d!/n",simple_MAJOR);
		return ret;
	}
	printk("Ok to register character device %d!/n",simple_MAJOR);

	mem_class = class_create(THIS_MODULE, "testdriver");
	if (IS_ERR(mem_class))
		return PTR_ERR(mem_class);

	pri_dev = device_create(mem_class, NULL, MKDEV(simple_MAJOR, 0),
			      NULL, "testdriver0");

	device_create_file(pri_dev, &dev_attr_setkey);
	device_create_file(pri_dev, &dev_attr_readcounter);
	device_create_file(pri_dev, &dev_attr_readdata);
	device_create_file(pri_dev, &dev_attr_writedata);
	device_create_file(pri_dev, &dev_attr_writeblk);

	simplebdev = blkdev_get_by_dev(MKDEV(SIMP_BLKDEV_DEVICEMAJOR, 0),
					    FMODE_READ | FMODE_WRITE, NULL);

	/*Please note, you need add those codes into your psp driver,Vincent*/
	rpmb = kzalloc(sizeof(*rpmb), GFP_KERNEL);
	if (!rpmb) {
		printk("-----------rpmb allocated failed---------------\n");
		return -ENOMEM;
	}


	/*Please note, you need add those codes into your psp driver,Vincent*/
	
	rpmb_bdev = blkdev_get_by_dev(MKDEV(179, 24), FMODE_READ | FMODE_WRITE, NULL);

	return 0;
}

module_init(simple_init_module);
module_exit(simple_cleanup_module);

MODULE_LICENSE("GPL");


