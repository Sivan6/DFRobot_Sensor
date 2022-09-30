/*!
 * @file DFRobot_Sensor.h
 * @brief 定义DFRobot_Sensor 类的基础结构
 * @n 这是一个虚拟的传感器，IIC地址不可改变,不对应任何实物，可以通过IIC和SPI口来控制它，假设它有下面这些功能
 * @n 向寄存器0里写入数据，点亮不同颜色的LED灯
 * @n 从寄存器1里读出数据，高四位表示光线强度，低四位表示声音强度
 * @n 从寄存器2 bit0里写入数据，写1表示正常模式，写0表示低功耗模式
 * @n 从寄存器3 读取数据，读到的是芯片版本0xDF
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [ZXW](924063564@qq.com)
 * @version  V1.0
 * @date  2019-07-13
 * @https://github.com/Sivan6/DFRobot_ZXW
 */

#ifndef __DFROBOT_ZXW_H_
#define __DFROBOT_ZXW_H_

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

#define ENABLE_DBG //========================================

#ifdef ENABLE_DBG
	#define DBG(...) {Serial.print(__FUNCTION__);Serial.print("()");Serial.print(__LINE__);Serial.println(__VA_ARGS__);}
#else 
	#define DBG(...)
#endif
#define DFRobot_Sensor_IIC_ADDR 0x66 //芯片IIC地址，无变化地址功能
#define DFRobot_Sensor_ID 0xDF //芯片IIC地址，无变化地址功能

#define SENSOR_ADDR_LED    0 //LED控制地址  这里的描述从芯片手册上抄写
#define SENSOR_ADDR_DATA   2 //组合数据地址  这里的描述从芯片手册上抄写
#define SENSOR_ADDR_CONFIG 3 //配置寄存器地址 这里的描述从芯片手册上抄写
#define SENSOR_ADDR_ID     4 //芯片ID寄存器地址 这里的描述从芯片手册上抄写

#define  COLOR_RGB565_BLACK     0x0000      // 黑色    
#define  COLOR_RGB565_NAVY      0x000F      // 深蓝色  
#define  COLOR_RGB565_DGREEN    0x03E0      // 深绿色  
#define  COLOR_RGB565_DCYAN     0x03EF      // 深青色  
#define  COLOR_RGB565_PURPLE    0x780F      // 紫色  
#define  COLOR_RGB565_MAROON    0x7800      // 深红色      
#define  COLOR_RGB565_OLIVE     0x7BE0      // 橄榄绿      
#define  COLOR_RGB565_LGRAY     0xC618      // 灰白色
#define  COLOR_RGB565_DGRAY     0x7BEF      // 深灰色      
#define  COLOR_RGB565_BLUE      0x001F      // 蓝色    
#define  COLOR_RGB565_GREEN     0x07E0      // 绿色          
#define  COLOR_RGB565_CYAN      0x07FF      // 青色  
#define  COLOR_RGB565_RED       0xF800      // 红色       
#define  COLOR_RGB565_MAGENTA   0xF81F      // 品红    
#define  COLOR_RGB565_YELLOW    0xFFE0      // 黄色        
#define  COLOR_RGB565_WHITE     0xFFFF      // 白色  

class DFRobot_ZXW
{
public:
	#define ERR_OK 0
	#define ERR_DATA_BUS -1
	#define ERR_IC_VERSION -2
	
	typedef struct
	{
		uint8_t r:5;
		uint8_t g:6;
		uint8_t b:5;	
	}__attribute__((packed)) sColor_t;
	
	typedef struct
	{
		uint8_t light:4;
		uint8_t sound:4;
	}__attribute__((packed)) sData_t;
	 /*
   这里从数据手册上抄写关于这个寄存器的描述
     * -----------------------------------------------------------------------------------------
     * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2   |    b1     |    b0    |
     * -----------------------------------------------------------------------------------------
     * |   ready  |         reversed               |      precision     | highspeed | lowpower |
     * -----------------------------------------------------------------------------------------
     *
     *上电后，ready位默认为1，不可更改
  */
  typedef struct {
    uint8_t   lowpower: 1; /*!< 上电为0，1：低功耗模式 0：正常功耗模式 */
    uint8_t   highspeed: 1; /*!< 上电为0，1：告诉模式 0：正常速度模式 */
    uint8_t   precision: 2; /*!< 上电为0，0：低精度模式，1：正常精度模式，2：高精度模式，3：超高精度模式 */
    uint8_t   reserved: 3; /*!< 上电为0，1：低功耗模式 0：正常功耗模式 */
    uint8_t   ready:1; /*!< 上电为0，1：低功耗模式 0：正常功耗模式 */
  } __attribute__ ((packed)) sMode_t;
  
	typedef enum
	{
		eNormalPower = 0,
		eLowPower = 1,	
	}ePowerMode_t;
	
	typedef enum
	{
		eNormalSpeed = 0<<1,
		eHighSpeed = 1<<1,
	}eSpeedMode_t;
	
	typedef enum
	{
		eLowPrecision = 0<<2,
		eNormalPrecision = 1<<2,
		eHighPrecision = 2<<2,
		eUltraPrecision = 3<<2,
	}ePrecisionMode_t;
	
public:
	DFRobot_ZXW(uint8_t mode);
	virtual int begin(void);//=====
	uint16_t soundStrengthDB(void);
	uint16_t lightStrengthLux(void);
	uint16_t switchMode(uint8_t mode);
	void setLED(uint8_t r,uint8_t g,uint8_t b);
	void setLED(uint16_t color);
protected:
	virtual uint8_t readReg(uint8_t reg,void* pBuf,size_t size)=0;
	virtual void writeReg(uint8_t reg,void* pBuf,size_t size)=0;
private:
	uint8_t _r,_g,_b;
	uint8_t _mode;
};

class DFRobot_ZXW_IIC:public DFRobot_ZXW
{
public:
	DFRobot_ZXW_IIC(TwoWire *pWire=&Wire,uint8_t mode=eNormalPrecision+eNormalSpeed+eNormalPower);
	virtual int begin(void);
protected:
	virtual uint8_t readReg(uint8_t reg,void* pBuf,size_t size);
	virtual void writeReg(uint8_t reg,void* pBuf,size_t size);
private:
	TwoWire *_pWire;
	uint8_t _deviceADDR;
};

class DFRobot_ZXW_SPI:public DFRobot_ZXW
{
public:
	DFRobot_ZXW_SPI(SPIClass *pSpi=&SPI,uint8_t csPin=4,uint8_t mode=eNormalPrecision+eNormalSpeed+eNormalPower);
	virtual int begin(void);
protected:
	virtual uint8_t readReg(uint8_t reg,void* pBuf,size_t size);
	virtual void writeReg(uint8_t reg,void* pBuf,size_t size);
private:
	SPIClass *_pSpi;
	uint8_t _csPin;
};



#endif
