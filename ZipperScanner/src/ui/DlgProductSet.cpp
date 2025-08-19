#include "DlgProductSet.h"

#include <QMessageBox>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QButtonGroup>

#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"

DlgProductSet::DlgProductSet(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgProductSetClass())
{
	ui->setupUi(this);

	build_ui();

	build_connect();
}

DlgProductSet::~DlgProductSet()
{
	delete ui;
}

void DlgProductSet::build_ui()
{
	read_config();

	// 查看是否有相同的输入输出IO
	auto indicesDO = DOFindAllDuplicateIndices();
	setDOErrorInfo(indicesDO);
	auto indicesDI = DIFindAllDuplicateIndices();
	setDIErrorInfo(indicesDI);

	// 在构造函数或 build_ui/build_connect 中添加如下代码
	QButtonGroup* imageFormatGroup = new QButtonGroup(this);
	imageFormatGroup->addButton(ui->rbtn_saveBmp);
	imageFormatGroup->addButton(ui->rbtn_saveJpeg);
	imageFormatGroup->addButton(ui->rbtn_savePng);

	imageFormatGroup->setExclusive(true);
}

void DlgProductSet::read_config()
{
	auto& globalConfig = GlobalData::getInstance().setConfig;

	// 剔废时间
	ui->pbtn_tifeijuli1->setText(QString::number(globalConfig.tifeijuli1));
	ui->pbtn_tifeijuli2->setText(QString::number(globalConfig.tifeijuli2));

	// 采图
	ui->cBox_takeCamera1Pictures->setChecked(globalConfig.takeWork1Pictures);
	ui->cBox_takeCamera2Pictures->setChecked(globalConfig.takeWork2Pictures);

	// 存图
	ui->cBox_takeNgPictures->setChecked(globalConfig.saveNGImg);
	ui->cBox_takeMaskPictures->setChecked(globalConfig.saveMaskImg);
	ui->cBox_takeOkPictures->setChecked(globalConfig.saveOKImg);
	ui->btn_saveQuality->setText(QString::number(globalConfig.imgSaveQuality));
	ui->rbtn_saveBmp->setChecked(globalConfig.imgIsSaveBmp);
	ui->rbtn_saveJpeg->setChecked(globalConfig.imgIsSaveJpeg);
	ui->rbtn_savePng->setChecked(globalConfig.imgIsSavePng);


	// 一工位的限位与像素当量
	ui->pbtn_shangxianwei1->setText(QString::number(globalConfig.shangXianWei1));
	ui->pbtn_xiaxianwei1->setText(QString::number(globalConfig.xiaXianWei1));
	ui->pbtn_zuoxianwei1->setText(QString::number(globalConfig.zuoXianWei1));
	ui->pbtn_youxianwei1->setText(QString::number(globalConfig.youXianWei1));
	ui->pbtn_xiangsudangliang1->setText(QString::number(globalConfig.xiangSuDangLiang1));

	// 二工位的限位与像素当量
	ui->pbtn_shangxianwei2->setText(QString::number(globalConfig.shangXianWei2));
	ui->pbtn_xiaxianwei2->setText(QString::number(globalConfig.xiaXianWei2));
	ui->pbtn_zuoxianwei2->setText(QString::number(globalConfig.zuoXianWei2));
	ui->pbtn_youxianwei2->setText(QString::number(globalConfig.youXianWei2));
	ui->pbtn_xiangsudangliang2->setText(QString::number(globalConfig.xiangSuDangLiang2));

	// 光源
	ui->pbtn_qiangbaoguang->setText(QString::number(globalConfig.qiangBaoGuang));
	ui->pbtn_qiangzengyi->setText(QString::number(globalConfig.qiangZengYi));

	ui->pbtn_zhongbaoguang->setText(QString::number(globalConfig.zhongBaoGuang));
	ui->pbtn_zhongzengyi->setText(QString::number(globalConfig.zhongZengYi));

	ui->pbtn_ruobaoguang->setText(QString::number(globalConfig.ruoBaoGuang));
	ui->pbtn_ruozengyi->setText(QString::number(globalConfig.ruoZengYi));

	// 调试模式默认为关闭
	globalConfig.debugMode = false;
	ui->cbox_debugMode->setChecked(globalConfig.debugMode);

	// 基本功能
	ui->cbox_qiyongerxiangji->setChecked(globalConfig.qiyongerxiangji);
	ui->cbox_qiyongyundongkongzhiqi->setChecked(globalConfig.qiyongyundongkongzhiqi);
	ui->cbox_yundongkongzhiqichonglian->setChecked(globalConfig.yundongkongzhiqichonglian);

	// 基本参数
	ui->btn_xiangjichufachangdu->setText(QString::number(globalConfig.xiangjichufachangdu));
	ui->btn_yanshichongkong->setText(QString::number(globalConfig.yanshichongkong));
	ui->btn_chongkongshijian->setText(QString::number(globalConfig.chongkongshijian));
	ui->btn_yanshiziqi->setText(QString::number(globalConfig.yanshiziqi));
	ui->btn_jiajiansushijian->setText(QString::number(globalConfig.jiajiansushijian));
	ui->btn_shoudongsudu->setText(QString::number(globalConfig.shoudongsudu));
	ui->btn_meizhuanmaichongshu->setText(QString::number(globalConfig.meizhuanmaichongshu));
	ui->btn_zidongladaisudu->setText(QString::number(globalConfig.zidongladaisudu));
	ui->btn_shedingzhouchang->setText(QString::number(globalConfig.shedingzhouchang));

	// 设置IO
	ui->btn_setqidonganniu->setText(QString::number(globalConfig.qidonganniuIn));
	ui->btn_setlalianlawan->setText(QString::number(globalConfig.lalianlawanIn));
	ui->btn_setjiting->setText(QString::number(globalConfig.jitingIn));
	ui->btn_setchongkong->setText(QString::number(globalConfig.chongkongOut));
	ui->btn_settuoji->setText(QString::number(globalConfig.tuojiOut));
	ui->btn_guanji->setText(QString::number(globalConfig.guanjiIn));

	// 默认显示第一个
	ui->tabWidget->setCurrentIndex(0);

	// 分数界面内容可选显示
	ui->ckb_queya->setChecked(globalConfig.isQueya);
	ui->ckb_tangshang->setChecked(globalConfig.isTangshang);
	ui->ckb_zangwu->setChecked(globalConfig.isZangwu);
	ui->ckb_suoxiao->setChecked(globalConfig.isSuoxiao);

	ui->ckb_extra1->setChecked(globalConfig.isExtra1);
	ui->ckb_extra2->setChecked(globalConfig.isExtra2);
	ui->ckb_extra3->setChecked(globalConfig.isExtra3);
	ui->ckb_extra4->setChecked(globalConfig.isExtra4);
	ui->ckb_extra5->setChecked(globalConfig.isExtra5);
	ui->ckb_extra6->setChecked(globalConfig.isExtra6);
	ui->ckb_extra7->setChecked(globalConfig.isExtra7);
	ui->ckb_extra8->setChecked(globalConfig.isExtra8);

	//图像旋转次数
	ui->btn_rotateImgCount1->setText(QString::number(globalConfig.imgRotateCount1));
	ui->btn_rotateImgCount2->setText(QString::number(globalConfig.imgRotateCount2));

	GlobalData::getInstance().imgRotateCount1 = globalConfig.imgRotateCount1;
	GlobalData::getInstance().imgRotateCount2 = globalConfig.imgRotateCount2;
}

void DlgProductSet::build_connect()
{
	auto& globalStruct = GlobalData::getInstance();

	QObject::connect(ui->pbtn_tifeijuli1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_yanchitifeishijian1_clicked);
	QObject::connect(ui->pbtn_tifeijuli2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_yanchitifeishijian2_clicked);
	QObject::connect(ui->pbtn_shangxianwei1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_shangxianwei1_clicked);
	QObject::connect(ui->pbtn_xiaxianwei1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_xiaxianwei1_clicked);
	QObject::connect(ui->pbtn_zuoxianwei1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zuoxianwei1_clicked);
	QObject::connect(ui->pbtn_youxianwei1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_youxianwei1_clicked);
	QObject::connect(ui->pbtn_xiangsudangliang1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_xiangsudangliang1_clicked);
	QObject::connect(ui->pbtn_shangxianwei2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_shangxianwei2_clicked);
	QObject::connect(ui->pbtn_xiaxianwei2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_xiaxianwei2_clicked);
	QObject::connect(ui->pbtn_zuoxianwei2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zuoxianwei2_clicked);
	QObject::connect(ui->pbtn_youxianwei2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_youxianwei2_clicked);
	QObject::connect(ui->pbtn_xiangsudangliang2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_xiangsudangliang2_clicked);
	QObject::connect(ui->pbtn_qiangbaoguang, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangbaoguang_clicked);
	QObject::connect(ui->pbtn_qiangzengyi, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangzengyi_clicked);
	QObject::connect(ui->pbtn_zhongbaoguang, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongbaoguang_clicked);
	QObject::connect(ui->pbtn_ruobaoguang, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruobaoguang_clicked);
	QObject::connect(ui->pbtn_zhongzengyi, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongzengyi_clicked);
	QObject::connect(ui->pbtn_ruozengyi, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruozengyi_clicked);
	QObject::connect(ui->cbox_debugMode, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_debugMode_checked);
	QObject::connect(ui->pbtn_close, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_close_clicked);
	QObject::connect(ui->cBox_takeCamera1Pictures, &QCheckBox::clicked,
		this, &DlgProductSet::cBox_takeCamera1Pictures_checked);
	QObject::connect(ui->cBox_takeCamera2Pictures, &QCheckBox::clicked,
		this, &DlgProductSet::cBox_takeCamera2Pictures_checked);
	QObject::connect(ui->cbox_qiyongerxiangji, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_qiyongerxiangji_checked);
	QObject::connect(ui->cbox_qiyongyundongkongzhiqi, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_qiyongyundongkongzhiqi_checked);
	QObject::connect(ui->cbox_yundongkongzhiqichonglian, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_yundongkongzhiqichonglian_checked);

	// 基本参数
	QObject::connect(ui->btn_xiangjichufachangdu, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiangjichufachangdu_clicked);
	QObject::connect(ui->btn_shoudongladai, &QPushButton::pressed,
		this, &DlgProductSet::btn_shoudongladai_pressed);
	QObject::connect(ui->btn_shoudongladai, &QPushButton::released,
		this, &DlgProductSet::btn_shoudongladai_released);
	QObject::connect(ui->btn_shoudongchongkong, &QPushButton::clicked,
		this, &DlgProductSet::btn_shoudongchongkong_clicked);
	QObject::connect(ui->btn_tuoji, &QPushButton::clicked,
		this, &DlgProductSet::btn_tuoji_clicked);
	QObject::connect(ui->btn_xiangjichufa, &QPushButton::clicked,
		this, &DlgProductSet::btn_xiangjichufa_clicked);
	QObject::connect(ui->btn_shoudongsudu, &QPushButton::clicked,
		this, &DlgProductSet::btn_shoudongsudu_clicked);
	QObject::connect(ui->btn_meizhuanmaichongshu, &QPushButton::clicked,
		this, &DlgProductSet::btn_meizhuanmaichongshu_clicked);
	QObject::connect(ui->btn_zidongladaisudu, &QPushButton::clicked,
		this, &DlgProductSet::btn_zidongladaisudu_clicked);
	QObject::connect(ui->btn_shedingzhouchang, &QPushButton::clicked,
		this, &DlgProductSet::btn_shedingzhouchang_clicked);
	QObject::connect(ui->btn_yanshichongkong, &QPushButton::clicked,
		this, &DlgProductSet::btn_yanshichongkong_clicked);
	QObject::connect(ui->btn_chongkongshijian, &QPushButton::clicked,
		this, &DlgProductSet::btn_chongkongshijian_clicked);
	QObject::connect(ui->btn_yanshiziqi, &QPushButton::clicked,
		this, &DlgProductSet::btn_yanshiziqi_clicked);
	QObject::connect(ui->btn_jiajiansushijian, &QPushButton::clicked,
		this, &DlgProductSet::btn_jiajiansushijian_clicked);

	// 监控IO
	QObject::connect(ui->cbox_DIqidonganniu, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DIqidonganniu_clicked);
	QObject::connect(ui->cbox_DIjiting, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DIjiting_clicked);
	QObject::connect(ui->cbox_DIlalianlawan, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DIlalianlawan_clicked);
	QObject::connect(ui->cbox_DOchongkong, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOchongkong_clicked);
	QObject::connect(ui->cbox_DOtuoji, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOtuoji_clicked);
	QObject::connect(ui->cbox_DOchufapaizhao, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOchufapaizhao_clicked);
	QObject::connect(ui->tabWidget, &QTabWidget::currentChanged,
		this, &DlgProductSet::tabWidget_indexChanged);

	// 设置IO
	QObject::connect(ui->btn_setqidonganniu, &QPushButton::clicked,
		this, &DlgProductSet::btn_setqidonganniu_clicked);
	QObject::connect(ui->btn_setlalianlawan, &QPushButton::clicked,
		this, &DlgProductSet::btn_setlalianlawan_clicked);
	QObject::connect(ui->btn_setjiting, &QPushButton::clicked,
		this, &DlgProductSet::btn_setjiting_clicked);
	QObject::connect(ui->btn_setchongkong, &QPushButton::clicked,
		this, &DlgProductSet::btn_setchongkong_clicked);
	QObject::connect(ui->btn_settuoji, &QPushButton::clicked,
		this, &DlgProductSet::btn_settuoji_clicked);
	QObject::connect(ui->btn_guanji,&QPushButton::clicked,
		this, &DlgProductSet::btn_guanji_clicked);


	// 连接监控IO信号
	QObject::connect(&globalStruct, &GlobalData::emit_InPutSignal,
		this, &DlgProductSet::monitorInPutSignal);
	QObject::connect(&globalStruct, &GlobalData::emit_OutPutSignal,
		this, &DlgProductSet::monitorOutPutSignal);

	// 分数界面内容可选显示
	QObject::connect(ui->ckb_queya, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_queya_checked);
	QObject::connect(ui->ckb_tangshang, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_tangshang_checked);
	QObject::connect(ui->ckb_zangwu, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_zangwu_checked);
	QObject::connect(ui->ckb_suoxiao, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_suoxiao_checked);
	QObject::connect(ui->ckb_extra1, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra1_checked);
	QObject::connect(ui->ckb_extra2, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra2_checked);
	QObject::connect(ui->ckb_extra3, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra3_checked);
	QObject::connect(ui->ckb_extra4, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra4_checked);
	QObject::connect(ui->ckb_extra5, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra5_checked);
	QObject::connect(ui->ckb_extra6, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra6_checked);
	QObject::connect(ui->ckb_extra7, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra7_checked);
	QObject::connect(ui->ckb_extra8, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_extra8_checked);

	//存图
	QObject::connect(ui->cBox_takeNgPictures, &QCheckBox::clicked,
		this, &DlgProductSet::cBox_takeNgPictures_checked);
	QObject::connect(ui->cBox_takeMaskPictures, &QCheckBox::clicked,
		this, &DlgProductSet::cBox_takeMaskPictures_checked);
	QObject::connect(ui->cBox_takeOkPictures, &QCheckBox::clicked,
		this, &DlgProductSet::cBox_takeOkPictures_checked);
	// 存图质量
	QObject::connect(ui->btn_saveQuality, &QPushButton::clicked,
		this, &DlgProductSet::btn_saveQuality_clicked);
	// 存图格式
	QObject::connect(ui->rbtn_saveBmp, &QRadioButton::clicked,
		this, &DlgProductSet::rbtn_saveBmp_checked);
	QObject::connect(ui->rbtn_saveJpeg, &QRadioButton::clicked,
		this, &DlgProductSet::rbtn_saveJpeg_checked);
	QObject::connect(ui->rbtn_savePng, &QRadioButton::clicked,
		this, &DlgProductSet::rbtn_savePng_checked);

	// 图像旋转次数
	QObject::connect(ui->btn_rotateImgCount1, &QPushButton::clicked,
		this, &DlgProductSet::btn_rotateImgCount1_clicked);
	QObject::connect(ui->btn_rotateImgCount2, &QPushButton::clicked,
		this, &DlgProductSet::btn_rotateImgCount2_clicked);

}

std::vector<std::vector<int>> DlgProductSet::DOFindAllDuplicateIndices()
{
	auto& setConfig = GlobalData::getInstance().setConfig;
	std::vector<int> values = {
		setConfig.chongkongOut,
		setConfig.tuojiOut
	};

	std::unordered_map<int, std::vector<int>> valueToIndices;
	for (size_t i = 0; i < values.size(); ++i) {
		valueToIndices[values[i]].push_back(static_cast<int>(i));
	}

	std::vector<std::vector<int>> result;
	std::set<int> used; // 防止重复分组
	for (const auto& pair : valueToIndices) {
		if (pair.second.size() > 1) {
			// 只收集未被收录过的index组
			bool alreadyUsed = false;
			for (int idx : pair.second) {
				if (used.count(idx)) {
					alreadyUsed = true;
					break;
				}
			}
			if (!alreadyUsed) {
				result.push_back(pair.second);
				used.insert(pair.second.begin(), pair.second.end());
			}
		}
	}
	return result;
}

void DlgProductSet::setDIErrorInfo(const std::vector<std::vector<int>>& index)
{
	ui->lb_qidonganniu->clear();
	ui->lb_lalianlawan->clear();
	ui->lb_jiting->clear();
	ui->lb_guanji->clear();

	for (const auto& classic : index)
	{
		for (const auto& item : classic)
		{
			setDIErrorInfo(item);
		}
	}
}

void DlgProductSet::setDIErrorInfo(int index)
{
	QString text = "重复数值";
	switch (index)
	{
	case 0:
		ui->lb_qidonganniu->setText(text);
		break;
	case 1:
		ui->lb_lalianlawan->setText(text);
		break;
	case 2:
		ui->lb_jiting->setText(text);
		break;
	case 3:
		ui->lb_guanji->setText(text);
		break;
	}
}

void DlgProductSet::closeAllIOBtn()
{
	auto& globalStruct = GlobalData::getInstance();
	bool isChongKongSet = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, false);

	// 冲孔
	if (!isChongKongSet)
	{
		QMessageBox::warning(this, "警告", "手动冲孔失败!");
	}

	// 脱机
	bool isTuoJiSet = globalStruct.zmotion.setIOOut(ControlLines::tuojiOut, false);
	if (!isTuoJiSet)
	{
		QMessageBox::warning(this, "警告", "设置脱机失败!");
	}
}

void DlgProductSet::setDOErrorInfo(const std::vector<std::vector<int>>& index)
{
	ui->lb_chongkong->clear();
	ui->lb_tuoji->clear();

	for (const auto& classic : index)
	{
		for (const auto& item : classic)
		{
			setDOErrorInfo(item);
		}
	}
}

void DlgProductSet::setDOErrorInfo(int index)
{
	QString text = "重复数值";
	switch (index)
	{
	case 0:
		ui->lb_chongkong->setText(text);
		break;
	case 1:
		ui->lb_tuoji->setText(text);
		break;
	}
}

std::vector<std::vector<int>> DlgProductSet::DIFindAllDuplicateIndices()
{
	auto& setConfig = GlobalData::getInstance().setConfig;
	std::vector<int> values = {
		setConfig.qidonganniuIn,
		setConfig.lalianlawanIn,
		setConfig.jitingIn,
		setConfig.guanjiIn
	};

	std::unordered_map<int, std::vector<int>> valueToIndices;
	for (size_t i = 0; i < values.size(); ++i) {
		valueToIndices[values[i]].push_back(static_cast<int>(i));
	}

	std::vector<std::vector<int>> result;
	std::set<int> used; // 防止重复分组
	for (const auto& pair : valueToIndices) {
		if (pair.second.size() > 1) {
			// 只收集未被收录过的index组
			bool alreadyUsed = false;
			for (int idx : pair.second) {
				if (used.count(idx)) {
					alreadyUsed = true;
					break;
				}
			}
			if (!alreadyUsed) {
				result.push_back(pair.second);
				used.insert(pair.second.begin(), pair.second.end());
			}
		}
	}
	return result;
}

void DlgProductSet::pbtn_close_clicked()
{
	auto& GlobalStructData = GlobalData::getInstance();

	// 关闭所有可以点动的IO按钮
	closeAllIOBtn();

	// 关闭监控IO线程
	GlobalData::getInstance()._isUpdateMonitorInfo = false;
	GlobalData::getInstance().monitorZMotionMonitorThread.setRunning(false);

	GlobalStructData.saveDlgProductSetConfig();
	this->close();
}


void DlgProductSet::pbtn_yanchitifeishijian1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_tifeijuli1->setText(value);
		globalStructSetConfig.tifeijuli1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_yanchitifeishijian2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_tifeijuli2->setText(value);
		globalStructSetConfig.tifeijuli2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_shangxianwei1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_shangxianwei1->setText(value);
		globalStructSetConfig.shangXianWei1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_xiaxianwei1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_xiaxianwei1->setText(value);
		globalStructSetConfig.xiaXianWei1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_zuoxianwei1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_zuoxianwei1->setText(value);
		globalStructSetConfig.zuoXianWei1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_youxianwei1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_youxianwei1->setText(value);
		globalStructSetConfig.youXianWei1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_xiangsudangliang1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_xiangsudangliang1->setText(value);
		globalStructSetConfig.xiangSuDangLiang1 = value.toDouble();
		emit pixToWorldChanged();
	}
}

void DlgProductSet::pbtn_shangxianwei2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_shangxianwei2->setText(value);
		globalStructSetConfig.shangXianWei2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_xiaxianwei2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_xiaxianwei2->setText(value);
		globalStructSetConfig.xiaXianWei2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_zuoxianwei2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_zuoxianwei2->setText(value);
		globalStructSetConfig.zuoXianWei2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_youxianwei2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_youxianwei2->setText(value);
		globalStructSetConfig.youXianWei2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_xiangsudangliang2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
		ui->pbtn_xiangsudangliang2->setText(value);
		globalStructSetConfig.xiangSuDangLiang2 = value.toDouble();
		emit pixToWorldChanged();
	}
}

void DlgProductSet::pbtn_qiangbaoguang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 11 || value.toDouble() > 300)
		{
			QMessageBox::warning(this, "提示", "请输入11到300的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;

		ui->pbtn_qiangbaoguang->setText(value);
		globalStructSetConfig.qiangBaoGuang = value.toDouble();
		if (globalStructGeneralConfig.qiangGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setExposureTime(static_cast<size_t>(globalStructSetConfig.qiangBaoGuang));
			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setExposureTime(static_cast<size_t>(globalStructSetConfig.qiangBaoGuang));
			}
		}
	}
}

void DlgProductSet::pbtn_qiangzengyi_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 16)
		{
			QMessageBox::warning(this, "提示", "请输入0到16的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;
		ui->pbtn_qiangzengyi->setText(value);
		globalStructSetConfig.qiangZengYi = value.toDouble();
		if (globalStructGeneralConfig.qiangGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setGain(static_cast<size_t>(globalStructSetConfig.qiangZengYi));
			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setGain(static_cast<size_t>(globalStructSetConfig.qiangZengYi));
			}
		}
	}
}

void DlgProductSet::pbtn_zhongbaoguang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 11 || value.toDouble() > 300)
		{
			QMessageBox::warning(this, "提示", "请输入11到300的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;
		ui->pbtn_zhongbaoguang->setText(value);
		globalStructSetConfig.zhongBaoGuang = value.toDouble();
		if (globalStructGeneralConfig.zhongGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setExposureTime(static_cast<size_t>(globalStructSetConfig.zhongBaoGuang));
			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setExposureTime(static_cast<size_t>(globalStructSetConfig.zhongBaoGuang));
			}
		}
	}
}

void DlgProductSet::pbtn_ruobaoguang_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 11 || value.toDouble() > 300)
		{
			QMessageBox::warning(this, "提示", "请输入11到300的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;
		ui->pbtn_ruobaoguang->setText(value);
		globalStructSetConfig.ruoBaoGuang = value.toDouble();
		if (globalStructGeneralConfig.ruoGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setExposureTime(static_cast<size_t>(globalStructSetConfig.ruoBaoGuang));

			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setExposureTime(static_cast<size_t>(globalStructSetConfig.ruoBaoGuang));
			}
		}
	}
}

void DlgProductSet::pbtn_zhongzengyi_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 16)
		{
			QMessageBox::warning(this, "提示", "请输入0到16的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;
		ui->pbtn_zhongzengyi->setText(value);
		globalStructSetConfig.zhongZengYi = value.toDouble();
		if (globalStructGeneralConfig.zhongGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setGain(static_cast<size_t>(globalStructSetConfig.zhongZengYi));

			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setGain(static_cast<size_t>(globalStructSetConfig.zhongZengYi));
			}
		}
	}
}

void DlgProductSet::pbtn_ruozengyi_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 16)
		{
			QMessageBox::warning(this, "提示", "请输入0到16的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		auto& globalStructGeneralConfig = globalStruct.generalConfig;
		ui->pbtn_ruozengyi->setText(value);
		globalStructSetConfig.ruoZengYi = value.toDouble();
		if (globalStructGeneralConfig.ruoGuang == true)
		{
			if (globalStruct.camera1)
			{
				globalStruct.camera1->setGain(static_cast<size_t>(globalStructSetConfig.ruoZengYi));

			}
			if (globalStruct.camera2)
			{
				globalStruct.camera2->setGain(static_cast<size_t>(globalStructSetConfig.ruoZengYi));
			}
		}
	}
}

void DlgProductSet::cBox_takeNgPictures_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.saveNGImg = ui->cBox_takeNgPictures->isChecked();
}

void DlgProductSet::cBox_takeMaskPictures_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.saveMaskImg = ui->cBox_takeMaskPictures->isChecked();
}

void DlgProductSet::cBox_takeOkPictures_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.saveOKImg = ui->cBox_takeOkPictures->isChecked();
}

void DlgProductSet::cbox_debugMode_checked(bool ischecked)
{
	auto& isDebug = GlobalData::getInstance().setConfig.debugMode;
	auto& globalStruct = GlobalData::getInstance();
	isDebug = ischecked;
	isDebugIO = ischecked;
	if (isDebugIO)
	{
		ui->cbox_DIqidonganniu->setChecked(false);
		ui->cbox_DIjiting->setChecked(false);
		ui->cbox_DIlalianlawan->setChecked(false);
		ui->cbox_DObujindianjimaichong->setChecked(false);
		ui->cbox_DOchongkong->setChecked(false);
		ui->cbox_DOtuoji->setChecked(false);
		ui->cbox_DOchufapaizhao->setChecked(false);

		ui->cbox_DIqidonganniu->setEnabled(true);
		ui->cbox_DIjiting->setEnabled(true);
		ui->cbox_DIlalianlawan->setEnabled(true);
		ui->cbox_DObujindianjimaichong->setEnabled(true);
		ui->cbox_DOchongkong->setEnabled(true);
		ui->cbox_DOtuoji->setEnabled(true);
		ui->cbox_DOchufapaizhao->setEnabled(true);

		globalStruct.monitorZMotionMonitorThread.setRunning(false);
	}
	else
	{
		ui->cbox_DIqidonganniu->setChecked(false);
		ui->cbox_DIjiting->setChecked(false);
		ui->cbox_DIlalianlawan->setChecked(false);
		ui->cbox_DObujindianjimaichong->setChecked(false);
		ui->cbox_DOchongkong->setChecked(false);
		ui->cbox_DOtuoji->setChecked(false);
		ui->cbox_DOchufapaizhao->setChecked(false);

		ui->cbox_DIqidonganniu->setEnabled(false);
		ui->cbox_DIjiting->setEnabled(false);
		ui->cbox_DIlalianlawan->setEnabled(false);
		ui->cbox_DObujindianjimaichong->setEnabled(false);
		ui->cbox_DOchongkong->setEnabled(false);
		ui->cbox_DOtuoji->setEnabled(false);
		ui->cbox_DOchufapaizhao->setEnabled(false);

		globalStruct.monitorZMotionMonitorThread.setRunning(true);
	}
}

void DlgProductSet::cBox_takeCamera1Pictures_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.takeWork1Pictures = ui->cBox_takeCamera1Pictures->isChecked();
}

void DlgProductSet::cBox_takeCamera2Pictures_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.takeWork2Pictures = ui->cBox_takeCamera2Pictures->isChecked();
}

void DlgProductSet::rbtn_saveJpeg_checked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::JPEG);
	globalStructSetConfig.imgIsSaveJpeg = true;
	globalStructSetConfig.imgIsSavePng = false;
	globalStructSetConfig.imgIsSaveBmp = false;
}

void DlgProductSet::rbtn_savePng_checked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::PNG);
	globalStructSetConfig.imgIsSavePng = true;
	globalStructSetConfig.imgIsSaveJpeg = false;
	globalStructSetConfig.imgIsSaveBmp = false;
}

void DlgProductSet::rbtn_saveBmp_checked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	globalStruct.imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::BMP);
	globalStructSetConfig.imgIsSaveBmp = true;
	globalStructSetConfig.imgIsSaveJpeg = false;
	globalStructSetConfig.imgIsSavePng = false;
}

void DlgProductSet::btn_saveQuality_clicked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 30 || value.toDouble() > 100)
		{
			QMessageBox::warning(this, "提示", "请输入30到100的数值");
			return;
		}
		ui->btn_saveQuality->setText(value);
		globalStructSetConfig.imgSaveQuality = value.toInt();
		globalStruct.imageSaveEngine->setSaveImgQuality(globalStructSetConfig.imgSaveQuality);
	}
}

void DlgProductSet::cbox_qiyongerxiangji_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.qiyongerxiangji = ui->cbox_qiyongerxiangji->isChecked();
}

void DlgProductSet::cbox_qiyongyundongkongzhiqi_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.qiyongyundongkongzhiqi = ui->cbox_qiyongyundongkongzhiqi->isChecked();
}

void DlgProductSet::cbox_yundongkongzhiqichonglian_checked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.yundongkongzhiqichonglian = ui->cbox_yundongkongzhiqichonglian->isChecked();
}

void DlgProductSet::btn_xiangjichufachangdu_clicked()
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_xiangjichufachangdu->setText(value);
		globalStructSetConfig.xiangjichufachangdu = value.toDouble();
		bool isSet = globalStruct.zmotion.setModbus(4, 1, value.toFloat());

		if (!isSet)
		{
			QMessageBox::warning(this, "警告", "设定拉袋长度失败!");
		}
	}
}

void DlgProductSet::btn_shoudongladai_pressed()
{
	auto& globalStruct = GlobalData::getInstance();
	auto setConfig = globalStruct.setConfig;
	auto value = setConfig.meizhuanmaichongshu / setConfig.shedingzhouchang;

	// 启动电机
	auto isAxisType = globalStruct.zmotion.setAxisType(0, 1);
	double unit = value;
	auto isAxisPulse = globalStruct.zmotion.setAxisPulse(0, unit);
	double acc = setConfig.jiajiansushijian;
	auto isAxisAcc = globalStruct.zmotion.setAxisAcc(0, acc);
	auto isAxisDec = globalStruct.zmotion.setAxisDec(0, acc*2);
	double speed = setConfig.shoudongsudu;
	auto isAxisRunSpeed = globalStruct.zmotion.setAxisRunSpeed(0, speed);
	auto isAxisRun = globalStruct.zmotion.setAxisRun(0, -1);

	if (!isAxisType || !isAxisPulse || !isAxisAcc || !isAxisDec || !isAxisRunSpeed || !isAxisRun)
	{
		QMessageBox::warning(this, "警告", "电机参数设置失败");
	}
}

void DlgProductSet::btn_shoudongladai_released()
{
	auto& globalStruct = GlobalData::getInstance();
	// 停止电机
	bool isStop = globalStruct.zmotion.stopAllAxis();

	if (!isStop)
	{
		QMessageBox::warning(this, "警告", "手动拉带取消失败!");
	}
}

void DlgProductSet::btn_shoudongchongkong_clicked()
{
	auto future = QtConcurrent::run([this]() {
		auto& globalStruct = GlobalData::getInstance();
		auto chongkongshijian = globalStruct.setConfig.chongkongshijian;
		auto yanchichongkongshijian = globalStruct.setConfig.yanshichongkong;
		QThread::msleep(yanchichongkongshijian);
		bool isSet = globalStruct.zmotion.SetIOOut(2, ControlLines::chongkongOUT, true, chongkongshijian);

		if (!isSet) {
			QMetaObject::invokeMethod(this, [this]() {
				QMessageBox::warning(this, "警告", "手动冲孔失败!");
				}, Qt::QueuedConnection);
		}
		});
}

void DlgProductSet::btn_tuoji_clicked()
{
	auto& globalStruct = GlobalData::getInstance();

	bool isGetTuoJiOut = false;
	bool tuojiState = globalStruct.zmotion.getIOOut(ControlLines::tuojiOut, isGetTuoJiOut);
	bool isSuccess = globalStruct.zmotion.setIOOut(ControlLines::tuojiOut, !tuojiState);
	if (!isSuccess)
	{
		QMessageBox::warning(this, "警告", "设置脱机失败!");
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



void DlgProductSet::btn_xiangjichufa_clicked()
{

}

void DlgProductSet::btn_shoudongsudu_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_shoudongsudu->setText(value);
		globalStructSetConfig.shoudongsudu = value.toDouble();
	}
}

void DlgProductSet::btn_meizhuanmaichongshu_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_meizhuanmaichongshu->setText(value);
		globalStructSetConfig.meizhuanmaichongshu = value.toDouble();
	}
}

void DlgProductSet::btn_zidongladaisudu_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_zidongladaisudu->setText(value);
		globalStructSetConfig.zidongladaisudu = value.toDouble();
	}
}

void DlgProductSet::btn_shedingzhouchang_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_shedingzhouchang->setText(value);
		globalStructSetConfig.shedingzhouchang = value.toDouble();
	}
}

void DlgProductSet::btn_yanshichongkong_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_yanshichongkong->setText(value);
		globalStructSetConfig.yanshichongkong = value.toDouble();
	}
}

void DlgProductSet::btn_chongkongshijian_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_chongkongshijian->setText(value);
		globalStructSetConfig.chongkongshijian = value.toDouble();
	}
}

void DlgProductSet::btn_yanshiziqi_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_yanshiziqi->setText(value);
		globalStructSetConfig.yanshiziqi = value.toDouble();
	}
}

void DlgProductSet::btn_jiajiansushijian_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_jiajiansushijian->setText(value);
		globalStructSetConfig.jiajiansushijian = value.toDouble();
	}
}

void DlgProductSet::cbox_DIqidonganniu_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::qidonganniuIn, isChecked);
	}
}

void DlgProductSet::cbox_DIjiting_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::jitingIn, isChecked);
	}
}

void DlgProductSet::cbox_DIlalianlawan_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::lalianlawanIn, isChecked);
	}
}


void DlgProductSet::cbox_DOchongkong_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chongkongOUT, isChecked);
	}
}

void DlgProductSet::cbox_DOtuoji_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::tuojiOut, isChecked);
	}
}

void DlgProductSet::cbox_DOchufapaizhao_clicked(bool isChecked)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& globalStructSetConfig = globalStruct.setConfig;
	if (isDebugIO)
	{
		//auto isSuccess = globalStruct.zmotion.setIOOut(ControlLines::chufapaizhaoOUT, isChecked);
	}
}

void DlgProductSet::btn_setqidonganniu_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_setqidonganniu->setText(value);
		globalStructSetConfig.qidonganniuIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::btn_setlalianlawan_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_setlalianlawan->setText(value);
		globalStructSetConfig.lalianlawanIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::btn_setjiting_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_setjiting->setText(value);
		globalStructSetConfig.jitingIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::btn_setchongkong_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_setchongkong->setText(value);
		globalStructSetConfig.chongkongOut = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::btn_settuoji_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_settuoji->setText(value);
		globalStructSetConfig.tuojiOut = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::btn_guanji_clicked()
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toInt() < 0)
		{
			QMessageBox::warning(this, "提示", "请输入大于0的数值");
			return;
		}
		ui->btn_guanji->setText(value);
		globalStructSetConfig.guanjiIn = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
	}
}

void DlgProductSet::tabWidget_indexChanged(int index)
{
	auto& globalStruct = GlobalData::getInstance();
	auto& _isUpdateMonitorInfo = GlobalData::getInstance()._isUpdateMonitorInfo;
	switch (index) {
	case 0:
		_isUpdateMonitorInfo = false;
		globalStruct.monitorZMotionMonitorThread.setRunning(false);
		break;
	case 1:
		_isUpdateMonitorInfo = false;
		globalStruct.monitorZMotionMonitorThread.setRunning(false);
		break;
	case 2:
		_isUpdateMonitorInfo = true;
		globalStruct.monitorZMotionMonitorThread.setRunning(true);
		break;
	case 3:
		_isUpdateMonitorInfo = false;
		globalStruct.monitorZMotionMonitorThread.setRunning(false);
		break;
	default:
		_isUpdateMonitorInfo = false;
		globalStruct.monitorZMotionMonitorThread.setRunning(false);
		break;
	}
}

void DlgProductSet::monitorInPutSignal(size_t index, bool state)
{
	if (isDebugIO == false)
	{
		if (index == ControlLines::qidonganniuIn) // 启动按钮
		{
			if (state)
			{
				ui->cbox_DIqidonganniu->setChecked(true);
			}
			else
			{
				ui->cbox_DIqidonganniu->setChecked(false);
			}
		}
		else if (index == ControlLines::jitingIn) // 急停按钮
		{
			if (state)
			{
				ui->cbox_DIjiting->setChecked(true);
			}
			else
			{
				ui->cbox_DIjiting->setChecked(false);
			}
		}
		else if (index == ControlLines::lalianlawanIn) // 拉链拉完按钮
		{
			if (state)
			{
				ui->cbox_DIlalianlawan->setChecked(true);
			}
			else
			{
				ui->cbox_DIlalianlawan->setChecked(false);
			}
		}

	}

}

void DlgProductSet::monitorOutPutSignal(size_t index, bool state)
{
	if (isDebugIO == false)
	{
		if (index == ControlLines::chongkongOUT) // 冲孔按钮
		{
			if (state)
			{
				ui->cbox_DOchongkong->setChecked(true);
			}
			else
			{
				ui->cbox_DOchongkong->setChecked(false);
			}
		}
		else if (index == ControlLines::tuojiOut) // 脱机按钮
		{
			if (state)
			{
				ui->cbox_DOtuoji->setChecked(true);
			}
			else
			{
				ui->cbox_DOtuoji->setChecked(false);
			}
		}
	}
}

void DlgProductSet::ckb_queya_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isQueya = isChecked;
}

void DlgProductSet::ckb_tangshang_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isTangshang = isChecked;
}

void DlgProductSet::ckb_zangwu_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isZangwu = isChecked;
}

void DlgProductSet::ckb_suoxiao_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isSuoxiao = isChecked;
}

void DlgProductSet::ckb_extra1_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra1 = isChecked;
}

void DlgProductSet::ckb_extra2_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra2 = isChecked;
}

void DlgProductSet::ckb_extra3_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra3 = isChecked;
}

void DlgProductSet::ckb_extra4_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra4 = isChecked;
}

void DlgProductSet::ckb_extra5_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra5 = isChecked;
}

void DlgProductSet::ckb_extra6_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra6 = isChecked;
}

void DlgProductSet::ckb_extra7_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra7 = isChecked;
}

void DlgProductSet::ckb_extra8_checked(bool isChecked)
{
	auto& globalStructSetConfig = GlobalData::getInstance().setConfig;
	globalStructSetConfig.isExtra8 = isChecked;
}

void DlgProductSet::btn_rotateImgCount1_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 3)
		{
			QMessageBox::warning(this, "提示", "请输入0到3的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		ui->btn_rotateImgCount1->setText(value);
		globalStructSetConfig.imgRotateCount1 = value.toInt();
		globalStruct.imgRotateCount1 = value.toInt();
	}
}

void DlgProductSet::btn_rotateImgCount2_clicked()
{
	NumberKeyboard numKeyBord;
	numKeyBord.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	auto isAccept = numKeyBord.exec();
	if (isAccept == QDialog::Accepted)
	{
		auto value = numKeyBord.getValue();
		if (value.toDouble() < 0 || value.toDouble() > 3)
		{
			QMessageBox::warning(this, "提示", "请输入0到3的数值");
			return;
		}
		auto& globalStruct = GlobalData::getInstance();
		auto& globalStructSetConfig = globalStruct.setConfig;
		ui->btn_rotateImgCount2->setText(value);
		globalStructSetConfig.imgRotateCount2 = value.toInt();
		globalStruct.imgRotateCount2 = value.toInt();
	}
}







