#include <DFRobot_ZXW.h>
#include <string.h>

DFRobot_ZXW::DFRobot_ZXW(){	//构造函数的重写
	Serial.println("hello DFRobot!!!");
}
DFRobot_ZXW::~DFRobot_ZXW(){	//虚构函数的重写
	Serial.println("byebye DFRobot");
}
//设置姓名函数
int DFRobot_ZXW::setName(const char *name)
{
	if(strlen(name)<20)
	{
		_name=name;
		return 0;
	}
	return -1;
}
//设置年龄函数（输入整数类型）
int DFRobot_ZXW::setAge(uint8_t age)
{
	if((age>18)||(age<100))
	{
		_age=age;
		return 0;
	}
	return -1;
}
//设置姓名函数（输入字符串类型）
int DFRobot_ZXW::setAge(String age)
{
	int tem = age.toInt();//字符串转整形函数
	if((tem>18)||(tem<100))
	{
		_age=tem;
		return 1;
	}
	return 0;
}
//得到姓名函数
String DFRobot_ZXW::getName(void)
{
	return _name;
}
//得到年龄函数
uint8_t DFRobot_ZXW::getAge(void)
{
	return _age;
}

