// -*- C++ -*-
/*!
 * @file  ThresholdSwitch.h
 * @brief ModuleDescription
 * @date  $Date$
 *
 * @author 片桐大地
 * cy14119(at)shibaura-it.ac.jp
 *
 * $Id$
 */

#ifndef THRESHOLDSWITCH_H
#define THRESHOLDSWITCH_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <vector>

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
 * @class ThresholdSwitch
 * @brief ModuleDescription
 *
 * ThresholdSwitchは，コンポーネントから入力された値を参照し，閾値
 * を超えたらtrueを返すコンポーネントです.
 *
 * Inport
 * 名前/型/説明
 * InportData/TimedDouble/外部で読み取ったデータを受け取る．
 * Outport
 * 名前/型/説明
 * OutResult/TimedBoolean	/読み取ったデータと任意の値からtrueまたは
 * falseを出力する．
 *
 */
class ThresholdSwitch
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  ThresholdSwitch(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~ThresholdSwitch();

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
   * OutResultの初期設定をします。
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
   * 入力された値が閾値を超えているか否かを判断します。また、confi
   * guretionの設定の反映を行います。
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
   * 自動演算モードにするか手動入力モードにするかを選びます．
   * 0.	自動演算モード
   * 1.	手動入力モード
   * - Name: AutoMode AutoMode
   * - DefaultValue: 1
   */
  int m_AutoMode;
  /*!
   * 任意の回数の中で，この回数分だけ閾値を超えればtrueが出力される
   * 値．
   * - Name: Frequency Frequency
   * - DefaultValue: 3
   */
  int m_Frequency;
  /*!
   * 入力されるデータの値の平均値．
   * - Name: Average Average
   * - DefaultValue: 512
   */
  double m_Average;
  /*!
   * 入力されるデータの最大値です．
   * - Name: InportMax InportMax
   * - DefaultValue: 1023
   */
  double m_InportMax;
  /*!
   * 入力されるデータの最小値です．
   * - Name: InportMin InportMin
   * - DefaultValue: -1
   */
  double m_InportMin;
  /*!
   * trueを出力するかfalseを出力するかを決めるときに参照する値の参
   * 照データの個数です.
   * - Name: Reference Reference
   * - DefaultValue: 5
   */
  int m_Reference;
  /*!
   * 平均値から最大値，最小値を100%とした時の閾値です．
   * - Name: ThresholdPercent ThresholdPercent
   * - DefaultValue: 90
   */
  double m_ThresholdPercent;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedDouble m_InportData;
  /*!
   * 外部で読み取ったっデータを受け取ります。
   * - Type: TimedDouble
   */
  InPort<RTC::TimedDouble> m_InportDataIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedBoolean m_OutResult;
  /*!
   * 受け取ったデータと任意に設定した値からtrueまたはfalseを出力す
   * る
   * - Type: TimedBoolean
   */
  OutPort<RTC::TimedBoolean> m_OutResultOut;
  
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
	 int refNum = 0, sum = 1, in_dataNum = 0, aveNum = 0,/* refdata[REFERENCE] = {},*/ count = 0, ignore = 0, ref = 0, oldref;
	 double process = 0, bias = 0, ThresholdMax = 0, ThresholdMin = -1, AutoMax = 0, AutoMin = -1;
	 double ave = 0, max = 0, min = 0;
	 bool now_result;
	 std::vector<int> in_data;
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void ThresholdSwitchInit(RTC::Manager* manager);
};

#endif // THRESHOLDSWITCH_H
