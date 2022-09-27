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
File        : GUIConf.h
Purpose     : Configures emWins abilities, fonts etc.
----------------------------------------------------------------------
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
 
#ifndef GUICONF_H
#define GUICONF_H

/*********************************************************************
*
*       Multi layer/display support
*/
#define GUI_NUM_LAYERS            2    // Maximum number of available layers

/*********************************************************************
*
*       Multi tasking support
*/
 #define GUI_OS                    (0)


/*********************************************************************
*
*       Configuration of touch support
*/
#define GUI_SUPPORT_TOUCH       (1)  // Support touchscreen
#define USE_GT911_CTP 	 0
#define USE_MXT224_CTP 	 0
#define USE_RTP          0
#define USE_CTP          0
#define New_CTP 				 0
#define use_XPT2046      1


#define TK020F9168       0
#define TFT1P1061        0
#define TK043F1508       0
#define TK022RB417       0

#define USE_16bit_LCD    0
#define USE_Software_Reset_LCD    0  //是否需要软件复位；用硬件复位的LCD不需要初始化IO来复位它
#define LCD_MODE_MCU_or_RGB       0  //MCU mode=0 ;RGB mode=1;
#define LCD_RGB_ORIENTATION       1  //ORIENTATION=1旋转90度   or normal=0 


/*********************************************************************
*
*       Default font
*/
#define GUI_DEFAULT_FONT          &GUI_Font6x8
#define GUI_USE_ARGB                   (1)
#define GUI_SUPPORT_BIDI     0
/*********************************************************************
*
*         Configuration of available packages
*/
#define GUI_SUPPORT_MOUSE             (1)    /* Support a mouse */
#define GUI_WINSUPPORT                (1)    /* Use window manager */
#define GUI_SUPPORT_MEMDEV            (1)    /* Memory device package available */
#define GUI_SUPPORT_DEVICES           (1)    /* Enable use of device pointers */
#define GUI_ALLOC_SIZE            1024*10
#endif  // Avoid multiple inclusion

// 物理显示尺寸定义

#define XSIZE_PHYS 800
#define YSIZE_PHYS 480
#if GUI_SUPPORT_TOUCH
		// Touch screen
		//触摸屏校验值
		//==============RTP 电阻触摸==============//
//		#if USE_RTP 
//		#define TOUCH_X_MIN 460
//		#define TOUCH_X_MAX 3900
//		#define TOUCH_Y_MIN 500
//		#define TOUCH_Y_MAX 3750
//		#endif

		#if USE_RTP 
		#define TOUCH_X_MIN 380
		#define TOUCH_X_MAX 4020
		#define TOUCH_Y_MIN 550
		#define TOUCH_Y_MAX 3850
		#endif

		#if use_XPT2046 
		#define TOUCH_X_MIN 3900
		#define TOUCH_X_MAX 150
		#define TOUCH_Y_MIN 230
		#define TOUCH_Y_MAX 3850
		#endif


		//==============CTP 电容触摸==============//
		#if USE_GT911_CTP
		#define TOUCH_X_MIN 1
		#define TOUCH_X_MAX 1024
		#define TOUCH_Y_MIN 600
		#define TOUCH_Y_MAX 1
		#endif
		
		#if USE_MXT224_CTP | New_CTP | USE_CTP
			#define TOUCH_X_MIN 1
			#define TOUCH_X_MAX 800
			#define TOUCH_Y_MIN 480
			#define TOUCH_Y_MAX 1
		#endif
#endif
/*************************** End of file ****************************/

 

