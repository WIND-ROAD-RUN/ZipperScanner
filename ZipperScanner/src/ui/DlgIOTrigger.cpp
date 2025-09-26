#include "DlgIOTrigger.h"

#include <QMessageBox>
#include <QtConcurrent/qtconcurrentrun.h>

#include "GlobalStruct.hpp"
#include "Modules.hpp"

DlgIOTrigger::DlgIOTrigger(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgIOTriggerClass())
{
	ui->setupUi(this);

	build_connect();
}

DlgIOTrigger::~DlgIOTrigger()
{
	delete ui;
}

void DlgIOTrigger::build_connect()
{
	QObject::connect(ui->pbtn_close, &QPushButton::clicked,
		this, &DlgIOTrigger::pbtn_close_clicked);
	QObject::connect(ui->btn_shoudongladai, &QPushButton::pressed,
		this, &DlgIOTrigger::btn_shoudongladai_pressed);
	QObject::connect(ui->btn_shoudongladai, &QPushButton::released,
		this, &DlgIOTrigger::btn_shoudongladai_released);
	QObject::connect(ui->btn_tuoji, &QPushButton::clicked,
		this, &DlgIOTrigger::btn_tuoji_clicked);
	QObject::connect(ui->btn_xiangjichufa, &QPushButton::clicked,
		this, &DlgIOTrigger::btn_xiangjichufa_clicked);
	QObject::connect(ui->btn_shoudongchongkong, &QPushButton::clicked,
		this, &DlgIOTrigger::btn_shoudongchongkong_clicked);
}

void DlgIOTrigger::pbtn_close_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	bool isChongKongSet = zmotion->setIOOut(ControlLines::chongkongOUT, false);

	// 冲孔
	if (!isChongKongSet)
	{
		//QMessageBox::warning(this, "警告", "关闭冲孔失败!");
	}

	// 脱机
	bool isTuoJiSet = zmotion->setIOOut(ControlLines::tuojiOut, false);
	if (!isTuoJiSet)
	{
		//QMessageBox::warning(this, "警告", "关闭脱机失败!");
		ui->btn_tuoji->setStyleSheet(
			"QPushButton {"
			"border-color: #388E3C;"
			"background-color: #4CAF50;"
			"color: #fff;"
			"font-weight: bold;"
			"}"
		);
		ui->btn_tuoji->setText("已脱机...");
	}
	else
	{
		ui->btn_tuoji->setStyleSheet(
			"QPushButton {"
			"padding: 6px 14px;"
			"border: 2px solid #CCC;"
			"border-radius: 4px;"
			"background-color: red;"
			"color: #444;"
			"}"
		);
		ui->btn_tuoji->setText("脱机");
	}

	this->close();
}

void DlgIOTrigger::btn_shoudongladai_pressed()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto value = setConfig.meizhuanmaichongshu / setConfig.shedingzhouchang;

	// 启动电机
	auto isAxisType = zmotion->setAxisType(0, 1);
	double unit = value;
	auto isAxisPulse = zmotion->setAxisPulse(0, unit);
	double acc = setConfig.jiajiansushijian;
	auto isAxisAcc = zmotion->setAxisAcc(0, acc);
	auto isAxisDec = zmotion->setAxisDec(0, acc*2);
	double speed = setConfig.shoudongsudu;
	auto isAxisRunSpeed = zmotion->setAxisRunSpeed(0, speed);
	auto isAxisRun = zmotion->setAxisRun(0, -1);

	if (!isAxisType || !isAxisPulse || !isAxisAcc || !isAxisDec || !isAxisRunSpeed || !isAxisRun)
	{
		//QMessageBox::warning(this, "警告", "电机参数设置失败");
	}
}

void DlgIOTrigger::btn_shoudongladai_released()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	// 停止电机
	bool isStop = zmotion->stopAllAxis();

	if (!isStop)
	{
		//QMessageBox::warning(this, "警告", "手动拉带取消失败!");
	}
}

void DlgIOTrigger::btn_shoudongchongkong_clicked()
{
	auto future = QtConcurrent::run([this]() {
		auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto chongkongshijian = setConfig.chongkongshijian*1000;
		auto yanchichongkongshijian = setConfig.yanshichongkong;
		QThread::msleep(yanchichongkongshijian);

		// 停止电机
		bool isStop = zmotion->stopAllAxis();

		if (!isStop)
		{
			//QMessageBox::warning(this, "警告", "停止电机失败!");
		}
		// 冲孔
		bool isSet = zmotion->SetIOOut(2, ControlLines::chongkongOUT, true, chongkongshijian);

		if (!isSet) {
			/*QMetaObject::invokeMethod(this, [this]() {
				QMessageBox::warning(this, "警告", "手动冲孔失败!");
				}, Qt::QueuedConnection);*/
		}
		});
}

void DlgIOTrigger::btn_tuoji_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	bool isGetTuoJiOut = false;
	bool tuojiState = zmotion->getIOOut(ControlLines::tuojiOut, isGetTuoJiOut);
	bool isSuccess = zmotion->setIOOut(ControlLines::tuojiOut, !tuojiState);
	if (!isSuccess)
	{
		//QMessageBox::warning(this, "警告", "设置脱机失败!");
	}

	if (!tuojiState)
	{
		ui->btn_tuoji->setText("已脱机...");
		ui->btn_tuoji->setStyleSheet(
			"QPushButton {"
			"border-color: #388E3C;"
			"background-color: #4CAF50;"
			"color: #fff;"
			"font-weight: bold;"
			"}"
		);
	}
	else
	{
		ui->btn_tuoji->setText("脱机");
		ui->btn_tuoji->setStyleSheet(
			"QPushButton {"
			"padding: 6px 14px;"
			"border: 2px solid #CCC;"
			"border-radius: 4px;"
			"background-color: red;"
			"color: #444;"
			"}"
		);
	}
}

void DlgIOTrigger::btn_xiangjichufa_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	bool isXiangJiChuFaSet = zmotion->SetIOOut(3, ControlLines::xiangjichufaOut1, true, 100);
	bool xiangjichufa = zmotion->SetIOOut(3, ControlLines::xiangjichufaOut2, true, 100);

	if (!isXiangJiChuFaSet||!xiangjichufa)
	{
		//QMessageBox::warning(this, "警告", "相机触发失败!");
	}
}

