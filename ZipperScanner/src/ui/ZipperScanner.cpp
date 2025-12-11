#include "ZipperScanner.h"

#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QProcess>

#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"
#include "Utilty.hpp"
#include "WarnUtilty.hpp"
#include "rqw_CameraObjectThread.hpp"
#include "DetachDefectThread.h"
#include "DlgIOTrigger.h"
#include "DlgProductScore.h"
#include "DlgProductSet.h"
#include "DlgShutdownWarn.h"
#include "Modules.hpp"
#include "DlgCloseForm.h"

#ifdef BUILD_WITHOUT_HARDWARE
void ZipperScanner::cBox_testPushImg_checked(bool checked)
{
	if (checked)
	{
		Modules::getInstance().test_module.testImgPush = true;
	}
	else
	{
		Modules::getInstance().test_module.testImgPush = false;
	}
}
#endif

ZipperScanner::ZipperScanner(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::ZipperScannerClass())
{
	auto& globalStruct = GlobalData::getInstance();

	ui->setupUi(this);

	// 读取参数
	read_config();

	// 构建运动控制器
	getZMotionStateAndUpdateUi();

	//开机清零
	pbtn_resetProduct_clicked();

	// 构建UI
	build_ui();

	// 构建图片放大查看器
	build_ImageEnlargedDisplay();

	// 连接相机
	getCameraStateAndUpdateUi();

	// 连接槽函数
	build_connect();
}

ZipperScanner::~ZipperScanner()
{
	destroyComponents();
	Modules::getInstance().stop();
	Modules::getInstance().destroy();
#ifdef NDEBUG
	if (isShutdownByIO)
	{
		bool result = QProcess::startDetached("shutdown", QStringList() << "-s" << "-t" << "0");
		qDebug() << "Shutdown command started:" << result;
	}
#endif

	delete ui;
}

// 构建UI
void ZipperScanner::build_ui()
{
	build_ZipperScannerData();

#ifdef BUILD_WITHOUT_HARDWARE
	cBox_testPushImg = new QCheckBox(this);
	cBox_testPushImg->setText("图像推送状态");
	ui->gBox_infor->layout()->addWidget(cBox_testPushImg);
	QObject::connect(cBox_testPushImg, &QCheckBox::clicked,
		this, &ZipperScanner::cBox_testPushImg_checked);
#endif
}

// 连接槽函数
void ZipperScanner::build_connect()
{
	auto& GlobalStructDataZipper = GlobalData::getInstance();
	// 退出
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_exit_clicked);

	// 设置
	QObject::connect(ui->pbtn_set, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_set_clicked);

	// 分数
	QObject::connect(ui->pbtn_score, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_score_clicked);

	// 开启调试显示新窗体
	QObject::connect(ui->rbtn_debug, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_debug_checked);

	// 强光
	QObject::connect(ui->rbtn_strongLight, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_strongLight_checked);
	// 中光
	QObject::connect(ui->rbtn_mediumLight, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_mediumLight_checked);
	// 弱光
	QObject::connect(ui->rbtn_weakLight, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_weakLight_checked);

	// 打开图像路径文件夹
	QObject::connect(ui->pbtn_openSaveLocation, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_openSaveLocation_clicked);

	// 采图
	QObject::connect(ui->rbtn_takePicture, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_takePicture_checked);

	// 是否识别框
	QObject::connect(ui->ckb_shibiekuang, &QCheckBox::clicked,
		this, &ZipperScanner::ckb_shibiekuang_checked);

	// 是否文字
	QObject::connect(ui->ckb_wenzi, &QCheckBox::clicked,
		this, &ZipperScanner::ckb_wenzi_checked);

	// 连接启动按钮
	QObject::connect(ui->rbtn_start, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_start_clicked);
	// 连接停止按钮
	QObject::connect(ui->rbtn_stop, &QRadioButton::clicked,
		this, &ZipperScanner::rbtn_stop_clicked);

	// 连接IO触发窗体
	QObject::connect(ui->pbtn_IOTrigger, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_IOTrigger_clicked);

	// 连接显示标题
	QObject::connect(clickableTitle, &rw::rqw::ClickableLabel::clicked,
		this, &ZipperScanner::lb_title_clicked);

	// 连接设置拉带长度按钮
	QObject::connect(ui->btn_shedingladaichangdu, &QPushButton::clicked,
		this, &ZipperScanner::btn_shedingladaichangdu_clicked);

	// 连接重置产品按钮
	QObject::connect(ui->pbtn_resetProduct, &QPushButton::clicked,
		this, &ZipperScanner::pbtn_resetProduct_clicked);
}

// 构建相机
void ZipperScanner::getCameraStateAndUpdateUi()
{
	auto& cameraModules = Modules::getInstance().cameraModule;
	auto errors = cameraModules.getBuildResults();
	updateCameraLabelState(1, true);
	updateCameraLabelState(2, true);

	for (const auto& error : errors)
	{
		auto index = static_cast<int>(error);
		updateCameraLabelState(index, false);
	}
}

void ZipperScanner::getZMotionStateAndUpdateUi()
{
	auto& motionControllerModule = Modules::getInstance().motionControllerModule;
	auto& isBuildZmotion = motionControllerModule.isConnectMotion;
	updateCameraLabelState(0, isBuildZmotion);
}

// 加载ZipperScanner窗体数据
void ZipperScanner::build_ZipperScannerData()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& statisticalInfo = Modules::getInstance().runtimeInfoModule.statisticalInfo;
	
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	// 初始化全局数据
	ui->label_produceLength->setText(QString::number(zipperScannerConfig.produceLength));
	ui->label_punchCount->setText(QString::number(zipperScannerConfig.punchCount));
	statisticalInfo.produceLength = zipperScannerConfig.produceLength;
	statisticalInfo.punchCount = zipperScannerConfig.punchCount;

	ui->rbtn_strongLight->setChecked(zipperScannerConfig.qiangGuang);
	ui->rbtn_mediumLight->setChecked(zipperScannerConfig.zhongGuang);
	ui->rbtn_weakLight->setChecked(zipperScannerConfig.ruoGuang);
	ui->btn_shedingladaichangdu->setText(QString::number(zipperScannerConfig.shedingladaichangdu));

	rbtn_stop_clicked(true); // 默认停止

	// 去掉标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);

	// 开机默认不显示但是勾选
	ui->ckb_shibiekuang->setVisible(false);
	ui->ckb_wenzi->setVisible(false);

	ui->ckb_shibiekuang->setChecked(true);
	ui->ckb_wenzi->setChecked(false);

	// 初始化图像查看器
	_picturesViewer = new PictureViewerThumbnails(this);

	ini_clickableTitle();
}

void ZipperScanner::ini_clickableTitle()
{
	// 初始化标题label
	clickableTitle = new rw::rqw::ClickableLabel(this);
	auto layoutTitle = ui->groupBox_head->layout();
	layoutTitle->replaceWidget(ui->label_title, clickableTitle);
	delete ui->label_title;
	clickableTitle->setText("拉链检测");
	clickableTitle->setStyleSheet("QLabel {font-size: 30px;font-weight: bold;color: rgb(255, 255, 255);padding: 5px 5px;border-bottom: 2px solid #cccccc;}");
}

void ZipperScanner::destroyComponents()
{
	// 关闭剔废功能并停止冲孔与轴运动
	rbtn_stop_clicked(true); // 默认停止
	rbtn_removeFunc_checked(false);

	// 销毁图片放大查看器
	destroy_ImageEnlargedDisplay();
}

void ZipperScanner::read_config()
{
	read_config_GeneralConfig();
	updateControllines();
}

// 读取通用配置
void ZipperScanner::read_config_GeneralConfig()
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& storeContext = Modules::getInstance().configManagerModule.storeContext;

	storeContext->ensureFileExistsSafe(globalPath.generalConfigPath.toStdString(), cdm::GeneralConfig());
	auto loadResult = storeContext->loadSafe(globalPath.generalConfigPath.toStdString());
	if (!loadResult)
	{
		storeContext->saveSafe(cdm::GeneralConfig(), globalPath.generalConfigPath.toStdString());
		return;
	}
	generalConfig = *loadResult;
}

void ZipperScanner::updateControllines()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	ControlLines::qidonganniuIn = setConfig.qidonganniuIn;
	ControlLines::jitingIn = setConfig.jitingIn;
	ControlLines::lalianlawanIn = setConfig.lalianlawanIn;
	ControlLines::guanjiIn = setConfig.guanjiIn;
	ControlLines::chongkongOUT = setConfig.chongkongOut;
	ControlLines::tuojiOut = setConfig.tuojiOut;
	ControlLines::xiangjichufaOut1 = setConfig.xiangjichufapaizhao1Out;
	ControlLines::xiangjichufaOut2 = setConfig.xiangjichufapaizhao2Out;
	ControlLines::DOWarnRed = setConfig.DOWarnRed;
	ControlLines::DOWarnGreen = setConfig.DOWarnGreen;
}

void ZipperScanner::changeRemoveFucState(bool state)
{
	auto& runningState = Modules::getInstance().runtimeInfoModule.runningState;
	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;
	if (state)
	{
		runningState = RunningState::OpenRemoveFunc;
		if (camera1)
		{
			camera1->setTriggerState(true);
			camera1->setFrameRate(50);
		}
		if (camera2)
		{
			camera2->setTriggerState(true);
			camera2->setFrameRate(50);
		}
		ui->rbtn_debug->setChecked(false);
		ui->ckb_shibiekuang->setVisible(false);
		ui->ckb_wenzi->setVisible(false);
	}
	else
	{
		runningState = RunningState::Stop;
	}
}

void ZipperScanner::pbtn_exit_clicked()
{
#ifdef NDEBUG
	auto& _dlgCloseForm = Modules::getInstance().uiModule._dlgCloseForm;
	if (_dlgCloseForm)
	{
		_dlgCloseForm->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
		_dlgCloseForm->exec();
	}
#else
	this->close();
#endif
}

void ZipperScanner::pbtn_set_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		if (numKeyBord.getValue() == "1234") {
			auto& _dlgProductSet = Modules::getInstance().uiModule._dlgProductSet;
			_dlgProductSet->setFixedSize(this->width(), this->height());
			_dlgProductSet->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
			_dlgProductSet->exec();
		}
		else {
			QMessageBox::warning(this, "Error", "密码错误，请重新输入");
		}
	}
}

void ZipperScanner::pbtn_score_clicked()
{
	auto& _dlgProductScore = Modules::getInstance().uiModule._dlgProductScore;
	_dlgProductScore->setFixedSize(this->width(), this->height());
	_dlgProductScore->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	_dlgProductScore->exec();
}

void ZipperScanner::rbtn_debug_checked(bool checked)
{
	auto isRuning = ui->rbtn_start->isChecked();

	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;

	auto& runningState = Modules::getInstance().runtimeInfoModule.runningState;
	if (!isRuning) {
		if (checked) {
			runningState = RunningState::Debug;
			if (camera1)
			{
				camera1->setTriggerState(false);
				camera1->setFrameRate(5);
			}
			if (camera2)
			{
				camera2->setTriggerState(false);
				camera2->setFrameRate(5);
			}
			ui->rbtn_takePicture->setChecked(false);
		}
		else {
			runningState = RunningState::Stop;
			if (camera1)
			{
				camera1->setTriggerState(true);
				camera1->setFrameRate(50);
			}
			if (camera2)
			{
				camera2->setTriggerState(true);
				camera2->setFrameRate(50);
			}
		}
		ui->ckb_shibiekuang->setVisible(checked);
		ui->ckb_wenzi->setVisible(checked);
	}
	else {
		ui->rbtn_debug->setChecked(false);
	}
}

void ZipperScanner::rbtn_strongLight_checked(bool checked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;

	if (camera1)
	{
		auto isSuccess1 = camera1->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang1));
		auto isSuccess2 = camera1->setGain(static_cast<size_t>(setConfig.qiangZengYi1));
	}
	if (camera2)
	{
		auto isSuccess1 = camera2->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang2));
		auto isSuccess2 = camera2->setGain(static_cast<size_t>(setConfig.qiangZengYi2));
	}

	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	zipperScannerConfig.qiangGuang = true;
	zipperScannerConfig.zhongGuang = false;
	zipperScannerConfig.ruoGuang = false;
}

void ZipperScanner::rbtn_mediumLight_checked(bool checked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;

	if (camera1)
	{
		auto isSuccess1 = camera1->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang1));
		auto isSuccess2 = camera1->setGain(static_cast<size_t>(setConfig.zhongZengYi1));
	}
	if (camera2)
	{
		auto isSuccess1 = camera2->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang2));
		auto isSuccess2 = camera2->setGain(static_cast<size_t>(setConfig.zhongZengYi2));
	}
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	zipperScannerConfig.qiangGuang = false;
	zipperScannerConfig.zhongGuang = true;
	zipperScannerConfig.ruoGuang = false;
}

void ZipperScanner::rbtn_weakLight_checked(bool checked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto& camera1 = Modules::getInstance().cameraModule.camera1;
	auto& camera2 = Modules::getInstance().cameraModule.camera2;
	if (camera1)
	{
		auto isSuccess1 = camera1->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang1));
		auto isSuccess2 = camera1->setGain(static_cast<size_t>(setConfig.ruoZengYi1));
	}
	if (camera2)
	{
		auto isSuccess1 = camera2->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang2));
		auto isSuccess2 = camera2->setGain(static_cast<size_t>(setConfig.ruoZengYi2));
	}
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	zipperScannerConfig.qiangGuang = false;
	zipperScannerConfig.zhongGuang = false;
	zipperScannerConfig.ruoGuang = true;
}

void ZipperScanner::pbtn_openSaveLocation_clicked()
{
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	QString imageSavePath = imageSaveEngine->getRootPath();

	_picturesViewer->setRootPath(imageSavePath);
	_picturesViewer->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	_picturesViewer->show();
}

void ZipperScanner::rbtn_takePicture_checked()
{
	if (ui->rbtn_debug->isChecked() == true)
	{
		ui->rbtn_takePicture->setChecked(false);
	}
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& isTakePictures = Modules::getInstance().runtimeInfoModule.isTakePictures;
	generalConfig.isSaveImg = ui->rbtn_takePicture->isChecked();
	isTakePictures = ui->rbtn_takePicture->isChecked();
}

void ZipperScanner::rbtn_removeFunc_checked(bool checked)
{
	changeRemoveFucState(checked);
}

void ZipperScanner::ckb_shibiekuang_checked(bool checked)
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	generalConfig.isshibiekuang = ui->ckb_shibiekuang->isChecked();

	emit shibiekuangChanged();
}

void ZipperScanner::ckb_wenzi_checked(bool checked)
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	generalConfig.iswenzi = ui->ckb_wenzi->isChecked();

	emit wenziChanged();
}

void ZipperScanner::rbtn_start_clicked(bool checked)
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto & globalData = GlobalData::getInstance();
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (checked)
	{
		generalConfig.isStart = true;
		generalConfig.isStop = false;

		// 启动电机
		auto value = setConfig.meizhuanmaichongshu / setConfig.shedingzhouchang;

		auto isAxisType = zmotion->setAxisType(0, 1);
		double unit = value;
		auto isAxisPulse = zmotion->setAxisPulse(0, unit);
		double acc = setConfig.jiajiansushijian;
		auto isAxisAcc = zmotion->setAxisAcc(0, acc);
		auto isAxisDec = zmotion->setAxisDec(0, acc * 2);
		double speed = setConfig.zidongladaisudu;
		auto isAxisRunSpeed = zmotion->setAxisRunSpeed(0, speed);
		auto isAxisRun = zmotion->setAxisRun(0, -1);

		//记录当前位置
		

		if (!isAxisType || !isAxisPulse || !isAxisAcc || !isAxisDec || !isAxisRunSpeed || !isAxisRun)
		{
			//QMessageBox::warning(this, "警告", "电机参数设置失败");
		}
		changeRemoveFucState(true);

		globalData .goToGetStartLocation = true;
	}
	else
	{
		generalConfig.isStart = false;
		generalConfig.isStop = true;

		// 停止电机
		bool isStop = zmotion->stopAllAxis();

		if (!isStop)
		{
			//QMessageBox::warning(this, "警告", "停止电机取消失败!");
		}
		changeRemoveFucState(false);
	}
}

void ZipperScanner::rbtn_stop_clicked(bool checked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& globalData = GlobalData::getInstance();
	if (checked)
	{
		changeRemoveFucState(false);
		ui->rbtn_stop->setChecked(checked);
		generalConfig.isStart = false;
		generalConfig.isStop = true;

		// 停止电机
		bool isStop = zmotion->stopAllAxis();

		// 停止冲孔
		isStop = zmotion->setIOOut(ControlLines::chongkongOUT, false);

		globalData.goToGetStopLocation = true;
	}
	else
	{
		changeRemoveFucState(true);
		generalConfig.isStart = true;
		generalConfig.isStop = false;
	}
}

void ZipperScanner::pbtn_IOTrigger_clicked()
{
	auto& _dlgIOTrigger = Modules::getInstance().uiModule._dlgIOTrigger;
	_dlgIOTrigger->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	// 计算居中位置
	QPoint center = this->geometry().center() - QPoint(_dlgIOTrigger->width() / 2, _dlgIOTrigger->height() / 2);
	_dlgIOTrigger->move(center);
	_dlgIOTrigger->exec();
}

void ZipperScanner::btn_shedingladaichangdu_clicked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	// 弹出数字键盘对话框
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		bool ok;
		double value = numKeyBord.getValue().toDouble(&ok);
		if (ok && value > 0)
		{
			generalConfig.shedingladaichangdu = value;
			ui->btn_shedingladaichangdu->setText(QString::number(value));
		}
		else
		{
			QMessageBox::warning(this, "Error", "请输入大于0的数值");
		}
	}
}

void ZipperScanner::pbtn_resetProduct_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto& statisticalInfo = Modules::getInstance().runtimeInfoModule.statisticalInfo;
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	generalConfig.produceLength = 0;
	generalConfig.punchCount = 0;
	ui->label_produceLength->setText(QString::number(generalConfig.produceLength, 'f', 2));
	ui->label_punchCount->setText(QString::number(generalConfig.punchCount));

	statisticalInfo.produceLength = 0;
	statisticalInfo.produceLengthBeforeStart = 0;
	statisticalInfo.punchCount = 0;
	bool isGet{false};
	auto isConnect = zmotion->getConnectState(isGet);
	if (isConnect&& isGet)
	{
		auto& globalData = GlobalData::getInstance();
		bool isGetLocation{false};
		auto location= zmotion->getAxisLocation(0, isGetLocation);
		if (isGetLocation)
		{
			globalData.startLocation = location;
		}
	}
}

void ZipperScanner::lb_title_clicked()
{
	if (0 != minimizeCount)
	{
		minimizeCount--;
	}
	else if (0 >= minimizeCount)
	{
		// 最小化主窗体
		this->showMinimized();

		auto& _dlgProductSet = Modules::getInstance().uiModule._dlgProductSet;
		auto& _dlgProductScore = Modules::getInstance().uiModule._dlgProductScore;

		// 最小化所有子窗体（如果已创建且可见）
		if (_dlgProductSet && _dlgProductSet->isVisible())
			_dlgProductSet->showMinimized();
		if (_dlgProductScore && _dlgProductScore->isVisible())
			_dlgProductScore->showMinimized();
		if (_picturesViewer && _picturesViewer->isVisible())
			_picturesViewer->showMinimized();
		if (_imageEnlargedDisplay && _imageEnlargedDisplay->isVisible())
			_imageEnlargedDisplay->showMinimized();

		minimizeCount = 3; // 重置最小化计数器
	}
}

void ZipperScanner::onCameraDisplay(QPixmap image, size_t index, bool isbad)
{
	if (index == 1)
	{
		if (!_isImageEnlargedDisplay)
		{
			imgDis1->setPixmap(image.scaled(imgDis1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			if (isbad)
			{
				imgNgDis1->setPixmap(image.scaled(imgNgDis1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
				_lastNgImage1 = image;
			}
			_lastImage1 = image;
		}
		else
		{
			if (0 == _currentImageEnlargedDisplayIndex)
			{
				_imageEnlargedDisplay->setShowImg(image);
			}
			if (isbad && 2 == _currentImageEnlargedDisplayIndex)
			{
				_imageEnlargedDisplay->setShowImg(image);
				_lastNgImage1 = image;
			}
			_lastImage1 = image;
		}
	}
	else if (index == 2)
	{
		if (!_isImageEnlargedDisplay)
		{
			imgDis2->setPixmap(image.scaled(imgDis2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
			if (isbad)
			{
				imgNgDis2->setPixmap(image.scaled(imgNgDis2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
				_lastNgImage2 = image;
			}
			_lastImage2 = image;
		}
		else
		{
			if (1 == _currentImageEnlargedDisplayIndex)
			{
				_imageEnlargedDisplay->setShowImg(image);
			}
			if (isbad && 3 == _currentImageEnlargedDisplayIndex)
			{
				_imageEnlargedDisplay->setShowImg(image);
				_lastNgImage2 = image;
			}
			_lastImage2 = image;
		}
	}
}

void ZipperScanner::getStartOrStopSignal(size_t index, bool state)
{
	if (index == ControlLines::qidonganniuIn)
	{
		if (state)
		{
			ui->rbtn_start->setChecked(true);
			rbtn_start_clicked(state);
			// 启动的时候记录当前位置
		}
		else
		{
			ui->rbtn_start->setChecked(false);
		}
	}
	else if (index == ControlLines::jitingIn)
	{
		if (state)
		{
			ui->rbtn_stop->setChecked(true);
			rbtn_stop_clicked(state);
		}
		else
		{
			ui->rbtn_stop->setChecked(false);
		}
	}
}

void ZipperScanner::imgDis1_clicked()
{
	if (!_lastImage1.isNull())
	{
		_imageEnlargedDisplay->setShowImg(_lastImage1);
	}
	else
	{
		_imageEnlargedDisplay->clearImgDis();
	}
	_currentImageEnlargedDisplayIndex = 0;
	_imageEnlargedDisplay->setGboxTitle(_workStationTitleMap[_currentImageEnlargedDisplayIndex]);
	_imageEnlargedDisplay->exec();
	refreshShowImages();
}

void ZipperScanner::imgDis2_clicked()
{
	if (!_lastImage2.isNull())
	{
		_imageEnlargedDisplay->setShowImg(_lastImage2);
	}
	else
	{
		_imageEnlargedDisplay->clearImgDis();
	}
	_currentImageEnlargedDisplayIndex = 1;
	_imageEnlargedDisplay->setGboxTitle(_workStationTitleMap[_currentImageEnlargedDisplayIndex]);
	_imageEnlargedDisplay->exec();
	refreshShowImages();
}

void ZipperScanner::imgNgDis1_clicked()
{
	if (!_lastNgImage1.isNull())
	{
		_imageEnlargedDisplay->setShowImg(_lastNgImage1);
	}
	else
	{
		_imageEnlargedDisplay->clearImgDis();
	}
	_currentImageEnlargedDisplayIndex = 2;
	_imageEnlargedDisplay->setGboxTitle(_workStationTitleMap[_currentImageEnlargedDisplayIndex]);
	_imageEnlargedDisplay->exec();
	refreshShowImages();
}

void ZipperScanner::imgNgDis2_clicked()
{
	if (!_lastNgImage2.isNull())
	{
		_imageEnlargedDisplay->setShowImg(_lastNgImage2);
	}
	else
	{
		_imageEnlargedDisplay->clearImgDis();
	}
	_currentImageEnlargedDisplayIndex = 3;
	_imageEnlargedDisplay->setGboxTitle(_workStationTitleMap[_currentImageEnlargedDisplayIndex]);
	_imageEnlargedDisplay->exec();
	refreshShowImages();
}

void ZipperScanner::refreshShowImages()
{
	if (!_lastImage1.isNull())
	{
		imgDis1->setPixmap(_lastImage1.scaled(imgDis1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if (!_lastImage2.isNull())
	{
		imgDis2->setPixmap(_lastImage2.scaled(imgDis2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if (!_lastNgImage1.isNull())
	{
		imgNgDis1->setPixmap(_lastNgImage1.scaled(imgNgDis1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	if (!_lastNgImage2.isNull())
	{
		imgNgDis2->setPixmap(_lastNgImage2.scaled(imgNgDis2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void ZipperScanner::build_ImageEnlargedDisplay()
{
	imgDis1 = new rw::rqw::ClickableLabel(this);
	imgDis1->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	imgDis2 = new rw::rqw::ClickableLabel(this);
	imgDis2->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	imgNgDis1 = new rw::rqw::ClickableLabel(this);
	imgNgDis1->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	imgNgDis2 = new rw::rqw::ClickableLabel(this);
	imgNgDis2->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

	ui->gBoix_ImageDisplay->layout()->replaceWidget(ui->label_imgDisplay_1, imgDis1);
	ui->gBoix_ImageDisplay->layout()->replaceWidget(ui->label_imgDisplay_3, imgDis2);
	ui->gBoix_ImageDisplay->layout()->replaceWidget(ui->label_imgDisplay_2, imgNgDis1);
	ui->gBoix_ImageDisplay->layout()->replaceWidget(ui->label_imgDisplay_4, imgNgDis2);

	delete ui->label_imgDisplay_1;
	delete ui->label_imgDisplay_3;
	delete ui->label_imgDisplay_2;
	delete ui->label_imgDisplay_4;

	QObject::connect(imgDis1, &rw::rqw::ClickableLabel::clicked
		, this, &ZipperScanner::imgDis1_clicked);
	QObject::connect(imgDis2, &rw::rqw::ClickableLabel::clicked
		, this, &ZipperScanner::imgDis2_clicked);
	QObject::connect(imgNgDis1, &rw::rqw::ClickableLabel::clicked
		, this, &ZipperScanner::imgNgDis1_clicked);
	QObject::connect(imgNgDis2, &rw::rqw::ClickableLabel::clicked
		, this, &ZipperScanner::imgNgDis2_clicked);

	_workStationTitleMap = {
		{0,"一号工位"},
		{1,"二号工位"},
		{2,"一号NG工位"},
		{3,"二号NG工位"}
	};

	_imageEnlargedDisplay = new ImageEnlargedDisplay(this);
	_imageEnlargedDisplay->setMonitorValue(&_isImageEnlargedDisplay);
	_imageEnlargedDisplay->setMonitorDisImgIndex(&_currentImageEnlargedDisplayIndex);
	_imageEnlargedDisplay->initWorkStationTitleMap(_workStationTitleMap);
	_imageEnlargedDisplay->setNum(2);
	_imageEnlargedDisplay->show();
	_imageEnlargedDisplay->close();
}

void ZipperScanner::destroy_ImageEnlargedDisplay()
{
	if (_imageEnlargedDisplay)
	{
		_imageEnlargedDisplay->close();
		delete _imageEnlargedDisplay;
		_imageEnlargedDisplay = nullptr;
	}
}

void ZipperScanner::onFinishProduce()
{
	if (!isSendProduceInfo)
	{
		rbtn_stop_clicked(true);
		ui->rbtn_stop->setChecked(true);
		isSendProduceInfo = true;
		QMessageBox::information(this, "提示", "已生产到设定的拉带长度,自动清零");
		pbtn_resetProduct_clicked();
		isSendProduceInfo = false;
	}
}

void ZipperScanner::onUpdateStatisticalInfo()
{
	auto& statisticalInfo = Modules::getInstance().runtimeInfoModule.statisticalInfo;
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	generalConfig.produceLength = statisticalInfo.produceLength + statisticalInfo.produceLengthBeforeStart.load();
	ui->label_produceLength->setText(QString::number(generalConfig.produceLength, 'f', 2));
	generalConfig.punchCount = statisticalInfo.punchCount;
	ui->label_punchCount->setText(QString::number(generalConfig.punchCount));
}

void ZipperScanner::shutdownComputerTrigger(int time)
{
	if (!_isConnnectCard)
	{
		return;
	}

	auto& _dlgShutdownWarn = Modules::getInstance().uiModule._dlgShutdownWarn;

	int shutDownBoundary = 7;
	if (time == -1)
	{
		_dlgShutdownWarn->close();
		return;
	}
	if (time == 0)
	{
		_dlgShutdownWarn->show();
		_dlgShutdownWarn->setTimeValue(shutDownBoundary - time);
		return;
	}

	_dlgShutdownWarn->setTimeValue((shutDownBoundary - time) % shutDownBoundary);

	if ((shutDownBoundary - time) == 0)
	{
		isShutdownByIO = true;
		this->close();
	}
}

void ZipperScanner::updateCameraLabelState(int cameraIndex, bool state)
{
	switch (cameraIndex)
	{
	case 0:
		if (state)
		{
			ui->label_cardState->setText("连接成功");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
		}
		else
		{
			ui->label_cardState->setText("连接失败");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
			rw::rqw::WarningInfo info;
			info.message = "运动控制器连接失败";
			info.type = rw::rqw::WarningType::Error;
			info.warningId = WarningId::cZMotionDisconnectAlarm;
			Modules::getInstance().warningModule.addWarning(info);
		}
		break;
	case 1:
		if (state) {
			ui->label_camera1State->setText("连接成功");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
		}
		else {
			ui->label_camera1State->setText("连接失败");
			ui->label_camera1State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
			rw::rqw::WarningInfo info;
			info.message = "相机1断连";
			info.type = rw::rqw::WarningType::Error;
			info.warningId = WarningId::ccameraDisconnectAlarm1;
			Modules::getInstance().warningModule.addWarning(info);
		}
		break;
	case 2:
		if (state) {
			ui->label_camera2State->setText("连接成功");
			ui->label_camera2State->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
		}
		else {
			ui->label_camera2State->setText("连接失败");
			ui->label_camera2State->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
			rw::rqw::WarningInfo info;
			info.message = "相机2断连";
			info.type = rw::rqw::WarningType::Error;
			info.warningId = WarningId::ccameraDisconnectAlarm2;
			Modules::getInstance().warningModule.addWarning(info);
		}
		break;
	default:
		break;
	}
}

