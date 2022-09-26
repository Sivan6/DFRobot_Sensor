# DFRobot_Sensor
这是一个实习生培训用最简单的的Arduino的库
这里需要显示拍照图片，可以一张图片，可以多张图片（不要用SVG图）

如果以后有事物就在数据手册上抄一下芯片的描述
这里写模块介绍，做到读完这段，就能对模块有初步了解，让客户懂的用这个模块能干什么（数据手册通常比较官方，这里你可以举例子，更场景化）<br>
这个模块的优点，告诉用户为什么要购买这个模块
这里需要显示拍照图片，可以一张图片，可以多张图片（不要用SVG图）

![正反面svg效果图](https://github.com/ouki-wang/DFRobot_Sensor/raw/master/resources/images/SEN0245svg1.png)


## 产品链接（链接到英文商城）
    SKU：产品名称
   
## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary

这个库具备设置名字，设置年龄，读取名字，读取年龄功能

## Installation

To use this library, first download the library file, paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
   /**
    * @brief 构造函数
    * @param 可以对其进行重写
    */
    DFRobot_ZXW();
    /**
    * @brief 析构函数
    * @param 在程序销毁是执行
    */
    ~DFRobot_ZXW();
    /**
    * @brief 赋值姓名函数
    * @return 返回0表示初始化成功，返回-1表示失败
    */
    int setName(const char * name);
    /**
    * @brief 赋值年龄函数
    * @param 返回0表示初始化成功，返回-1表示失败
    */
    int setAge(uint8_t age);
    /**
    * @brief 赋值年龄函数
    * @param 字符串类型的赋值
    */
    int setAge(String age);
    /**
    * @brief 取值函数
    * @param 取到你赋值姓名的函数
    */
    String getName(void);
    /**
    * @brief 取值函数
    * @param 取到你赋值年龄的函数
    */
    uint8_t getAge(void);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino uno        |      √       |              |             | 
Mega2560       	   |      √       |              |             | 
Leonardo       	   |      √       |              |             | 
mPython/ESP32      |      √       |              |             | 
micro:bit          |      √       |              |             | 


## History

- data 2019-7-28
- version V0.1


## Credits

Written by Alexander(ouki.wang@dfrobot.com), 2019. (Welcome to our [website](https://www.dfrobot.com/))





