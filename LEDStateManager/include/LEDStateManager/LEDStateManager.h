// -*- C++ -*-
/*!
 * @file  LEDStateManager.h
 * @brief This component manage and link plural LED.
 * @date  $Date$
 *
 * @author Shintaro nakazawa
 * cy14143@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef LEDSTATEMANAGER_H
#define LEDSTATEMANAGER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <stdio.h>
#include <vector>

class MyInPort
{
public:
	MyInPort(std::string name) :m_inIn(name.c_str(), m_in)//ポートを作るコンストラクタ、MyInPortのコンストラクタの処理をするとnameに入れた名前でポートの形が作られる
	{
	};

	RTC::TimedBoolean m_in;
	InPort<RTC::TimedBoolean> m_inIn;
};

class MyOutPort
{
public:
	MyOutPort(std::string name) :m_outOut(name.c_str(), m_out)//ポートを作るコンストラクタ、MyOutPortのコンストラクタの処理をするとnameに入れた名前でポートの形が作られる
	{
	};

	RTC::TimedBoolean m_out;
	OutPort<RTC::TimedBoolean> m_outOut;
};

/*!
 * @class LEDStateManager
 * @brief This component manage and link plural LED.
 *
 * 接続されたLEDの点灯/消灯状態を入力として受取し，Configurationで
 * 設定したモードの方法で連動するようにtrue/falseを出力します．
 * InPort, OutPortの数はconfigurationで設定できます．
 *
 * <InPort>
 * 現在のLEDの点灯/消灯状態に応じてtrue/falseが入力されます．
 * 接続するLEDの数に応じてConfiguration:inportNumの値を変更してくだ
 * さい．
 * <OutPort>
 * 連動処理後のLEDの点灯/消灯に応じてtrue/falseが出力されます．
 * 接続するLEDの数に応じてConfiguration:inportNumの値を変更してくだ
 * さい．
 *
 */
class LEDStateManager
  : public RTC::DataFlowComponentBase
{
 public:
	 //プロトタイプ宣言
	 void InPortSetup();
	 void OutPortSetup();
	 void switchLED(short portNo, bool state);
	 void switchLEDbyMode(short mode, short portNo, bool state);
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  LEDStateManager(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~LEDStateManager();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
 　* Configurationで設定した数InPort, OutPortを追加し，全て初期化します．
 　* また，フラグと乱数も初期化します．
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
　 * Deactivated時に行う処理はありません．
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   * configurationのModeの値に応じて，LEDを連動させます．
   * Mode 0:通常連動モード
   * Mode 1:イエスマンモード
   * Mode 2:ランダムモード
   * Mode 3:非連動モード
   * その他:全出力ポートにfalseを入力
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 連動方法を設定します．
   * Mode 0:通常連動モード
   * Mode 1:イエスマンモード
   * Mode 2:ランダムモード
   * Mode 3:非連動モード
   * その他:全出力ポートにfalseを入力
   * - Name: Mode Mode
   * - DefaultValue: 0
   */
  int m_Mode;
  /*!
   * 連動時の親機の番号を設定します．
   * - Name: BaseUnitNum BaseUnitNum
   * - DefaultValue: 0
   */
  int m_BaseUnitNum;
  /*!
   * 使用するinportの数を決定します．
   * - Name: inportNum inportNum
   * - DefaultValue: 4
   */
  int m_inportNum;
  /*!
   * 使用するinportの数を決定します．
   * - Name: outportNum outportNum
   * - DefaultValue: 4
   */
  int m_outportNum;


  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedBoolean m_in0;
  /*!
   * 現在接続されているLEDの点灯/消灯に応じてtrue/falseが入力されま
   * す．
   * 接続するLEDの数に応じてConfiguration:inportNumの値を変更してく
   * ださい．ポートの呼び名は上から0番，1番，・・・としています．
   * - Type: TimedBoolean
   * - Number: 1
   */
  InPort<RTC::TimedBoolean> m_in0In;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedBoolean m_out0;
  /*!
   * 連動処理後のLEDの点灯/消灯に応じてtrue/falseが出力されます．
   * 接続するLEDの数に応じてConfiguration:outportNumの値を変更して
   * ください．
   * ポートの呼び名は上から0番，1番，・・・としています．
   * - Type: TimedBoolean
   * - Number: 1
   */
  OutPort<RTC::TimedBoolean> m_out0Out;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
	 std::vector<bool> flagLED;//LED変更スイッチフラグ
	 std::vector<MyInPort*> in_ports;	//InPortの情報を格納する
	 std::vector<MyOutPort*> out_ports;	//OutPortの情報を格納する
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void LEDStateManagerInit(RTC::Manager* manager);
};

#endif // LEDSTATEMANAGER_H
