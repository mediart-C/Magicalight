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
	
	//�t���O������
	for (int i = 0; i < m_inportNum; i++){
	flagLED.push_back(false);
	}
	
	//����������
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
			in_ports[i]->m_inIn.read();//�ǂݍ���
			if (in_ports[i]->m_in.data == 1){//�X�C�b�`on
				if (flagLED[i] == true){//�t���Oon�Ȃ�
					switchLEDbyMode(m_Mode, i, !out_ports[i]->m_out.data);
					flagLED[i] = false;//�t���Ooff
				}
			}
			else{//�^�N�g�X�C�b�`off
				flagLED[i] = true;//�t���Oon
			}
		}//isNew�I���
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
	unsigned int in_port_size = in_ports.size();//���݂�outport�ݒ萔�𒲂ׂ�
	if (m_inportNum > in_port_size)//m_portNum�̓R���t�B�O�H�w��̃|�[�g����茻�݂̃|�[�g�������Ȃ������ꍇ
	{
		for (int i = in_port_size; i < m_inportNum; i++)//���₵�����|�[�g�����J��Ԃ�
		{
			std::string name = "in";//�|�[�g�̖��O���uoutport�v�ɂ���
			name = name + coil::otos<int>(i);//�|�[�g�̖��O���uoutport�Z�v(�Z�͔ԍ�)�ɂ���
			MyInPort* port = new MyInPort(name);//�|�[�g���X�g�ɓ���邽�߂̃|�[�g����Ō��߂��|�[�g���ō��
			in_ports.push_back(port);//������|�[�g���|�[�g���X�g�ɂԂ�����
			addInPort(name.c_str(), port->m_inIn);//�|�[�g�̎��Ԃ�ǉ�
			std::cout << "addInPort : " << name << "-" << port << std::endl;
		}
	}
	else if (m_inportNum < in_port_size)//�w��̃|�[�g����茻�݃|�[�g�������������ꍇ
	{
		for (int i = m_inportNum; i < in_port_size; i++)//���炵�����|�[�g�����J��Ԃ�
		{
			MyInPort* port = in_ports.back();//�|�[�g���X�g�̍Ō���̃|�[�g�ւ̃|�C���^���擾
			removeInPort(port->m_inIn);//�|�[�g�̎��Ԃ��폜
			in_ports.pop_back();//���X�g����|�[�g�ւ̃|�C���^���폜
			delete port;//���������|�[�g�ւ̃|�C���^�̗̈�����
			std::cout << "deleteInPort : " << port << std::endl;
		}
	}

	for (int i = 0; i < m_inportNum; i++){
		in_ports[i]->m_in.data = false;
		//�|�[�g������
	}
}

void LEDStateManager::OutPortSetup(){
	unsigned int out_port_size = out_ports.size();//���݂�outport�ݒ萔�𒲂ׂ�
	if (m_outportNum > out_port_size)//m_portNum�̓R���t�B�O�H�w��̃|�[�g����茻�݂̃|�[�g�������Ȃ������ꍇ
	{
		for (int i = out_port_size; i < m_outportNum; i++)//���₵�����|�[�g�����J��Ԃ�
		{
			std::string name = "out";//�|�[�g�̖��O���uoutport�v�ɂ���
			name = name + coil::otos<int>(i);//�|�[�g�̖��O���uoutport�Z�v(�Z�͔ԍ�)�ɂ���
			MyOutPort* port = new MyOutPort(name);//�|�[�g���X�g�ɓ���邽�߂̃|�[�g����Ō��߂��|�[�g���ō��
			out_ports.push_back(port);//������|�[�g���|�[�g���X�g�ɂԂ�����
			addOutPort(name.c_str(), port->m_outOut);//�|�[�g�̎��Ԃ�ǉ�
			std::cout << "addOutPort : " << name << "-" << port << std::endl;
		}
	}
	else if (m_outportNum < out_port_size)//�w��̃|�[�g����茻�݃|�[�g�������������ꍇ
	{
		for (int i = m_outportNum; i < out_port_size; i++)//���炵�����|�[�g�����J��Ԃ�
		{
			MyOutPort* port = out_ports.back();//�|�[�g���X�g�̍Ō���̃|�[�g�ւ̃|�C���^���擾
			removeOutPort(port->m_outOut);//�|�[�g�̎��Ԃ��폜
			out_ports.pop_back();//���X�g����|�[�g�ւ̃|�C���^���폜
			delete port;//���������|�[�g�ւ̃|�C���^�̗̈�����
			std::cout << "deleteOutPort : " << port << std::endl;
		}
	}

	for (int i = 0; i < m_outportNum; i++){
		out_ports[i]->m_out.data = false;
		//�|�[�g������
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
mode...0:�A��(�qLED�ύX�s��) 1:�A��(�qLED�ύX��) 2:�����_�� ���̑�:��A��
*/
void LEDStateManager::switchLEDbyMode(short mode, short portNo, bool state){
	switch (mode){
	case 0:
		if (portNo == m_BaseUnitNum){//�e�@�̏ꍇ
			switchLED(m_BaseUnitNum, state);
			for (int i = 0; i < m_inportNum; i++){
				switchLED(i, out_ports[m_BaseUnitNum]->m_out.data);
			}
		}
		break;
	case 1:
		if (portNo == m_BaseUnitNum){//�e�@�̏ꍇ
			switchLED(m_BaseUnitNum, state);
			for (int i = 0; i < m_inportNum; i++){
				switchLED(i, out_ports[m_BaseUnitNum]->m_out.data);
			}
		}
		else{//�q�@�̏ꍇ
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


