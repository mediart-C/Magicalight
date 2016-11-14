// -*- C++ -*-
/*!
 * @file  AnalogInput.cpp
 * @brief Receive analog input from sensor and send that.
 * @date $Date$
 *
 * @author Shintaro Nakazawa
 * cy14143@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "AnalogInput.h"

// Module specification
// <rtc-template block="module_spec">
static const char* analoginput_spec[] =
  {
    "implementation_id", "AnalogInput",
    "type_name",         "AnalogInput",
    "description",       "Receive analog input from sensor and send that.",
    "version",           "1.0.0",
    "vendor",            "ShintaroNakazawa",
    "category",          "RaspberryPi",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AnalogInput::AnalogInput(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_OutDataOut("OutData", m_OutData)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
AnalogInput::~AnalogInput()
{
}



RTC::ReturnCode_t AnalogInput::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("OutData", m_OutDataOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AnalogInput::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * SPI通信を行うためにADCの設定を行います．今回はmcp3002という型番
 * のADCを使用するので，関数mcp3002Setupを呼び出します．
 */

RTC::ReturnCode_t AnalogInput::onActivated(RTC::UniqueId ec_id)
{
	if (mcp3002Setup(PINBASE + ANALOG_CHANNEL, SPI_CHANNEL)){
		std::cout << "mpc3002Setup faild" << std::endl;
	}
  return RTC::RTC_OK;
}

/*!
 * Deactivate時に行う処理は特にありません．
 */

RTC::ReturnCode_t AnalogInput::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * センサから受け取ったデータを外部へ出力します．
 */

RTC::ReturnCode_t AnalogInput::onExecute(RTC::UniqueId ec_id)
{
	double value;

	//SPI通信を行い，センサからのデータを取得します．
	value = analogRead(PINBASE + SPI_CHANNEL);
	std::cout << "RawData = " << value << std::endl;

	//出力
	m_OutData.data = value;
	m_OutDataOut.write();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AnalogInput::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AnalogInput::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AnalogInputInit(RTC::Manager* manager)
  {
    coil::Properties profile(analoginput_spec);
    manager->registerFactory(profile,
                             RTC::Create<AnalogInput>,
                             RTC::Delete<AnalogInput>);
  }
  
};


