// #include <sample_usbd.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>


#include <zephyr/logging/log.h>


#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/class/usb_hid.h>
#include <zephyr/devicetree.h>


#include "kb_misc.h"



LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const uint8_t hid_report_desc[] = {				\
	HID_USAGE_PAGE(HID_USAGE_GEN_DESKTOP),			\
	HID_USAGE(HID_USAGE_GEN_DESKTOP_KEYBOARD),		\
	HID_COLLECTION(HID_COLLECTION_APPLICATION),		\
		HID_USAGE_PAGE(HID_USAGE_GEN_DESKTOP_KEYPAD),	\
		/* HID_USAGE_MINIMUM(Keyboard LeftControl) */	\
		HID_USAGE_MIN8(0xE0),				\
		/* HID_USAGE_MAXIMUM(Keyboard Right GUI) */	\
		HID_USAGE_MAX8(0xE7),				\
		HID_LOGICAL_MIN8(0),				\
		HID_LOGICAL_MAX8(1),				\
		HID_REPORT_SIZE(1),				\
		HID_REPORT_COUNT(8),				\
		/* HID_INPUT(Data,Var,Abs) */			\
		HID_INPUT(0x02),				\
		HID_REPORT_SIZE(8),				\
		HID_REPORT_COUNT(1),				\
		/* HID_INPUT(Cnst,Var,Abs) */			\
		HID_INPUT(0x03),				\
		HID_REPORT_SIZE(1),				\
		HID_REPORT_COUNT(5),				\
		HID_USAGE_PAGE(HID_USAGE_GEN_LEDS),		\
		/* HID_USAGE_MINIMUM(Num Lock) */		\
		HID_USAGE_MIN8(1),				\
		/* HID_USAGE_MAXIMUM(Kana) */			\
		HID_USAGE_MAX8(5),				\
		/* HID_OUTPUT(Data,Var,Abs) */			\
		HID_OUTPUT(0x02),				\
		HID_REPORT_SIZE(3),				\
		HID_REPORT_COUNT(1),				\
		/* HID_OUTPUT(Cnst,Var,Abs) */			\
		HID_OUTPUT(0x03),				\
		HID_REPORT_SIZE(8),				\
		//Change this variable to add more buttons in the report (Keep within the 64 byte limit for USB FS)
		HID_REPORT_COUNT(12),				\ 
		HID_LOGICAL_MIN8(0),				\
		HID_LOGICAL_MAX8(101),				\
		HID_USAGE_PAGE(HID_USAGE_GEN_DESKTOP_KEYPAD),	\
		/* HID_USAGE_MIN8(Reserved) */			\
		HID_USAGE_MIN8(0),				\
		/* HID_USAGE_MAX8(Keyboard Application) */	\
		HID_USAGE_MAX8(101),				\
		/* HID_INPUT (Data,Ary,Abs) */			\
		HID_INPUT(0x00),				\
	HID_END_COLLECTION,					\
};

enum kb_report_idx {
	KB_MOD_KEY = 0,
	KB_RESERVED,
	KB_KEY_CODE1,
	KB_KEY_CODE2,
	KB_KEY_CODE3,
	KB_KEY_CODE4,
	KB_KEY_CODE5,
	KB_KEY_CODE6,
	KB_KEY_CODE7,
	KB_KEY_CODE8,
	KB_KEY_CODE9,
	KB_KEY_CODE10,
	KB_KEY_CODE11,
	KB_KEY_CODE12,
	KB_REPORT_COUNT,
};

// static struct column_data {
//     const struct device *dev;
//     uint32_t pin;	
//     uint8_t index;
//     struct gpio_callback cb;
// };
static enum usb_dc_status_code usb_status;

static void status_cb(enum usb_dc_status_code status, const uint8_t *param)
{
    usb_status = status;
}


static const struct gpio_dt_spec row[] = 
{
    GPIO_DT_SPEC_GET(DT_NODELABEL(row0), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(row1), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(row2), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(row3), gpios),
	GPIO_DT_SPEC_GET(DT_NODELABEL(row4), gpios),
	GPIO_DT_SPEC_GET(DT_NODELABEL(row5), gpios),
};

static const struct gpio_dt_spec column[] = 
{
    GPIO_DT_SPEC_GET(DT_NODELABEL(col0), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col1), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col2), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col3), gpios),
	GPIO_DT_SPEC_GET(DT_NODELABEL(col4), gpios),
	GPIO_DT_SPEC_GET(DT_NODELABEL(col5), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col6), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col7), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col8), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col9), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col10), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col11), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col12), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col13), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col14), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col15), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col16), gpios),
    GPIO_DT_SPEC_GET(DT_NODELABEL(col17), gpios),
};
// static const struct gpio_dt_spec temp = GPIO_DT_SPEC_GET(DT_NODELABEL(led0), gpios);
// K_USEC(100)
struct k_timer my_timer;       //timer interrupt to execute scanning 




static void ALWAYS_INLINE config_row_column(void){
	// gpio_dev = device_get_binding("GPIO_0");
	for(uint8_t i = 0; i<ARRAY_SIZE(row);i++){
		if (!gpio_is_ready_dt(&row[i])) {
			printk("row[%d] could not configure",i);
			// return NULL;
		}
		gpio_pin_configure_dt(&row[i],GPIO_OUTPUT);
		
	}

	for(uint8_t i = 0; i<ARRAY_SIZE(column);i++){
		if (!gpio_is_ready_dt(&column[i])) {
			printk("column[%d] could not configure",i);
			// return NULL;
		}
		gpio_pin_configure_dt(&column[i],GPIO_INPUT|GPIO_PULL_UP);	
	}
}


uint32_t key_data[ROW];
K_MSGQ_DEFINE(key_data_msgq, sizeof(key_data), 2, 1);

void scan_row(void)
{	
	for(uint8_t row_val=0 ; row_val<ROW ; row_val++)
	{
		for(uint8_t j=0 ; j<ROW ; j++)
		{
			gpio_pin_set_dt(&row[j],0);
		}
		gpio_pin_set_dt(&row[row_val],1);
		/* Reading port value register as a whole and sending it to msgq */ 
		key_data[row_val] = *(uint32_t *)(GPIO_0_BASE_REG+GPIO_0_IN_OFFSET);
		// printk("keydata[%d] = %x\n",row_val, key_data[row_val]);
	}
	// printk("\n\n");
	if (k_msgq_put(&key_data_msgq, &key_data, K_NO_WAIT) != 0)
	{
		LOG_ERR("Failed to put new key_data_msgq input event");
	}
}

// // static uint8_t __aligned(sizeof(void *)) pre_report[KB_REPORT_COUNT] = {0,0,0,0,0,0,0,0};
static uint8_t pre_report[KB_NUMBER][KB_REPORT_COUNT];
K_MSGQ_DEFINE(report_msgq1, sizeof(pre_report[0]), 2, 1);
K_MSGQ_DEFINE(report_msgq2, sizeof(pre_report[0]), 2, 1);
bool volatile flag_msg = false;
// // extern uint8_t const modkey[];

void parse_row_data(void)
{
	
	bool volatile flag_modkey=false;
	uint32_t temp[ROW];
	k_msgq_get(&key_data_msgq, temp, K_FOREVER);
	// memset(pre_report, 0, sizeof(pre_report));
	for(uint8_t j = 0 ; j<KB_NUMBER ; j++){
		for(uint8_t i = 0 ; i<ARRAY_SIZE(pre_report[0]); i++){
			pre_report[j][i] = 0;
		}
	}
	// for(uint8_t i = 0 ; i<ARRAY_SIZE(pre_report); i++){
	// 		pre_report[i] = 0;
	// }
	for(uint8_t i = 0 ; i<ROW ; i++)
	{
		temp[i] = ~temp[i];
		if((temp[i] & 0xFE03E71C)!=0){
			flag_msg = true;
			for(uint8_t j = 0 ; j<COL ; j++)
			{
				// This variable stores the value after bitwise shifting the temp.
				uint32_t shift_store;
				shift_store =  temp[i] >> shift[j];
				if(shift_store & 0x00000001)
				{
					// This loop check is key pressed is a mod key
					for(uint8_t h = 0 ; h<8 ; h++)
					{
						if(keyboard_matrix[i][j]==modkey[h])
						{
							//set however many mod keys are pressed 
							pre_report[0][KB_MOD_KEY] |= 1<<h;
							pre_report[1][KB_MOD_KEY] |= 1<<h;
							flag_modkey = true;
							break;
						}
					}
					// if not a modkey, treat as a normal key
					bool flag_placeholder = false;
					if(!flag_modkey)
					{
						for(uint8_t h = KB_KEY_CODE1 ; h<KB_REPORT_COUNT ; h++)
						{
							for(uint8_t r = 0 ; r<KB_NUMBER ; r++){
								if(!pre_report[r][h])
								{
									pre_report[r][h] = keyboard_matrix[i][j];
									flag_placeholder = true;
									break;
								}
							}
							if(flag_placeholder){
								break;
							}
							// if(!pre_report[h])
							// {
							// 	pre_report[h] = keyboard_matrix[i][j];
							// 	break;
							// }
						}
					}		
				}
				flag_modkey = false;
			}
		}
	}
	
	if(flag_msg)
	{
		// for (uint8_t i = 0 ; i<KB_REPORT_COUNT ; i++){
		// 	printk("0x%X    ",pre_report[i]);
		// }
		// printk("\n\n");
		k_msgq_put(&report_msgq1,pre_report[0],K_NO_WAIT);
		k_msgq_put(&report_msgq2,pre_report[1],K_NO_WAIT);
		
	}
}



uint8_t report1[KB_REPORT_COUNT];
uint8_t  report2[KB_REPORT_COUNT];

int main(void)
{
	config_row_column();
	// -----------
	const struct device *hid_dev;
	const struct device *hid_dev2;
	// -----------
	#if defined(CONFIG_USB_DEVICE_STACK_NEXT)
	hid_dev1 = DEVICE_DT_GET_ONE(zephyr_hid_device);
	#else
	hid_dev = device_get_binding("HID_0");
	#endif

	#if defined(CONFIG_USB_DEVICE_STACK_NEXT)
	hid_dev2 = DEVICE_DT_GET_ONE(zephyr_hid_device);
	#else
	hid_dev2 = device_get_binding("HID_1");
	#endif
	// ------------
    if (!hid_dev)
	{
		LOG_ERR("Cannot get HID device"); 
		return 0;
	}
	if (!hid_dev2)
	{
		LOG_ERR("Cannot get HID device"); 
		return 0;
	}
	// ------------
	usb_hid_register_device(hid_dev, hid_report_desc, sizeof(hid_report_desc), NULL);
	usb_hid_init(hid_dev);

	usb_hid_register_device(hid_dev2, hid_report_desc, sizeof(hid_report_desc), NULL);
	usb_hid_init(hid_dev2);
	// ------------
	usb_enable(status_cb);

	k_timer_init(&my_timer,scan_row,NULL);
	k_timer_start(&my_timer,K_USEC(1000),K_USEC(500));



	while (true) {
		parse_row_data();
		if(flag_msg){
			k_msgq_get(&report_msgq1, &report1, K_FOREVER);
			k_msgq_get(&report_msgq2, &report2, K_FOREVER);
			hid_int_ep_write(hid_dev, report1, sizeof(report1), NULL);
			hid_int_ep_write(hid_dev2, report2, sizeof(report2), NULL);
		}




		// k_msleep(1000);

	}

	return 0;
}