#include <DFRobot_ZXW.h>//引入头文件

void setup(void){
  Serial.begin(115200);  //初始化串口
  delay(100);
  DFRobot_ZXW zt;         //建立对象
  zt.setName("zhangsan");zt.setAge(18);//进行赋值
  Serial.print("name=");Serial.println(zt.getName()); //打印和取值
  Serial.print("age=");Serial.println(zt.getAge());
}

void loop(void){
  
}
