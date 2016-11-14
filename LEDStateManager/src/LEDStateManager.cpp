// -*- C++ -*-
/*!
 * @file  LEDStateManager.cpp
 * @brief This component manage and link plural LED.
 * @date $Date$
 *
 * @author Shintaro nakazawa
 * cy14143@shibaura-it.ac.jp
 *
 * $Id$
 */

#include "LEDStateManager.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ledstatemanager_spec[] =
  {
    "implementation_id", "LEDStateManager",
    "type_name",         "LEDStateManager",
    "description",       "This component manage and link plural LED.",
    "version",           "1.0.0",
    "vendor",            "Shintaro Nakazawa",
    "category",          "Too",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Mode", "0",
    "conf.default.BaseUnitNum", "0",
    "conf.default.inportNum", "4",
    "conf.default.outportNum", "4",
    // Widget
    "conf.__widget__.Mode", "text",
    "conf.__widget__.BaseUnitNum", "text",
    "conf.__widget__.inportNum", "text",
    "conf.__widget__.outportNum", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
LEDStateManager::LEDStateManager(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_in0In("in0", m_in0),
    m_out0Out("out0", m_out0)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
LEDStateManager::~LEDStateManager()
{
}



RTC::ReturnCode_t LEDStateManager::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in0", m_in0In);
  
  // Set OutPort buffer
  addOutPort("out0", m_out0Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Mode", m_Mode, "0");
  bindParameter("BaseUnitNum", m_BaseUnitNum, "0");
  bindParameter("inportNum", m_inportNum, "4");
  bindParameter("outportNum", m_outportNum, "4");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t LEDStateManager::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t LEDStateManager::onActivated(RTC::UniqueId ec_id)
{
	std::cout << "Activated" << std::endl;
	std::cout << "inportNum : " << m_inportNum << std::endl;
	std::cout << "outportNum : " << m_outportNum << std::endl;
	std::cout << "Mode : " << m_Mode << std::endl;
	

	InPortSetup();

	OutPortSetup();
	
	//フラグ初期化
	for (int i = 0; i < m_inportNum; i++){
	flagLED.push_back(false);
	}
	
	//乱数初期化
	srand((unsigned int)time(NULL));
	

  return RTC::RTC_OK;
}


RTC::ReturnCode_t LEDStateManager::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t LEDStateManager::onExecute(RTC::UniqueId ec_id)
{
	
	for (int i = 0; i < m_inportNum; i++){
		if (in_ports[i]->m_inIn.isNew()){
			in_ports[i]->m_inIn.read();//読み込み
			if (in_ports[i]->m_in.data == 1){//スイッチon
				if (flagLED[i] == true){//フラグonなら
					switchLEDbyMode(m_Mode, i, !out_ports[i]->m_out.data);
					flagLED[i] = false;//フラグoff
				}
			}
			else{//タクトスイッチoff
				flagLED[i] = true;//フラグon
			}
		}//isNew終わり
		out_ports[i]->m_outOut.write();
	}
	
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t LEDStateManager::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t LEDStateManager::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


void LEDStateManager::InPortSetup(){
	unsigned int in_port_size = in_ports.size();//現在のoutport設定数を調べる
	if (m_inportNum > in_port_size)//m_portNumはコンフィグ？指定のポート数より現在のポート数が少なかった場合
	{
		for (int i = in_port_size; i < m_inportNum; i++)//増やしたいポート数分繰り返す
		{
			std::string name = "in";//ポートの名前を「outport」にする
			name = name + coil::otos<int>(i);//ポートの名前を「outport〇」(〇は番号)にする
			MyInPort* port = new MyInPort(name);//ポートリストに入れるためのポートを上で決めたポート名で作る
			in_ports.push_back(port);//作ったポートをポートリストにぶちこむ
			addInPort(name.c_str(), port->m_inIn);//ポートの実態を追加
			std::cout << "addInPort : " << name << "-" << port << std::endl;
		}
	}
	else if (m_inportNum < in_port_size)//指定のポート数より現在ポート数が多かった場合
	{
		for (int i = m_inportNum; i < in_port_size; i++)//減らしたいポート数分繰り返す
		{
			MyInPort* port = in_ports.back();//ポートリストの最後尾のポートへのポインタを取得
			removeInPort(port->m_inIn);//ポートの実態を削除
			in_ports.pop_back();//リストからポートへのポインタを削除
			delete port;//今回作ったポートへのポインタの領域を解放
			std::cout << "deleteInPort : " << port << std::endl;
		}
	}

	for (int i = 0; i < m_inportNum; i++){
		in_ports[i]->m_in.data = false;
		//ポート初期化
	}
}

void LEDStateManager::OutPortSetup(){
	unsigned int out_port_size = out_ports.size();//現在のoutport設定数を調べる
	if (m_outportNum > out_port_size)//m_portNumはコンフィグ？指定のポート数より現在のポート数が少なかった場合
	{
		for (int i = out_port_size; i < m_outportNum; i++)//増やしたいポート数分繰り返す
		{
			std::string name = "out";//ポートの名前を「outport」にする
			name = name + coil::otos<int>(i);//ポートの名前を「outport〇」(〇は番号)にする
			MyOutPort* port = new MyOutPort(name);//ポートリストに入れるためのポートを上で決めたポート名で作る
			out_ports.push_back(port);//作ったポートをポートリストにぶちこむ
			addOutPort(name.c_str(), port->m_outOut);//ポートの実態を追加
			std::cout << "addOutPort : " << name << "-" << port << std::endl;
		}
	}
	else if (m_outportNum < out_port_size)//指定のポート数より現在ポート数が多かった場合
	{
		for (int i = m_outportNum; i < out_port_size; i++)//減らしたいポート数分繰り返す
		{
			MyOutPort* port = out_ports.back();//ポートリストの最後尾のポートへのポインタを取得
			removeOutPort(port->m_outOut);//ポートの実態を削除
			out_ports.pop_back();//リストからポートへのポインタを削除
			delete port;//今回作ったポートへのポインタの領域を解放
			std::cout << "deleteOutPort : " << port << std::endl;
		}
	}

	for (int i = 0; i < m_outportNum; i++){
		out_ports[i]->m_out.data = false;
		//ポート初期化
	}
}


/*
*/
void LEDStateManager::switchLED(short portNo, bool state){
	if ((0 <= portNo) && (portNo < m_inportNum)){
		out_ports[portNo]->m_out.data = state;
	}
}

/*
mode...0:連動(子LED変更不可) 1:連動(子LED変更可) 2:ランダム その他:非連動
*/
void LEDStateManager::switchLEDbyMode(short mode, short portNo, bool state){
	switch (mode){
	case 0:
		if (portNo == m_BaseUnitNum){//親機の場合
			switchLED(m_BaseUnitNum, state);
			for (int i = 0; i < m_inportNum; i++){
				switchLED(i, out_ports[m_BaseUnitNum]->m_out.data);
			}
		}
		break;
	case 1:
		if (portNo == m_BaseUnitNum){//親機の場合
			switchLED(m_BaseUnitNum, state);
			for (int i = 0; i < m_inportNum; i++){
				switchLED(i, out_ports[m_BaseUnitNum]->m_out.data);
			}
		}
		else{//子機の場合
			switchLED(portNo, state);
		}
		break;
	case 2:
		for (int i = 0; i < m_inportNum; i++){
			switchLED(i, rand() % 2);
		}
		break;
	default:
		switchLED(portNo, state);
		break;
	}
}

extern "C"
{
 
  void LEDStateManagerInit(RTC::Manager* manager)
  {
    coil::Properties profile(ledstatemanager_spec);
    manager->registerFactory(profile,
                             RTC::Create<LEDStateManager>,
                             RTC::Delete<LEDStateManager>);
  }
  
};


