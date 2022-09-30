#include <DFRobot_ZXW.h>

DFRobot_ZXW::DFRobot_ZXW(uint8_t mode)
:_mode(mode)
{
	
}

DFRobot_ZXW_IIC::DFRobot_ZXW_IIC(TwoWire *pWire,uint8_t mode)
:DFRobot_ZXW(mode)
{
	_deviceADDR = DFRobot_Sensor_IIC_ADDR;
	_pWire=pWire;
}

DFRobot_ZXW_SPI::DFRobot_ZXW_SPI(SPIClass *pSpi,uint8_t csPin=4,uint8_t mode)
:DFRobot_ZXW(mode)
{
	_pSpi = pSpi;
	_csPin = csPin;
}

int DFRobot_ZXW::begin(void)
{
	uint8_t id=0xDF;
	uint8_t buf;
	if(readReg(SENSOR_ADDR_ID,&buf,1)==0)
	{
		DBG("bus data access error");
		return ERR_DATA_BUS;
	}
	DBG("real sensor id=");
	DBG(id);
	if(id != DFRobot_Sensor_ID)
	{
		return ERR_IC_VERSION;
	}
	write(SENSOR_ADDR_CONFIG,&_mode,1);
	DBG("begin ok!");
	return ERR_OK;
}

int DFRobot_ZXW_IIC::begin(void)
{
	Wire.begin();
	return DFRobot_ZXW::begin();
}

int DFRobot_ZXW_SPI::begin(void)
{
	pinMode(_csPin,OUTPUT);//==========================
	_pSpi->begin();
	return DFRobot_ZXW::begin();
}

void DFRobot_ZXW_IIC::writeReg(uint8_t reg,void* pBuf,size_t size)
{
	if(pBuf == NULL)
	{
		DBG("pBuf ERROR = NULL");
	}
	uint8_t* _pBuf = (uint8_t*)pBuf;
	_pWire->beginTransmission(_deviceADDR);
	for(uint16_t i=0;i<size;i++)
	{
		_pWire->write(_pBuf[i]);
	}
	_pWire->endTransmission();
}

uint8_t DFRobot_ZXW_IIC::readReg(uint8_t reg,void* pBuf,size_t size)
{
	if(pBuf == BULL)
	{
		DBG("pBuf ERROR = NULL");
	}
	uint8_t * _pBuf = (uint8_t*)pBuf;
	_pWire->beginTransmission(_deviceADDR);//使用指定的地址开始向I2C从设备进行传输。
	if(_pWire->endTransmission()!=0)//用到了 Wire.endTransmission()，结束一个由beginTransmission（）
									//开始的并且由write（）排列的从机的传输。返回0 成功 1 数据溢出 2 发送错误或其他错误
	{
		return 0;
	}//控制器设备使用此函数从外围设备请求字节
	_pWire->requestFrom(_deviceADDR,(uint8_t)size);//主设备请求从设备一个字节，这个字节可以被主设备用
	for(uint16_t i=0;i<size;i++)
	{
		_pBuf[i] = _pWire->read();
	}
	_pWire->endTransmission();
	return size;
}

void DFRobot_ZXW_SPI::writeReg(uint8_t reg,void* pBuf,size_t size)
{
	if(pBuf == NULL)
	{
		DBG("pBuf ERROR = NULL");
	}
	uint8_t* _pBuf = (uint8_t)pBuf;
	//==========================================
	_pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE));
	_pSpi->transfer(reg);
	while(size--)
	{
		_pSpi->transfer(*_pBuf);
		_pBuf ++;
	}
	digitalWrite(_csPin,1);
	_pSpi->endTransaction();
}

void DFRobot_ZXW_SPI::readReg(uint8_t reg,void* pBuf,size_t size)
{
	if(pBuf == BULL)
	{
		DBG("pBuf ERROR = NULL");
	}
	size_t count = 0;
	uint8_t* _pBuf = (uint8_t)pBuf;
	//==========================================
	_pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
	_pSpi->transfer(reg);
	while(size--)
	{
		*_pBuf = SPI.transfer(0x00);
		_pBuf ++;
		count++;
	}
	digitalWrite(_csPin,1);
	_pSpi->endTransaction();
	return count;
}

uint16_t DFRobot_ZXW::soundStrengthDB(void)
{
	//sData_t data;
	uint8_t data;
	readReg(SENSOR_ADDR_DATA,&data,sizeof(data));
	DBG("sound is");
	DBG(data.sound);
	return (data>>4)<<3;
}

uint16_t DFRobot_ZXW::lightStrengthLux(void)
{
	//sData_t data;
	uint8_t data;
	readReg(SENSOR_ADDR_DATA,&data,sizeof(data));
	DBG("light is");
	DBG(data.light);
	data&0x0f;
	return data.light*10000;
}

uint16_t DFRobot_ZXW::switchMode(uint8_t mode)
{
	uint8_t temp;
	#ifdef ENABLE_DBG
	readReg(SENSOR_ADDR_CONFIG,&temp,sizeof(temp));
	DBG("before switch mode = ");
	DBG(mode);
	#endif
	writeReg(SENSOR_ADDR_CONFIG,&mode,sizeof(mode));
	#ifdef ENABLE_DBG
	readReg(SENSOR_ADDR_CONFIG,&temp,sizeof(temp));
	DBG("after switch mode = ");
	#endif
}

void DFRobot_ZXW::setLED(uint8_t r,uint8_t g,uint8_t b)
{
	sColor_t data={.b=b>>3,.g=g>>2,.r=r>>3};
	writeReg(SENSOR_ADDR_LED,&data,sizeof(data));
}

void DFRobot_ZXW::setLED(uint16_t color)
{
	
	writeReg(SENSOR_ADDR_LED,&color,2);
}