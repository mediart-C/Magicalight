// -*- C++ -*-
/*!
 * @file  ThresholdSwitch.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * @author 片桐大地
 * cy14119(at)shibaura-it.ac.jp
 *
 * $Id$
 */

#include "ThresholdSwitch.h"

// Module specification
// <rtc-template block="module_spec">
static const char* thresholdswitch_spec[] =
  {
    "implementation_id", "ThresholdSwitch",
    "type_name",         "ThresholdSwitch",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.AutoMode", "1",
    "conf.default.Frequency", "3",
    "conf.default.Average", "512",
    "conf.default.InportMax", "1023",
    "conf.default.InportMin", "-1",
    "conf.default.Reference", "5",
    "conf.default.ThresholdPercent", "90",
    // Widget
    "conf.__widget__.AutoMode", "text",
    "conf.__widget__.Frequency", "text",
    "conf.__widget__.Average", "text",
    "conf.__widget__.InportMax", "text",
    "conf.__widget__.InportMin", "text",
    "conf.__widget__.Reference", "text",
    "conf.__widget__.ThresholdPercent", "ordered_list",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ThresholdSwitch::ThresholdSwitch(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InportDataIn("InportData", m_InportData),
    m_OutResultOut("OutResult", m_OutResult)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ThresholdSwitch::~ThresholdSwitch()
{
}



RTC::ReturnCode_t ThresholdSwitch::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("InportData", m_InportDataIn);
  
  // Set OutPort buffer
  addOutPort("OutResult", m_OutResultOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("AutoMode", m_AutoMode, "1");
  bindParameter("Frequency", m_Frequency, "3");
  bindParameter("Average", m_Average, "512");
  bindParameter("InportMax", m_InportMax, "1023");
  bindParameter("InportMin", m_InportMin, "-1");
  bindParameter("Reference", m_Reference, "5");
  bindParameter("ThresholdPercent", m_ThresholdPercent, "90");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ThresholdSwitch::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * OutResultの初期設定をします。
 */

RTC::ReturnCode_t ThresholdSwitch::onActivated(RTC::UniqueId ec_id)
{
	//int型変数の初期化
	refNum = 0;  sum = 1;  in_dataNum = 0; aveNum = 0; count = 0; ignore = 0; ref = 0; oldref=0;
	//double型変数の初期化
	process = 0; bias = 0; ThresholdMax = 0; ThresholdMin = -1; AutoMax = 0; AutoMin = -1; ave = 0; max = 0; min = 0;
	//bool型変数の初期化
	now_result = false;

	m_OutResult.data = false;
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ThresholdSwitch::onDeactivated(RTC::UniqueId ec_id)
{
	m_OutResult.data = false;
  return RTC::RTC_OK;
}

/*!
 * 入力された値が閾値を超えているか否かを判断します。また、configu
 * retionの設定の反映を行います。
 */

RTC::ReturnCode_t ThresholdSwitch::onExecute(RTC::UniqueId ec_id)
{
	if (m_InportDataIn.isNew()){
		ref = m_Reference;	//参照データ数の更新

		if (oldref != ref){	//参照データ数の変更
			in_data.clear();
			in_data.resize(ref);
			in_data.shrink_to_fit();
			oldref = ref;
		}

		if (in_dataNum >= ref)	in_dataNum = 0;//参照データを入れなおす要素をはじめにもどす
		m_InportDataIn.read();
		std::cout << m_InportData.data << std::endl;//生データ表示
		std::cout << "Bias=" << bias << std::endl;//バイアス表示
		if (aveNum < 10000) aveNum++;//保持するデータ数増加
		ave = (aveNum*bias + m_InportData.data) / (aveNum + 1);//保持するデータを用いて平均を計算
		if (m_AutoMode == 1){
			bias = ave;
			if (AutoMax < (m_InportData.data - bias)){
				AutoMax = m_InportData.data - bias;
				max = AutoMax;
			}
			else if (AutoMin>(m_InportData.data - bias)){
				AutoMin = m_InportData.data - bias;
				min = AutoMin;
			}
		}
		else{
			bias = m_Average;
			ThresholdMax = m_InportMax;
			ThresholdMin = m_InportMin;
			max = ThresholdMax - bias;
			min = ThresholdMin - bias;
		}
		sum = m_InportData.data - bias;
		if ((100 * sum / max >= m_ThresholdPercent) || (100 * sum / min >= m_ThresholdPercent)){
			in_data[in_dataNum] = 1;
		}
		else{
			in_data[in_dataNum] = 0;
		}
		count = 0;
		for (refNum = 0; refNum < ref; refNum++){
			count = count + in_data[refNum];
		}
		if (count >= m_Frequency){
			now_result = true;
		}
		else{
			now_result = false;
		}
		m_OutResult.data = now_result;
		std::cout << m_OutResult.data << std::endl;
		m_OutResultOut.write();
		in_dataNum++;
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ThresholdSwitch::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ThresholdSwitch::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ThresholdSwitchInit(RTC::Manager* manager)
  {
    coil::Properties profile(thresholdswitch_spec);
    manager->registerFactory(profile,
                             RTC::Create<ThresholdSwitch>,
                             RTC::Delete<ThresholdSwitch>);
  }
  
};


