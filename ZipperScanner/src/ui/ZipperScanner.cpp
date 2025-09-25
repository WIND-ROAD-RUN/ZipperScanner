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
#include "Modules.hpp"

#ifdef BUILD_WITHOUT_HARDWARE
void ZipperScanner::cbox_testIfPushImg_clicked(bool states)
{
	GlobalThread::getInstance().testImgPush = states;
}

void ZipperScanner::sBox_pushImgTime_valueChanged(int value)
{
	auto& globalThread = GlobalThread::getInstance();
	if (globalThread.testImgPushThread)
	{
		globalThread.testImgPushThread->setPushImgTime(value);
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
	build_motion();

	//开机清零
	pbtn_resetProduct_clicked();

	// 构建UI
	build_ui();

	// 构建优先队列
	globalStruct.build_PriorityQueue();

	build_detachThread();

	build_DlgCloseForm();

	// 构建图像保存引擎
	build_imageSaveEngine();

	// 构建图片放大查看器
	build_ImageEnlargedDisplay();

	// 构建图像处理模块
	build_imageProcessorModule();

	// 连接相机
	build_camera();

	// 连接槽函数
	build_connect();

	// 启用所有后台线程
	start_Threads();

#ifdef BUILD_WITHOUT_HARDWARE
	auto& globalThread = GlobalThread::getInstance();
	_testIfPushImg = new QCheckBox(this);
	_testIfPushImg->setText("图像推送状态");
	ui->gBox_infor->layout()->addWidget(_testIfPushImg);
	QObject::connect(_testIfPushImg, &QCheckBox::clicked,
		this, &ZipperScanner::cbox_testIfPushImg_clicked);

	_pushImgTime = new QSpinBox(this);
	_pushImgTime->setRange(50, 2000);
	_pushImgTime->setSingleStep(50);
	_pushImgTime->setValue(150);
	ui->gBox_infor->layout()->addWidget(_pushImgTime);
	QObject::connect(_pushImgTime, &QSpinBox::valueChanged,
		this, &ZipperScanner::sBox_pushImgTime_valueChanged);


	globalThread.testImgPushThread = std::make_unique<TestImgPushThread>(this);
	QObject::connect(globalThread.testImgPushThread.get(), &TestImgPushThread::imgReady1,
		globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::onFrameCaptured);
	QObject::connect(globalThread.testImgPushThread.get(), &TestImgPushThread::imgReady2,
		globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::onFrameCaptured);

	globalThread.testImgPushThread->startThread();
#endif
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

void ZipperScanner::build_detachThread()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& detachUtiltyThread = Modules::getInstance().runtimeInfoModule.detachUtiltyThread;
	// 构建运动控制器IO状态监控线程
	globalStruct.build_MonitorZMotionIOStateThread();

	// 构建主窗体启停IO监控线程
	globalStruct.build_monitorStartOrStopThread();

	// 构建异步剔废线程
	globalStruct.build_DetachDefectThreadZipper();

	// 构建相机与板卡重连线程
	globalStruct.build_CameraAndCardStateThreadZipper();

	auto& globalThread = GlobalThread::getInstance();
	globalThread.buildDetachThread();

	QObject::connect(globalThread.monitorProduceLengthThread.get(), &MonitorProduceLengthThread::finishProduce,
		this, &ZipperScanner::onFinishProduce,Qt::BlockingQueuedConnection);
	QObject::connect(detachUtiltyThread.get(), &DetachUtiltyThread::updateStatisticalInfo,
		this, &ZipperScanner::onUpdateStatisticalInfo, Qt::QueuedConnection);
	QObject::connect(detachUtiltyThread.get(), &DetachUtiltyThread::shutdownComputer,
		this, &ZipperScanner::shutdownComputerTrigger, Qt::QueuedConnection);
}

void ZipperScanner::destory_detachThread()
{
	auto& globalStruct = GlobalData::getInstance();
	// 销毁主窗体启停IO监控线程
	globalStruct.destroy_monitorStartOrStopThread();
	// 销毁运动控制器IO状态监控线程
	globalStruct.destroy_MonitorZMotionIOStateThread();

	globalStruct.destroy_DetachDefectThreadZipper();

	auto& globalThread = GlobalThread::getInstance();
	globalThread.destroyDetachThread();
}

// 构建UI
void ZipperScanner::build_ui()
{
	build_ZipperScannerData();
	build_DlgProductSetData();
	ini_dlgProductSetCheckList();
	build_DlgProductScore();
	ini_dlgProductScoreGroupList();
	connectSetAndScore();
	build_DlgIOTrigger();
	_dlgShutdownWarn = new DlgShutdownWarn(this);

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

	// 连接显示NG图像
	QObject::connect(GlobalStructDataZipper.imageProcessingModule1.get(), &ImageProcessingModule::imageNGReady,
		this, &ZipperScanner::onCameraNGDisplay);
	QObject::connect(GlobalStructDataZipper.imageProcessingModule2.get(), &ImageProcessingModule::imageNGReady,
		this, &ZipperScanner::onCameraNGDisplay);

	// 连接UI更新
	QObject::connect(&GlobalStructDataZipper.getInstance(), &GlobalData::emit_updateUiLabels,
		this, &ZipperScanner::updateUiLabels);

	// 连接监控启停按钮
	QObject::connect(&GlobalStructDataZipper.getInstance(), &GlobalData::emit_StartOrStopSignal,
		this, &ZipperScanner::getStartOrStopSignal);

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
void ZipperScanner::build_camera()
{
	
}

void ZipperScanner::build_motion()
{
	auto& globalStruct = GlobalData::getInstance();
	globalStruct.zmotion.setIp("192.168.0.11");
	bool isConnected = globalStruct.zmotion.connect();
	_isConnnectCard = isConnected;
	if (isConnected)
	{
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto meizhuanmaichongshu = setConfig.meizhuanmaichongshu;
		auto shedingzhouchang = setConfig.shedingzhouchang;
		auto value = meizhuanmaichongshu / shedingzhouchang;

		bool isLocationZero = globalStruct.zmotion.setLocationZero(0);
		bool isAxisType = globalStruct.zmotion.setAxisType(0, 1);
		bool isAxisPulse = globalStruct.zmotion.setAxisPulse(0, value);

		bool isSetXiangJiChuFaChangDu = globalStruct.zmotion.setModbus(4, 1, setConfig.xiangjichufachangdu);
		bool isSetdangqianweizhi = globalStruct.zmotion.setModbus(2, 1, 0);
		 isSetdangqianweizhi = globalStruct.zmotion.setModbus(6, 1, 0);

		bool isOK = true;
		for (int i = 3; i < 13; i++)
		{
			isOK&& globalStruct.zmotion.setIOOut(i, false);
		}

		if (!isOK)
		{
			QMessageBox::warning(this, "警告", "初始化设置所有IO为false失败!");
		}

		if (!isLocationZero || !isAxisType || !isAxisPulse || !isSetXiangJiChuFaChangDu || !isSetdangqianweizhi)
		{
			QMessageBox::warning(this, "警告", "ZMotion参数设置失败!");
		}

		ui->label_cardState->setText("连接成功");
		ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
	}
	else
	{
		ui->label_cardState->setText("连接失败");
		ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
	}
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

	globalStruct.buildImageSaveEngine();

	// 初始化图像查看器
	_picturesViewer = new PictureViewerThumbnails(this);

	ini_clickableTitle();
}

// 通过实现DlgProductSet的构造函数进行初始化
void ZipperScanner::build_DlgProductSetData()
{
	_dlgProductSet = new DlgProductSet(this);
}

void ZipperScanner::ini_dlgProductSetCheckList()
{
	_dlgProductSetCheckList = {
		_dlgProductSet->ui->ckb_queya,
		_dlgProductSet->ui->ckb_tangshang,
		_dlgProductSet->ui->ckb_zangwu,
		_dlgProductSet->ui->ckb_suoxiao,
		_dlgProductSet->ui->ckb_huawen,
		_dlgProductSet->ui->ckb_yuan,
		_dlgProductSet->ui->ckb_huapo,
		_dlgProductSet->ui->ckb_duanxian,
		_dlgProductSet->ui->ckb_extra5,
		_dlgProductSet->ui->ckb_extra6,
		_dlgProductSet->ui->ckb_extra7,
		_dlgProductSet->ui->ckb_extra8
	};
}

// 通过实现DlgProductScore的构造函数进行初始化
void ZipperScanner::build_DlgProductScore()
{
	_dlgProductScore = new DlgProductScore(this);
}

void ZipperScanner::ini_dlgProductScoreGroupList()
{
	_dlgProductScoreGroupList = {
		_dlgProductScore->ui->widget_queya,
		_dlgProductScore->ui->widget_tangshang,
		_dlgProductScore->ui->widget_zangwu,
		_dlgProductScore->ui->widget_suoxiao,
		_dlgProductScore->ui->widget_huawen,
		_dlgProductScore->ui->widget_yuan,
		_dlgProductScore->ui->widget_huapo,
		_dlgProductScore->ui->widget_duanxian,
		_dlgProductScore->ui->widget_extra5,
		_dlgProductScore->ui->widget_extra6,
		_dlgProductScore->ui->widget_extra7,
		_dlgProductScore->ui->widget_extra8
	};
}

void ZipperScanner::connectSetAndScore()
{
	for (int i = 0; i < _dlgProductSetCheckList.size(); ++i) {
		connect(_dlgProductSetCheckList[i], &QCheckBox::toggled, _dlgProductScoreGroupList[i], &QWidget::setVisible);
		_dlgProductScoreGroupList[i]->setVisible(_dlgProductSetCheckList[i]->isChecked());
	}
}

void ZipperScanner::build_DlgIOTrigger()
{
	_dlgIOTrigger = new DlgIOTrigger(this);
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

void ZipperScanner::build_imageProcessorModule()
{
	auto& globalStruct = GlobalData::getInstance();

	QDir dir;

	QString enginePathFull = globalPath.modelPath;

	QFileInfo engineFile(enginePathFull);

	if (!engineFile.exists()) {
		QMessageBox::critical(this, "Error", "Engine file or Name file does not exist. The application will now exit.");
		QApplication::quit();
		return;
	}

	globalStruct.buildImageProcessorModules(enginePathFull);

	QObject::connect(globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::imageReady, this, &ZipperScanner::onCamera1Display);
	QObject::connect(globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::imageReady, this, &ZipperScanner::onCamera2Display);
	QObject::connect(this, &ZipperScanner::shibiekaungChanged, globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::shibiekaungChanged);
	QObject::connect(this, &ZipperScanner::shibiekaungChanged, globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::shibiekaungChanged);
	QObject::connect(this, &ZipperScanner::wenziChanged, globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::wenziChanged);
	QObject::connect(this, &ZipperScanner::wenziChanged, globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::wenziChanged);
	QObject::connect(_dlgProductScore, &DlgProductScore::scoreFormClosed,globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::paramMapsChanged);
	QObject::connect(_dlgProductScore, &DlgProductScore::scoreFormClosed,globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::paramMapsChanged);
	QObject::connect(_dlgProductSet, &DlgProductSet::pixToWorldChanged, globalStruct.imageProcessingModule1.get(), &ImageProcessingModule::paramMapsChanged);
	QObject::connect(_dlgProductSet, &DlgProductSet::pixToWorldChanged, globalStruct.imageProcessingModule2.get(), &ImageProcessingModule::paramMapsChanged);
}

void ZipperScanner::build_imageSaveEngine()
{
	QDir dir;
	QString imageSavePath = globalPath.imageSaveRootPath;
	//清理旧的数据

	//获取当前日期并设置保存路径
	QString currentDate = QDate::currentDate().toString("yyyy_MM_dd");
	auto& globalStruct = GlobalData::getInstance();
	globalStruct.buildImageSaveEngine();
	QString imageSaveEnginePath = imageSavePath + currentDate;

	QString imagesFilePathFilePathFull = dir.absoluteFilePath(imageSaveEnginePath);
	globalStruct.imageSaveEngine->setRootPath(imagesFilePathFilePathFull);

	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (setConfig.imgIsSaveJpeg)
	{
		globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::JPEG);
	}
	else if (setConfig.imgIsSavePng)
	{
		globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::PNG);
	}
	else if (setConfig.imgIsSaveBmp)
	{
		globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::BMP);
	}
	if (!setConfig.imgSaveQuality)
	{
		globalStruct.imageSaveEngine->setSaveImgQuality(80);
	}
	else
	{
		globalStruct.imageSaveEngine->setSaveImgQuality(setConfig.imgSaveQuality);
	}


	globalStruct.imageSaveEngine->startEngine();
}

void ZipperScanner::start_Threads()
{
	auto& globalStruct = GlobalData::getInstance();
	// 启动异步剔废线程
	globalStruct.detachDefectThreadZipper->startThread();
	// 启动相机重连线程
	globalStruct.cameraAndCardStateThreadZipper->startThread();

	auto& globalThread = GlobalThread::getInstance();
	globalThread.startDetachThread();
}

void ZipperScanner::build_DlgCloseForm()
{
	_dlgCloseForm = new DlgCloseForm(this);
}

void ZipperScanner::destroyComponents()
{
#ifdef BUILD_WITHOUT_HARDWARE
	auto& globalThread = GlobalThread::getInstance();
	globalThread.testImgPushThread->stopThread();
	globalThread.testImgPushThread.reset();
#endif
	auto& globalStructData = GlobalData::getInstance();
	// 关闭剔废功能并停止冲孔与轴运动
	rbtn_stop_clicked(true); // 默认停止
	rbtn_removeFunc_checked(false);

	destory_detachThread();
	// 销毁运动控制器
	globalStructData.destory_motion();
	// 销毁图像处理模块
	globalStructData.destroyImageProcessingModule();
	// 销毁图片放大查看器
	destroy_ImageEnlargedDisplay();
	// 销毁图像保存模块
	globalStructData.destroyImageSaveEngine();
	// 销毁剔废优先队列
	globalStructData.destroy_PriorityQueue();
}

void ZipperScanner::read_config()
{
	read_config_GeneralConfig();

	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	ControlLines::qidonganniuIn = setConfig.qidonganniuIn;
	ControlLines::jitingIn = setConfig.jitingIn;
	ControlLines::lalianlawanIn = setConfig.lalianlawanIn;
	ControlLines::guanjiIn = setConfig.guanjiIn;
	ControlLines::chongkongOUT = setConfig.chongkongOut;
	ControlLines::tuojiOut = setConfig.tuojiOut;
	ControlLines::xiangjichufaOut1 = setConfig.xiangjichufapaizhao1Out;
	ControlLines::xiangjichufaOut2 = setConfig.xiangjichufapaizhao2Out;
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
			_dlgProductSet->setFixedSize(this->width(), this->height());
			_dlgProductSet->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
			_dlgProductSet->exec();
		}
		else if (numKeyBord.getValue() == "6666")
		{
		}
		else {
			QMessageBox::warning(this, "Error", "密码错误，请重新输入");
		}
	}
}

void ZipperScanner::pbtn_score_clicked()
{
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
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	if (checked)
	{
		auto& globalStruct = GlobalData::getInstance();
		globalStruct.setLightLevel(LightLevel::StrongLight);
		generalConfig.zhongGuang = false;
		generalConfig.ruoGuang = false;
	}
	generalConfig.qiangGuang = ui->rbtn_strongLight->isChecked();
}

void ZipperScanner::rbtn_mediumLight_checked(bool checked)
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	if (checked)
	{
		auto& globalStruct = GlobalData::getInstance();
		globalStruct.setLightLevel(LightLevel::MediumLight);
		generalConfig.qiangGuang = false;
		generalConfig.ruoGuang = false;
	}
	generalConfig.zhongGuang = ui->rbtn_mediumLight->isChecked();
}

void ZipperScanner::rbtn_weakLight_checked(bool checked)
{
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	if (checked)
	{
		auto& globalStruct = GlobalData::getInstance();
		globalStruct.setLightLevel(LightLevel::WeakLight);
		generalConfig.qiangGuang = false;
		generalConfig.zhongGuang = false;
	}
	generalConfig.ruoGuang = ui->rbtn_weakLight->isChecked();
}

void ZipperScanner::pbtn_openSaveLocation_clicked()
{
	auto& globalStruct = GlobalData::getInstance();
	QString imageSavePath = globalStruct.imageSaveEngine->getRootPath();

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

	emit shibiekaungChanged();
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
	auto& globalStruct = GlobalData::getInstance();
	auto & globalThread= GlobalThread::getInstance();
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (checked)
	{
		generalConfig.isStart = true;
		generalConfig.isStop = false;

		// 启动电机
		auto value = setConfig.meizhuanmaichongshu / setConfig.shedingzhouchang;

		auto isAxisType = globalStruct.zmotion.setAxisType(0, 1);
		double unit = value;
		auto isAxisPulse = globalStruct.zmotion.setAxisPulse(0, unit);
		double acc = setConfig.jiajiansushijian;
		auto isAxisAcc = globalStruct.zmotion.setAxisAcc(0, acc);
		auto isAxisDec = globalStruct.zmotion.setAxisDec(0, acc * 2);
		double speed = setConfig.zidongladaisudu;
		auto isAxisRunSpeed = globalStruct.zmotion.setAxisRunSpeed(0, speed);
		auto isAxisRun = globalStruct.zmotion.setAxisRun(0, -1);

		//记录当前位置
		float nowLocation = 0;
		bool isget = false;
		nowLocation = GlobalData::getInstance().zmotion.getAxisLocation(0, isget);

		GlobalData::getInstance().startLocation = nowLocation;


		if (!isAxisType || !isAxisPulse || !isAxisAcc || !isAxisDec || !isAxisRunSpeed || !isAxisRun)
		{
			QMessageBox::warning(this, "警告", "电机参数设置失败");
		}
		changeRemoveFucState(true);

		globalThread.goToGetStartLocation = true;
	}
	else
	{
		generalConfig.isStart = false;
		generalConfig.isStop = true;

		// 停止电机
		bool isStop = globalStruct.zmotion.stopAllAxis();

		if (!isStop)
		{
			QMessageBox::warning(this, "警告", "停止电机取消失败!");
		}
		changeRemoveFucState(false);
	}
}

void ZipperScanner::rbtn_stop_clicked(bool checked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
	auto& globalThread = GlobalThread::getInstance();
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	if (checked)
	{
		changeRemoveFucState(false);
		ui->rbtn_stop->setChecked(checked);
		generalConfig.isStart = false;
		generalConfig.isStop = true;

		// 停止电机
		bool isStop = globalStruct.zmotion.stopAllAxis();

		// 停止冲孔
		isStop = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, false);

		globalThread.goToGetStopLocation = true;
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
	auto& globalStruct = GlobalData::getInstance();
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
	auto isConnect = globalStruct.zmotion.getConnectState(isGet);
	if (isConnect&& isGet)
	{
		auto& globalThread = GlobalThread::getInstance();
		bool isGetLocation{false};
		auto location= globalStruct.zmotion.getAxisLocation(0, isGetLocation);
		if (isGetLocation)
		{
			globalThread.startLocation = location;
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

void ZipperScanner::onCamera1Display(QPixmap image)
{
	if (!_isImageEnlargedDisplay)
	{
		imgDis1->setPixmap(image.scaled(imgDis1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else
	{
		if (0 == _currentImageEnlargedDisplayIndex) {
			_imageEnlargedDisplay->setShowImg(image);
		}
	}
	_lastImage1 = image;
}

void ZipperScanner::onCamera2Display(QPixmap image)
{
	if (!_isImageEnlargedDisplay)
	{
		imgDis2->setPixmap(image.scaled(imgDis2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else
	{
		if (1 == _currentImageEnlargedDisplayIndex) {
			_imageEnlargedDisplay->setShowImg(image);
		}
	}
	_lastImage2 = image;
}

void ZipperScanner::onCameraNGDisplay(QPixmap image, size_t index, bool isbad)
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

void ZipperScanner::updateUiLabels(int index, bool isConnected)
{
	switch (index)
	{
	case 0:
		_isConnnectCard = isConnected;
		if (isConnected)
		{
			ui->label_cardState->setText("连接成功");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(0, 230, 0);} "));
		}
		else
		{
			ui->label_cardState->setText("连接失败");
			ui->label_cardState->setStyleSheet(QString("QLabel{color:rgb(230, 0, 0);} "));
		}
		break;
	case 1:
		if (isConnected) {
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
			//labelWarning->addWarning(info);
		}
		break;
	case 2:
		if (isConnected) {
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
			//labelWarning->addWarning(info);
		}
		break;
	default:
		break;
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
			float nowLocation = 0;
			bool isget = false;
			nowLocation = GlobalData::getInstance().zmotion.getAxisLocation(0, isget);
			GlobalData::getInstance().startLocation = nowLocation;
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
			//labelWarning->addWarning(info);
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
			//labelWarning->addWarning(info);
		}
		break;
	default:
		break;
	}
}

