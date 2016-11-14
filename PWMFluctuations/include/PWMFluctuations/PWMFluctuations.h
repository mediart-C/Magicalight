// -*- C++ -*-
/*!
 * @file  PWMFluctuations.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * @author Shintaro Nakazawa
 * cy14143@shibaura-it.ac.jp
 * Daichi Katagiri
 * cy14119@shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef PWMFLUCTUATIONS_H
#define PWMFLUCTUATIONS_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

/***
wiringPiを使用するためのヘッダーファイル
***/
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "mcp3002.h"

/***
揺らがせるLEDを接続するポートの番号
ただしGPIOピン番号ではなく，WiriniPi番号なので注意してください．
***/
#define PIN 17
#define BASETIME 200
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

/*!
 * @class PWMFluctuations
 * @brief ModuleDescription
 *
 * 本コンポーネントはRaspberryPiに接続されたLEDをON，OFFを切り替え
 * ることで，疑似的に火のように揺らがせるコンポーネントです．
 * 今回はGPIO17ピンにLEDが接続されていることを前提とします．
 *
 * 入力ではTimedBoolean型の値を受け取り，TRUEが来続けているときはL
 * EDを点灯させ，FALSEが来続けているときはLEDを消灯させます．
 *
 */
class PWMFluctuations
  : public RTC::DataFlowComponentBase
{
 public:
	 /***
	 * プロトタイプ宣言
	 ***/
	 void SimpleLED(bool sw);
	 void FluctuationsLED(bool sw);
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PWMFluctuations(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PWMFluctuations();

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
   * wiringPiのセットアップを行います．
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * @pre RaspberryPiにWiringPiがインストールされていること。
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
   * configurationで指定したmodeの値によって処理を変えます．
   * mode 1:LEDを揺らがせます．
   * mode 0:LEDを通常点灯させます
   * それ以外:LEDを消灯します．
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * @pre RaspberryPiのGPIO17ピンにLED を接続してください．
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
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
   * 1:揺らぎモード
   * 0:通常点灯モード
   * それ以外:消灯モード
   * - Name: Mode Mode
   * - DefaultValue: 1
   */
  int m_Mode;
  /*!
   * 揺らぎ時の明るさの最大値を決定する．数値が大きい方が一番明るい
   * ときが明るくなる．
   * - Name: MaxBrightness MaxBrightness
   * - DefaultValue: 1200
   * - Range: 0より大きい
   */
  int m_MaxBrightness;
  /*!
   * 揺らぎ時の明るさの最大値を決定する．大きくなればなるほど一番暗
   * い時がより暗くなる．
   * - Name: MinBrightness MinBrightness
   * - DefaultValue: 300
   * - Range: 0より大きい
   */
  int m_MinBrightness;
  /*!
   * 揺らぎ時の揺らぎの変化の速さを変える．値を大きくすると速くなり
   * ，小さくすると遅くなる．
   * - Name: Rate Rate
   * - DefaultValue: 2
   * - Range: 0より大きい
   */
  int m_Rate;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedBoolean m_inSW;
  /*!
   * LEDの点灯/消灯を決めます．
   * TRUEが入力されている間は点灯，FALSEが入力されている間は消灯し
   * ます．
   * - Type: TimedBoolean
   * - Number: 1
   */
  InPort<RTC::TimedBoolean> m_inSWIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
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
	 int range, Max, Min, light;
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PWMFluctuationsInit(RTC::Manager* manager);
};

#endif // PWMFLUCTUATIONS_H
