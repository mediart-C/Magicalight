// -*- C++ -*-
/*!
 * @file  PWMFluctuations.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * @author Shintaro Nakazawa
 * cy14143@shibaura-it.ac.jp
 * Daichi Katagiri
 * cy14119@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "PWMFluctuations.h"

// Module specification
// <rtc-template block="module_spec">
static const char* pwmfluctuations_spec[] =
  {
    "implementation_id", "PWMFluctuations",
    "type_name",         "PWMFluctuations",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Shintaro Nakazawa, Daichi Katagiri",
    "category",          "RaspberryPi",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Mode", "1",
    "conf.default.MaxBrightness", "80",
    "conf.default.MinBrightness", "30",
    "conf.default.Rate", "500",
    // Widget
    "conf.__widget__.Mode", "text",
    "conf.__widget__.MaxBrightness", "text",
    "conf.__widget__.MinBrightness", "text",
    "conf.__widget__.Rate", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PWMFluctuations::PWMFluctuations(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inSWIn("inSW", m_inSW)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PWMFluctuations::~PWMFluctuations()
{
}



RTC::ReturnCode_t PWMFluctuations::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("inSW", m_inSWIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Mode", m_Mode, "1");
  bindParameter("MaxBrightness", m_MaxBrightness, "80");
  bindParameter("MinBrightness", m_MinBrightness, "30");
  bindParameter("Rate", m_Rate, "500");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PWMFluctuations::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * wiringPiのセットアップを行います．
 */

RTC::ReturnCode_t PWMFluctuations::onActivated(RTC::UniqueId ec_id)
{
	//WiringPiのセットアップ
	int w = wiringPiSetupGpio();
	std::cout << "Setup:" << w << std::endl;
	std::cout << "PWMFluctuations Start" << std::endl;

	//使用するportの初期化
	pinMode(PIN, OUTPUT);
	digitalWrite(PIN, 0);

  return RTC::RTC_OK;
}

/*!
 * DeactivatedされたらLEDをオフにします。．
 */

RTC::ReturnCode_t PWMFluctuations::onDeactivated(RTC::UniqueId ec_id)
{
	digitalWrite(PIN, 0);
  return RTC::RTC_OK;
}

/*!
 * configurationで指定したmodeの値によって処理を変えます．
 * mode 1:LEDを揺らがせます．
 * mode 0:LEDを通常点灯させます
 * それ以外:LEDを消灯します．
 */

RTC::ReturnCode_t PWMFluctuations::onExecute(RTC::UniqueId ec_id)
{
	switch (m_Mode){
	case 0: //自動揺らぎなし
		if (m_inSWIn.isNew()){
			m_inSWIn.read();
			SimpleLED(m_inSW.data);
		}
		break;
	case 1: //自動揺らぎあり
		if (m_inSWIn.isNew()){
			m_inSWIn.read();
			FluctuationsLED(m_inSW.data);
		}
		break;
	default:
		digitalWrite(PIN, 0);
		break;
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PWMFluctuations::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PWMFluctuations::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/***
揺らぎを実装する関数
***/
void PWMFluctuations::FluctuationsLED(bool sw){
	if (sw){								
		//エラーチェック
		Max = BASETIME*m_MaxBrightness;
		Min = BASETIME*m_MinBrightness;
		range = Max - Min + 1;
		if (m_Rate <= 0 || Max <= 0 || Min <= 0 ){
			digitalWrite(PIN, 0);
		}
		else if (Max < Min){
			Min = Max + 1;
			range = 1;
		}
		else{
			//iの変化によってOFFになる時間が徐々に変わることで明るさが変わりこれによって揺らぎを実装している
			int r = rand() % range + m_MinBrightness;	//MinBrightness~MaxBrightnessの間でランダムで値を決める
			if (light<r){											//現在の値よりもランダムの値が大きければifそうでなければelseに入る
				for (; light < r; light = light + m_Rate){					//iをRateの数分だけランダムの値に近づける
					if (light <= 0)light = 1;
					else if (Max <= light)light = Max - 1;
					digitalWrite(PIN, 1);						//ONの指令を出す
					usleep(light);							//ONをOnWidthの分だけ光らせる
					digitalWrite(PIN, 0);						//OFFの指令を出す
					usleep(Max - light);						//OFFの指令をOffWidethとiをかけた分だけ光らせる
				}
			}
			else if (light > r){
				for (; light>r; light = light - m_Rate){
					if (light <= 0)light = 1;
					else if (Max <= light)light = Max - 1;
					digitalWrite(PIN, 1);
					usleep(light);
					digitalWrite(PIN, 0);
					usleep(Max - light);
				}
			}
		}
	}
	else{
		digitalWrite(PIN, 0);								//ONの指令が来なければOFFの指令を出し続ける
	}
}

/***
引数の真偽によってLEDを点滅させる関数
***/
void PWMFluctuations::SimpleLED(bool sw){
	if (sw){
		digitalWrite(PIN, 1);
	}
	else{
		digitalWrite(PIN, 0);
	}
}

extern "C"
{
 
  void PWMFluctuationsInit(RTC::Manager* manager)
  {
    coil::Properties profile(pwmfluctuations_spec);
    manager->registerFactory(profile,
                             RTC::Create<PWMFluctuations>,
                             RTC::Delete<PWMFluctuations>);
  }
  
};


