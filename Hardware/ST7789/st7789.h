#ifndef __ST7789_H
#define __ST7789_H

#include "main.h"

#define USE_HORIZONTAL	2

#if (USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1)
/* 定义ATK-MD0130模块LCD尺寸 */
#define ATK_MD0130_LCD_WIDTH                240
#define ATK_MD0130_LCD_HEIGHT               135
#else
#define ATK_MD0130_LCD_WIDTH                240
#define ATK_MD0130_LCD_HEIGHT               135
#endif


/* IO操作 */
#define ATK_MD0130_PWR(x)                   do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(IPS_BK_GPIO_Port, IPS_BK_Pin, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(IPS_BK_GPIO_Port, IPS_BK_Pin, GPIO_PIN_RESET);   \
                                            }while(0)
#define ATK_MD0130_CS(x)                    do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(IPS_CS_GPIO_Port, IPS_CS_Pin, GPIO_PIN_SET) :      \
                                                HAL_GPIO_WritePin(IPS_CS_GPIO_Port, IPS_CS_Pin, GPIO_PIN_RESET);     \
                                            }while(0)
#define ATK_MD0130_WR(x)                    do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(IPS_DC_GPIO_Port, IPS_DC_Pin, GPIO_PIN_SET) :      \
                                                HAL_GPIO_WritePin(IPS_DC_GPIO_Port, IPS_DC_Pin, GPIO_PIN_RESET);     \
                                            }while(0)
#define ATK_MD0130_RST(x)                   do{ x ?                                                                                     \
                                                HAL_GPIO_WritePin(IPS_RST_GPIO_Port, IPS_RST_Pin, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(IPS_RST_GPIO_Port, IPS_RST_Pin, GPIO_PIN_RESET);   \
                                            }while(0)


/* 操作函数 */
void st7789_init(void);                                                                                                                             /* ATK-MD0130模块初始化 */
void st7789_display_on(void);                                                                                                                       /* 开启ATK-MD0130模块LCD背光 */
void st7789_display_off(void);                                                                                                                      /* 关闭ATK-MD0130模块LCD背光 */
void st7789_fill_block(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye, uint16_t *color);

#endif
