#include "st7789.h"
#include "spi.h"

/* 定义ATK-MD0130模块LCD显存 */
#define ATK_MD0130_LCD_BUF_SIZE (ATK_MD0130_LCD_WIDTH * ATK_MD0130_LCD_HEIGHT)
uint16_t g_st7789_lcd_buf[ATK_MD0130_LCD_BUF_SIZE] = {0};

extern __IO uint8_t ucStatues;

/**
 * @brief       ATK-MD0130模块SPI接口发送数据
 * @param       无
 * @retval      无
 */
void st7789_spi_send(uint8_t *buf, uint16_t len)
{
	HAL_SPI_Transmit(&hspi2, buf, len, HAL_MAX_DELAY);
}

/**
 * @brief       往ATK-MD0130模块写命令
 * @param       无
 * @retval      无
 */
static void st7789_write_cmd(uint8_t cmd)
{
    ATK_MD0130_WR(0);
    st7789_spi_send(&cmd, sizeof(uint8_t));
}

/**
 * @brief       往ATK-MD0130模块写数据
 * @param       无
 * @retval      无
 */
static void st7789_write_dat(uint8_t dat)
{
    ATK_MD0130_WR(1);
    st7789_spi_send(&dat, sizeof(uint8_t));
}

/**
 * @brief       往ATK-MD0130模块写16bit数据
 * @param       无
 * @retval      无
 */
static void st7789_write_dat_16b(uint16_t dat)
{
    uint8_t buf[2] = {0};
	
	buf[0] = dat >> 8;
	buf[1] = dat;
	
    ATK_MD0130_WR(1);
	st7789_spi_send(buf, 2);
}

/**
 * @brief       ATK-MD0130模块硬件初始化
 * @param       无
 * @retval      无
 */
static void st7789_hw_init(void)
{
    ATK_MD0130_CS(0);
}

/**
 * @brief       ATK-MD0130模块硬件复位
 * @param       无
 * @retval      无
 */
static void st7789_hw_reset(void)
{
    ATK_MD0130_RST(0);
    HAL_Delay(10);
    ATK_MD0130_RST(1);
    HAL_Delay(120);
}

/**
 * @brief       ATK-MD0130模块寄存器初始化
 * @param       无
 * @retval      无
 */
static void st7789_reg_init(void)
{
    /* Sleep Out */
    st7789_write_cmd(0x11);
    HAL_Delay(120);
    /* Memory Data Access Control */
	st7789_write_cmd(0x36);
	
	if(USE_HORIZONTAL == 0)
		st7789_write_dat(0x00);
	else if(USE_HORIZONTAL == 1)
		st7789_write_dat(0xC0);
	else if(USE_HORIZONTAL == 2)
		st7789_write_dat(0x70);
	else
		st7789_write_dat(0xA0);
    /* RGB 5-6-5-bit  */
    st7789_write_cmd(0x3A);
    st7789_write_dat(0x65);
    /* Porch Setting */
    st7789_write_cmd(0xB2);
    st7789_write_dat(0x0C);
    st7789_write_dat(0x0C);
    st7789_write_dat(0x00);
    st7789_write_dat(0x33);
    st7789_write_dat(0x33);
    /*  Gate Control */
    st7789_write_cmd(0xB7);
    st7789_write_dat(0x72);
    /* VCOM Setting */
    st7789_write_cmd(0xBB);
    st7789_write_dat(0x3D);
    /* LCM Control */
    st7789_write_cmd(0xC0);
    st7789_write_dat(0x2C);
    /* VDV and VRH Command Enable */
    st7789_write_cmd(0xC2);
    st7789_write_dat(0x01);
    /* VRH Set */
    st7789_write_cmd(0xC3);
    st7789_write_dat(0x19);
    /* VDV Set */
    st7789_write_cmd(0xC4);
    st7789_write_dat(0x20);
    /* Frame Rate Control in Normal Mode */
    st7789_write_cmd(0xC6);
    st7789_write_dat(0x0F);
    /* Power Control 1 */
    st7789_write_cmd(0xD0);
    st7789_write_dat(0xA4);
    st7789_write_dat(0xA1);
    /* Positive Voltage Gamma Control */
    st7789_write_cmd(0xE0);
    st7789_write_dat(0xD0);
    st7789_write_dat(0x04);
    st7789_write_dat(0x0D);
    st7789_write_dat(0x11);
    st7789_write_dat(0x13);
    st7789_write_dat(0x2B);
    st7789_write_dat(0x3F);
    st7789_write_dat(0x54);
    st7789_write_dat(0x4C);
    st7789_write_dat(0x18);
    st7789_write_dat(0x0D);
    st7789_write_dat(0x0B);
    st7789_write_dat(0x1F);
    st7789_write_dat(0x23);
    /* Negative Voltage Gamma Control */
    st7789_write_cmd(0xE1);
    st7789_write_dat(0xD0);
    st7789_write_dat(0x04);
    st7789_write_dat(0x0C);
    st7789_write_dat(0x11);
    st7789_write_dat(0x13);
    st7789_write_dat(0x2C);
    st7789_write_dat(0x3F);
    st7789_write_dat(0x44);
    st7789_write_dat(0x51);
    st7789_write_dat(0x2F);
    st7789_write_dat(0x1F);
    st7789_write_dat(0x1F);
    st7789_write_dat(0x20);
    st7789_write_dat(0x23);
    /* Display Inversion On */
    st7789_write_cmd(0x21);
    st7789_write_cmd(0x29);
}

/**
 * @brief       设置ATK-MD0130模块行列地址
 * @param       xs: 列起始地址
 *              ys: 行起始地址
 *              xe: 列结束地址
 *              ye: 行结束地址
 * @retval      无
 */
void st7789_set_address(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    if(USE_HORIZONTAL == 0)
	{
		st7789_write_cmd(0x2A);
		st7789_write_dat_16b(xs + 52);
		st7789_write_dat_16b(xe + 52);
		st7789_write_cmd(0x2B);
		st7789_write_dat_16b(ys + 40);
		st7789_write_dat_16b(ye + 40);
		st7789_write_cmd(0x2C);
	}
	else if(USE_HORIZONTAL == 1)
	{
		st7789_write_cmd(0x2A);
		st7789_write_dat_16b(xs + 53);
		st7789_write_dat_16b(xe + 53);
		st7789_write_cmd(0x2B);
		st7789_write_dat_16b(ys + 40);
		st7789_write_dat_16b(ye + 40);
		st7789_write_cmd(0x2C);
	}
	else if(USE_HORIZONTAL == 2)
	{
		st7789_write_cmd(0x2A);
		st7789_write_dat_16b(xs + 40);
		st7789_write_dat_16b(xe + 40);
		st7789_write_cmd(0x2B);
		st7789_write_dat_16b(ys + 53);
		st7789_write_dat_16b(ye + 53);
		st7789_write_cmd(0x2C);
	}
	else
	{
		st7789_write_cmd(0x2A);
		st7789_write_dat_16b(xs + 40);
		st7789_write_dat_16b(xe + 40);
		st7789_write_cmd(0x2B);
		st7789_write_dat_16b(ys + 52);
		st7789_write_dat_16b(ye + 52);
		st7789_write_cmd(0x2C);
	}
}

/**
 * @brief       ATK-MD0130模块初始化
 * @param       无
 * @retval      无
 */
void st7789_init(void)
{
    st7789_hw_init();
    st7789_hw_reset();
    st7789_reg_init();
    st7789_display_on();
}

/**
 * @brief       开启ATK-MD0130模块LCD背光
 * @param       无
 * @retval      无
 */
void st7789_display_on(void)
{
    ATK_MD0130_PWR(1);
}

/**
 * @brief       关闭ATK-MD0130模块LCD背光
 * @param       无
 * @retval      无
 */
void st7789_display_off(void)
{
    ATK_MD0130_PWR(0);
}

/**
 * @brief       ATK-MD0130模块LCD区域填充
 * @param       xs   : 区域起始X坐标
 *              ys   : 区域起始Y坐标
 *              xe   : 区域终止X坐标
 *              ye   : 区域终止Y坐标
 *              color: 区域填充颜色
 * @retval      无
 */
void st7789_fill_block(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color)
{
    uint32_t area_size;
    uint32_t area_remain = 0;
    uint16_t buf_index;
    
    area_size = (xe - xs + 1) * (ye - ys + 1);
    if (area_size > ATK_MD0130_LCD_BUF_SIZE)
    {
        area_remain = area_size - ATK_MD0130_LCD_BUF_SIZE;
        area_size = ATK_MD0130_LCD_BUF_SIZE;
    }
    st7789_set_address(xs, ys, xe, ye);
    ATK_MD0130_WR(1);
	
	hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
	
	HAL_SPI_Init(&hspi2);
	
    while (1)
    {
        for (buf_index=0; buf_index < area_size; buf_index++)
        {
            g_st7789_lcd_buf[buf_index] = *(color++);	
        } 
		
		ucStatues = 0;
		HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *)g_st7789_lcd_buf, area_size);
		while(ucStatues == 0){};

        if (area_remain == 0)
        {
            break;
        }
        
        if (area_remain > ATK_MD0130_LCD_BUF_SIZE)
        {
            area_remain = area_remain - ATK_MD0130_LCD_BUF_SIZE;
        }
        else
        {
            area_size = area_remain;
            area_remain = 0;
        }
    }
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&hspi2);
}

