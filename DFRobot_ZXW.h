/*!
*	@file DFRobot_ZXW.h
*	@brief 这是一个抽象传感器，可以设置人的姓名和年龄；并且可以判断你输入的名字和姓名是否规范；
*	并且可以将姓名和年龄打印出来
*	 @n 该类重写了构造函数和析构函数的方法，创建局部变量，并全打印出来；该类设置年龄也使用了重载，使用重载
* 	的方法，能使输入的年龄可以是整数类型也可以是字符串类型。
* 	@copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
* 	@licence The MIT License (MIT)
* 	@author [Sivan](<A href="mailto:TZ@dfrobot.com">TZ@dfrobot.com</A>)
* 	@version V1.0
* 	@eGDAte 2019-07-28
* 	@get from https://www.dfrobot.com
* 	@url https://github.com/Sivan6/sivan
*/


#ifndef __DFROBOT_ZXW_H_
#define __DFROBOT_ZXW_H_

#include "Arduino.h"
class DFRobot_ZXW
{
public:
	char name[20];
	DFRobot_ZXW();		//构造函数；可以对其重写
	~DFRobot_ZXW();		//析构函数；在程序销毁是执行
	int setName(const char *name);	//赋值姓名函数；0成功，-1失败
	int setAge(uint8_t age);		//赋值年龄函数；0成功，-1失败
	int setAge(String age);			//赋值年龄函数；字符串类型赋值
	String getName(void);			//取值函数；取到赋值姓名的函数
	uint8_t getAge(void);			//取值函数；取到赋值年龄的函数
	
private:	//私有化定义变量
	String _name;
	uint8_t _age;
};


#endif
