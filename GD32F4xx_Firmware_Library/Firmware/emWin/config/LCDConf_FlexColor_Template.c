/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2017  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.44 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *                      http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// 色彩转换
//
#define COLOR_CONVERSION GUICC_8888

//
// 显示驱动
//
#if LCD_MODE_MCU_or_RGB
	#define DISPLAY_DRIVER      &GUIDRV_Lin_OSX_32_API//   GUIDRV_Lin_32_API
#else
	#define DISPLAY_DRIVER &GUIDRV_Template_API  //GUIDRV_Lin_32_API  GUIDRV_Lin_OSX_32_API 
#endif

//
// 缓存 / 虚拟屏幕
//
#define NUM_BUFFERS   1
#define NUM_VSCREENS  1
/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif
#ifndef   NUM_VSCREENS
  #define NUM_VSCREENS 1
#else
  #if (NUM_VSCREENS <= 0)
    #error At least one screeen needs to be defined!
  #endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
  #error Virtual screens and multiple buffers are not allowed!
#endif
#ifndef   DISPLAY_ORIENTATION
  #define DISPLAY_ORIENTATION  0
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
#define LANDSCAPE   1
#else
#define LANDSCAPE   0
#endif

#if (LANDSCAPE == 1)
#define WIDTH       YSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      XSIZE_PHYS  /* Screen Hight (in pixels)         */
#else
#define WIDTH       XSIZE_PHYS  /* Screen Width (in pixels)         */
#define HEIGHT      YSIZE_PHYS  /* Screen Hight (in pixels)         */
#endif

#if ((DISPLAY_ORIENTATION & GUI_SWAP_XY) != 0)
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_TOP    TOUCH_X_MAX
    #define TOUCH_BOTTOM TOUCH_X_MIN
  #else
    #define TOUCH_TOP    TOUCH_X_MIN
    #define TOUCH_BOTTOM TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_LEFT   TOUCH_Y_MAX
    #define TOUCH_RIGHT  TOUCH_Y_MIN
  #else
    #define TOUCH_LEFT   TOUCH_Y_MIN
    #define TOUCH_RIGHT  TOUCH_Y_MAX
  #endif
#else
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_X) != 0)
    #define TOUCH_LEFT   TOUCH_X_MAX
    #define TOUCH_RIGHT  TOUCH_X_MIN
  #else
    #define TOUCH_LEFT   TOUCH_X_MIN
    #define TOUCH_RIGHT  TOUCH_X_MAX
  #endif
  #if ((DISPLAY_ORIENTATION & GUI_MIRROR_Y) != 0)
    #define TOUCH_TOP    TOUCH_Y_MAX
    #define TOUCH_BOTTOM TOUCH_Y_MIN
  #else
    #define TOUCH_TOP    TOUCH_Y_MIN
    #define TOUCH_BOTTOM TOUCH_Y_MAX
  #endif
#endif




/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
//void LCD_init_code(void)//液晶屏初始化代码
//{
//	int i;
//	//=================== TK043F1168 ===================//
//	WriteComm(0x2D); 
//        for (i=0; i<=63; i++)
//        {
//        WriteData(i*8);   
//        }
//
//        for (i=0; i<=63; i++)
//        {
//        WriteData(i*4);   
//        }
//
//        for (i=0; i<=63; i++)
//        {
//        WriteData(i*8);   
//        }
// 
//
//        WriteComm(0xB9); //Set_EXTC
//        WriteData(0xFF);
//        WriteData(0x83);
//        WriteData(0x69);
//
//
//
//        WriteComm(0xB1);  //Set Power 
//        WriteData(0x85);
//	WriteData(0x00);
//	WriteData(0x34);
//	WriteData(0x0A);
//	WriteData(0x00);
//	WriteData(0x0F);
//	WriteData(0x0F);
//	WriteData(0x2A);
//	WriteData(0x32);
//	WriteData(0x3F);
//	WriteData(0x3F);
//	WriteData(0x01); //update VBIAS
//	WriteData(0x23);
//	WriteData(0x01);
//	WriteData(0xE6);
//	WriteData(0xE6);
//	WriteData(0xE6);
//	WriteData(0xE6);
//	WriteData(0xE6);
//
//        WriteComm(0xB2); // SET Display 480x800
//        WriteData(0x00);
//        WriteData(0x20);
//        WriteData(0x0A);
//        WriteData(0x0A);
//        WriteData(0x70);
//        WriteData(0x00);
//        WriteData(0xFF);
//        WriteData(0x00);
//        WriteData(0x00);
//        WriteData(0x00);
//        WriteData(0x00);
//        WriteData(0x03);
//        WriteData(0x03);
//        WriteData(0x00);
//        WriteData(0x01);
//
//        WriteComm(0xB4); // SET Display 480x800
//        WriteData(0x00);
//        WriteData(0x18);
//        WriteData(0x80);
//        WriteData(0x10);
//        WriteData(0x01);
//        WriteComm(0xB6); // SET VCOM
//        WriteData(0x2C);
//        WriteData(0x2C);
//
//        WriteComm(0xD5); //SET GIP
//        WriteData(0x00);
//        WriteData(0x05);
//        WriteData(0x03);
//        WriteData(0x00);
//        WriteData(0x01);
//        WriteData(0x09);
//        WriteData(0x10);
//        WriteData(0x80);
//        WriteData(0x37);
//        WriteData(0x37);
//        WriteData(0x20);
//        WriteData(0x31);
//        WriteData(0x46);
//        WriteData(0x8A);
//        WriteData(0x57);
//        WriteData(0x9B);
//        WriteData(0x20);
//        WriteData(0x31);
//        WriteData(0x46);
//        WriteData(0x8A);
//        WriteData(0x57);
//        WriteData(0x9B);
//        WriteData(0x07);
//        WriteData(0x0F);
//        WriteData(0x02);
//        WriteData(0x00);
//        WriteComm(0xE0); //SET GAMMA
//        WriteData(0x00);
//        WriteData(0x08);
//        WriteData(0x0D);
//        WriteData(0x2D);
//        WriteData(0x34);
//        WriteData(0x3F);
//        WriteData(0x19);
//        WriteData(0x38);
//        WriteData(0x09);
//        WriteData(0x0E);
//        WriteData(0x0E);
//        WriteData(0x12);
//        WriteData(0x14);
//        WriteData(0x12);
//        WriteData(0x14);
//        WriteData(0x13);
//        WriteData(0x19);
//        WriteData(0x00);
//        WriteData(0x08);
//
//        WriteData(0x0D);
//        WriteData(0x2D);
//        WriteData(0x34);
//        WriteData(0x3F);
//        WriteData(0x19);
//        WriteData(0x38);
//        WriteData(0x09);
//        WriteData(0x0E);
//        WriteData(0x0E);
//        WriteData(0x12);
//        WriteData(0x14);
//        WriteData(0x12);
//        WriteData(0x14);
//        WriteData(0x13);
//        WriteData(0x19);
//        WriteComm(0xC1); //set DGC
//        WriteData(0x01); //enable DGC function
//        WriteData(0x02); //SET R-GAMMA
//        WriteData(0x08);
//        WriteData(0x12);
//        WriteData(0x1A);
//        WriteData(0x22);
//        WriteData(0x2A);
//        WriteData(0x31);
//        WriteData(0x36);
//        WriteData(0x3F);
//        WriteData(0x48);
//        WriteData(0x51);
//        WriteData(0x58);
//        WriteData(0x60);
//        WriteData(0x68);
//        WriteData(0x70);
//        WriteData(0x78);
//        WriteData(0x80);
//        WriteData(0x88);
//        WriteData(0x90);
//        WriteData(0x98);
//        WriteData(0xA0);
//        WriteData(0xA7);
//        WriteData(0xAF);
//        WriteData(0xB6);
//        WriteData(0xBE);
//        WriteData(0xC7);
//        WriteData(0xCE);
//        WriteData(0xD6);
//        WriteData(0xDE);
//        WriteData(0xE6);
//        WriteData(0xEF);
//        WriteData(0xF5);
//        WriteData(0xFB);
//        WriteData(0xFC);
//        WriteData(0xFE);
//        WriteData(0x8C);
//        WriteData(0xA4);
//        WriteData(0x19);
//        WriteData(0xEC);
//        WriteData(0x1B);
//        WriteData(0x4C);
//
//        WriteData(0x40);
//        WriteData(0x02); //SET G-Gamma
//        WriteData(0x08);
//        WriteData(0x12);
//        WriteData(0x1A);
//        WriteData(0x22);
//        WriteData(0x2A);
//        WriteData(0x31);
//        WriteData(0x36);
//        WriteData(0x3F);
//        WriteData(0x48);
//        WriteData(0x51);
//        WriteData(0x58);
//        WriteData(0x60);
//        WriteData(0x68);
//        WriteData(0x70);
//        WriteData(0x78);
//        WriteData(0x80);
//        WriteData(0x88);
//        WriteData(0x90);
//        WriteData(0x98);
//        WriteData(0xA0);
//        WriteData(0xA7);
//        WriteData(0xAF);
//        WriteData(0xB6);
//        WriteData(0xBE);
//        WriteData(0xC7);
//        WriteData(0xCE);
//        WriteData(0xD6);
//        WriteData(0xDE);
//        WriteData(0xE6);
//        WriteData(0xEF);
//        WriteData(0xF5);
//        WriteData(0xFB);
//        WriteData(0xFC);
//        WriteData(0xFE);
//        WriteData(0x8C);
//        WriteData(0xA4);
//        WriteData(0x19);
//        WriteData(0xEC);
//        WriteData(0x1B);
//        WriteData(0x4C);
//        WriteData(0x40);
//        WriteData(0x02); //SET B-Gamma
//        WriteData(0x08);
//        WriteData(0x12);
//        WriteData(0x1A);
//        WriteData(0x22);
//        WriteData(0x2A);
//        WriteData(0x31);
//        WriteData(0x36);
//        WriteData(0x3F);
//        WriteData(0x48);
//        WriteData(0x51);
//        WriteData(0x58);
//        WriteData(0x60);
//        WriteData(0x68);
//        WriteData(0x70);
//        WriteData(0x78);
//
//        WriteData(0x80);
//        WriteData(0x88);
//        WriteData(0x90);
//        WriteData(0x98);
//        WriteData(0xA0);
//        WriteData(0xA7);
//        WriteData(0xAF);
//        WriteData(0xB6);
//        WriteData(0xBE);
//        WriteData(0xC7);
//        WriteData(0xCE);
//        WriteData(0xD6);
//        WriteData(0xDE);
//        WriteData(0xE6);
//        WriteData(0xEF);
//        WriteData(0xF5);
//        WriteData(0xFB);
//        WriteData(0xFC);
//        WriteData(0xFE);
//        WriteData(0x8C);
//        WriteData(0xA4);
//        WriteData(0x19);
//        WriteData(0xEC);
//        WriteData(0x1B);
//        WriteData(0x4C);
//        WriteData(0x40);
//        WriteComm(0x3A); //Set COLMOD
//        WriteData(0x55);
//        WriteComm(0x11); //Sleep Out
//        LCD_delay(120);
//        WriteComm(0x29); //Display On
//                        
//        LCD_delay(100);
//        WriteComm(0x3A); //pixel format setting
//        WriteData(0x77); 
//        WriteComm(0x36); //pixel format setting
//        WriteData(0x68); //B,G,R
//}
//}

//void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend) 
//{
//	WriteComm(0x2a);
//	WriteData(Xstart>>8);
//	WriteData(Xstart);
//	WriteData(Xend>>8);
//	WriteData(Xend);
//
//	WriteComm(0x2b);   
//	WriteData(Ystart>>8);
//	WriteData(Ystart);
//	WriteData(Yend>>8);
//	WriteData(Yend);
//	
//	WriteComm(0x2c);
//}

//void LCD_DrawLineH(int x0, int x1,  int y, int LCD_COLORINDEX)
//{
//	BlockWrite(x0,x1,y,y);
//	TK80->CFGR3=x1-x0+1;
//		TK80->DINR = LCD_COLORINDEX;
//	while(TK80->SR & 0x10000);
//}

//void LCD_DrawLineV(int x, int y0,  int y1, int LCD_COLORINDEX)
//{	
//	BlockWrite(x,x,y0,y1);
//	TK80->CFGR3=y1-y0+1;
//		TK80->DINR = LCD_COLORINDEX;
//	while(TK80->SR & 0x10000);
//}

/*
*********************************************************************************************************
*	函 数 名: DrawHColorLine
*	功能说明: 绘制一条彩色水平线 （主要用于UCGUI的接口函数）
*	形    参：_usX1    ：起始点X坐标
*			  _usY1    ：水平线的Y坐标
*			  _usWidth ：直线的宽度
*			  _pColor : 颜色缓冲区
*	返 回 值: 无
*********************************************************************************************************
*/
//void LCD_DrawHColorLine(U16 x1 , U16 y1, U16 Width, U32 *_pColor)
//{
//	BlockWrite(x1,x1+Width-1,y1,y1);
//	TK80_DMA_Init((u32)_pColor,Width);
//	y1=x1+Width;
//	for (x1 = 0; x1 < y1; x1++)
//	{
//		TK80->DINR =  *_pColor++;
//	}
//}

//void LCD_PutPixel(U16 x,U16 y,int PixelIndex)
//{
//	BlockWrite(x,x,y,y);
//	TK80->DINR = PixelIndex;
//}

// int  LCD_GetPixel(U16 x,U16 y)
//{
//        int i;
//	WriteComm(0x2a);   
//	WriteData(x>>8);
//	WriteData(x&0xff);
//	WriteData(x>>8);
//	WriteData(x&0xff);
//
//	WriteComm(0x2b);   
//	WriteData(y>>8);
//	WriteData(y&0xff);
//	WriteData(y>>8);
//	WriteData(y&0xff);
////BlockWrite(x,x,y,y);
//	WriteComm(0x2E);while(TK80->SR & 0x10000);
	
//	x = TK80->DOUTR;while(TK80->SR & 0x10000);
//	x = TK80->DOUTR;while(TK80->SR & 0x10000);
//	x = (x&0xf800)|((x&0x00fc)<<3);
//	y = TK80->DOUTR;while(TK80->SR & 0x10000);

//	return x|(y>>11);
//	TK80->CFGR1 = 0x05080505;//把速度调低
//        TK80->CFGR2 = 0x0506;
//	x = TK80->DOUTR;while(TK80->SR & 0x10000);
//	i = TK80->DOUTR;while(TK80->SR & 0x10000);
//	TK80->CFGR1 = 0x00050202;//恢复高速写入速度
//        TK80->CFGR2 = 0x0502;
//	return(i);
//}

/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {

  /* 设置第一层的显示驱动和颜色转换 */
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  /* 公共显示驱动配置 */
  LCD_SetSizeEx(0, YSIZE_PHYS, XSIZE_PHYS);               // 实际显示像素
  
   if (LCD_GetSwapXY()) 
  {
    LCD_SetSizeEx (0, YSIZE_PHYS, XSIZE_PHYS);
    LCD_SetVSizeEx(0, YSIZE_PHYS * NUM_VSCREENS, XSIZE_PHYS);
  } 
  else 
  {
    LCD_SetSizeEx (0, XSIZE_PHYS, YSIZE_PHYS);
    LCD_SetVSizeEx(0, XSIZE_PHYS, YSIZE_PHYS * NUM_VSCREENS);
  }							     

  #if (GUI_SUPPORT_TOUCH == 1)
    /*设置显示方向*/
//    GUI_TOUCH_SetOrientation(GUI_SWAP_XY);//GUI_MIRROR_Y DISPLAY_ORIENTATION
    
    /* 校准触摸屏 */  
    GUI_TOUCH_Calibrate(GUI_COORD_X, 0,  WIDTH  - 1,TOUCH_LEFT,  TOUCH_RIGHT);
    GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, HEIGHT - 1, TOUCH_TOP, TOUCH_BOTTOM);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
    //
    // Called during the initialization process in order to set up the
    // display controller and put it into operation. If the display
    // controller is not initialized by any external routine this needs
    // to be adapted by the customer...
    //
    // ...
    return 0;
  }
  default:
    r = -1;
  }
  return r;
}

/*************************** End of file ****************************/

