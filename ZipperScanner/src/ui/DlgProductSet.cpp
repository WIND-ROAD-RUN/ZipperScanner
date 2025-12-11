#include "DlgProductSet.h"

#include <QMessageBox>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QButtonGroup>

#include "GlobalStruct.hpp"
#include "Modules.hpp"
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

	dlgWarningManager = new DlgWarningManager(this);

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

	//隐藏一些按钮
	ui->cbox_DOGreenLight_2->setVisible(false);
	ui->cbox_DOUpLight_2->setVisible(false);
	ui->cbox_DORedLight_2->setVisible(false);
	ui->cbox_DOUpLight_2->setVisible(false);

	ui->cbox_DICameraTrigger1_2->setVisible(false);
	ui->cbox_DICameraTrigger2_2->setVisible(false);
	ui->cbox_DICameraTrigger3_2->setVisible(false);
	ui->cbox_DICameraTrigger4_2->setVisible(false);
}

void DlgProductSet::read_config()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	// 剔废时间
	ui->pbtn_tifeijuli1->setText(QString::number(setConfig.tifeijuli1));
	ui->pbtn_tifeijuli2->setText(QString::number(setConfig.tifeijuli2));
	ui->pbtn_tifeirongyufangdou->setText(QString::number(setConfig.tifeirongyufangdou));

	// 采图
	ui->cBox_takeCamera1Pictures->setChecked(setConfig.takeWork1Pictures);
	ui->cBox_takeCamera2Pictures->setChecked(setConfig.takeWork2Pictures);

	// 存图
	ui->cBox_takeNgPictures->setChecked(setConfig.saveNGImg);
	ui->cBox_takeMaskPictures->setChecked(setConfig.saveMaskImg);
	ui->cBox_takeOkPictures->setChecked(setConfig.saveOKImg);
	ui->btn_saveQuality->setText(QString::number(setConfig.imgSaveQuality));
	ui->rbtn_saveBmp->setChecked(setConfig.imgIsSaveBmp);
	ui->rbtn_saveJpeg->setChecked(setConfig.imgIsSaveJpeg);
	ui->rbtn_savePng->setChecked(setConfig.imgIsSavePng);


	// 一工位的限位与像素当量
	ui->pbtn_shangxianwei1->setText(QString::number(setConfig.shangXianWei1));
	ui->pbtn_xiaxianwei1->setText(QString::number(setConfig.xiaXianWei1));
	ui->pbtn_zuoxianwei1->setText(QString::number(setConfig.zuoXianWei1));
	ui->pbtn_youxianwei1->setText(QString::number(setConfig.youXianWei1));
	ui->pbtn_xiangsudangliang1->setText(QString::number(setConfig.xiangSuDangLiang1));

	// 二工位的限位与像素当量
	ui->pbtn_shangxianwei2->setText(QString::number(setConfig.shangXianWei2));
	ui->pbtn_xiaxianwei2->setText(QString::number(setConfig.xiaXianWei2));
	ui->pbtn_zuoxianwei2->setText(QString::number(setConfig.zuoXianWei2));
	ui->pbtn_youxianwei2->setText(QString::number(setConfig.youXianWei2));
	ui->pbtn_xiangsudangliang2->setText(QString::number(setConfig.xiangSuDangLiang2));

	// 光源
	ui->pbtn_qiangbaoguang1->setText(QString::number(setConfig.qiangBaoGuang1));
	ui->pbtn_qiangzengyi1->setText(QString::number(setConfig.qiangZengYi1));
	ui->pbtn_zhongbaoguang1->setText(QString::number(setConfig.zhongBaoGuang1));
	ui->pbtn_zhongzengyi1->setText(QString::number(setConfig.zhongZengYi1));
	ui->pbtn_ruobaoguang1->setText(QString::number(setConfig.ruoBaoGuang1));
	ui->pbtn_ruozengyi1->setText(QString::number(setConfig.ruoZengYi1));

	ui->pbtn_qiangbaoguang2->setText(QString::number(setConfig.qiangBaoGuang2));
	ui->pbtn_qiangzengyi2->setText(QString::number(setConfig.qiangZengYi2));
	ui->pbtn_zhongbaoguang2->setText(QString::number(setConfig.zhongBaoGuang2));
	ui->pbtn_zhongzengyi2->setText(QString::number(setConfig.zhongZengYi2));
	ui->pbtn_ruobaoguang2->setText(QString::number(setConfig.ruoBaoGuang2));
	ui->pbtn_ruozengyi2->setText(QString::number(setConfig.ruoZengYi2));

	// 调试模式默认为关闭
	setConfig.debugMode = false;
	ui->cbox_debugMode->setChecked(setConfig.debugMode);

	// 基本功能
	ui->cbox_qiyongerxiangji->setChecked(setConfig.qiyongerxiangji);
	ui->cbox_qiyongyundongkongzhiqi->setChecked(setConfig.qiyongyundongkongzhiqi);
	ui->cbox_yundongkongzhiqichonglian->setChecked(setConfig.yundongkongzhiqichonglian);

	// 基本参数
	ui->btn_xiangjichufachangdu->setText(QString::number(setConfig.xiangjichufachangdu));
	ui->btn_yanshichongkong->setText(QString::number(setConfig.yanshichongkong));
	ui->btn_chongkongshijian->setText(QString::number(setConfig.chongkongshijian));
	ui->btn_yanshiziqi->setText(QString::number(setConfig.yanshiziqi));
	ui->btn_jiajiansushijian->setText(QString::number(setConfig.jiajiansushijian));
	ui->btn_shoudongsudu->setText(QString::number(setConfig.shoudongsudu));
	ui->btn_meizhuanmaichongshu->setText(QString::number(setConfig.meizhuanmaichongshu));
	ui->btn_zidongladaisudu->setText(QString::number(setConfig.zidongladaisudu));
	ui->btn_shedingzhouchang->setText(QString::number(setConfig.shedingzhouchang));

	// 设置IO
	ui->btn_setqidonganniu->setText(QString::number(setConfig.qidonganniuIn));
	ui->btn_setlalianlawan->setText(QString::number(setConfig.lalianlawanIn));
	ui->btn_setjiting->setText(QString::number(setConfig.jitingIn));
	ui->btn_setchongkong->setText(QString::number(setConfig.chongkongOut));
	ui->btn_settuoji->setText(QString::number(setConfig.tuojiOut));
	ui->btn_guanji->setText(QString::number(setConfig.guanjiIn));
	ui->btn_setxiangjichufa1->setText(QString::number(setConfig.xiangjichufapaizhao1Out));
	ui->btn_setxiangjichufa2->setText(QString::number(setConfig.xiangjichufapaizhao2Out));
	ui->btn_sethongdeng->setText(QString::number(setConfig.DOWarnRed));
	ui->btn_setlvdeng->setText(QString::number(setConfig.DOWarnGreen));

	// 默认显示第一个
	ui->tabWidget->setCurrentIndex(0);

	// 分数界面内容可选显示
	ui->ckb_queya->setChecked(setConfig.isQueya);
	ui->ckb_tangshang->setChecked(setConfig.isTangshang);
	ui->ckb_zangwu->setChecked(setConfig.isZangwu);
	ui->ckb_suoxiao->setChecked(setConfig.isSuoxiao);

	ui->ckb_huawen->setChecked(setConfig.isExtra1);
	ui->ckb_yuan->setChecked(setConfig.isExtra2);
	ui->ckb_huapo->setChecked(setConfig.isExtra3);
	ui->ckb_duanxian->setChecked(setConfig.isExtra4);
	ui->ckb_extra5->setChecked(setConfig.isExtra5);
	ui->ckb_extra6->setChecked(setConfig.isExtra6);
	ui->ckb_extra7->setChecked(setConfig.isExtra7);
	ui->ckb_extra8->setChecked(setConfig.isExtra8);

	//图像旋转次数
	ui->btn_rotateImgCount1->setText(QString::number(setConfig.imgRotateCount1));
	ui->btn_rotateImgCount2->setText(QString::number(setConfig.imgRotateCount2));
}

void DlgProductSet::build_connect()
{
	QObject::connect(ui->pbtn_tifeijuli1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_tifeijuli1_clicked);
	QObject::connect(ui->pbtn_tifeijuli2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_tifeijuli2_clicked);
	QObject::connect(ui->pbtn_tifeirongyufangdou, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_tifeirongyufangdou_clicked);
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
	QObject::connect(ui->pbtn_qiangbaoguang1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangbaoguang1_clicked);
	QObject::connect(ui->pbtn_qiangzengyi1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangzengyi1_clicked);
	QObject::connect(ui->pbtn_zhongbaoguang1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongbaoguang1_clicked);
	QObject::connect(ui->pbtn_ruobaoguang1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruobaoguang1_clicked);
	QObject::connect(ui->pbtn_zhongzengyi1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongzengyi1_clicked);
	QObject::connect(ui->pbtn_ruozengyi1, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruozengyi1_clicked);
	QObject::connect(ui->pbtn_qiangbaoguang2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangbaoguang2_clicked);
	QObject::connect(ui->pbtn_qiangzengyi2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_qiangzengyi2_clicked);
	QObject::connect(ui->pbtn_zhongbaoguang2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongbaoguang2_clicked);
	QObject::connect(ui->pbtn_ruobaoguang2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruobaoguang2_clicked);
	QObject::connect(ui->pbtn_zhongzengyi2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_zhongzengyi2_clicked);
	QObject::connect(ui->pbtn_ruozengyi2, &QPushButton::clicked,
		this, &DlgProductSet::pbtn_ruozengyi2_clicked);
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

	QObject::connect(ui->pbtn_warningForm, &QCheckBox::clicked,
		this, &DlgProductSet::pbtn_warningForm_clicked);

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
	QObject::connect(ui->cbox_DOchufapaizhao1, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOchufapaizhao1_clicked);
	QObject::connect(ui->cbox_DOchufapaizhao2, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOchufapaizhao2_clicked);
	QObject::connect(ui->tabWidget, &QTabWidget::currentChanged,
		this, &DlgProductSet::tabWidget_indexChanged);
	QObject::connect(ui->cbox_DOhongdeng, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOhongdeng_clicked);
	QObject::connect(ui->cbox_DOlvdeng, &QCheckBox::clicked,
		this, &DlgProductSet::cbox_DOlvdeng_clicked);

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
	QObject::connect(ui->btn_guanji, &QPushButton::clicked,
		this, &DlgProductSet::btn_guanji_clicked);
	QObject::connect(ui->btn_setxiangjichufa1, &QPushButton::clicked,
		this, &DlgProductSet::btn_setxiangjichufa1_clicked);
	QObject::connect(ui->btn_setxiangjichufa2, &QPushButton::clicked,
		this, &DlgProductSet::btn_setxiangjichufa2_clicked);
	QObject::connect(ui->btn_sethongdeng, &QPushButton::clicked,
		this, &DlgProductSet::btn_sethongdeng_clicked);
	QObject::connect(ui->btn_setlvdeng, &QPushButton::clicked,
		this, &DlgProductSet::btn_setlvdeng_clicked);


	// 分数界面内容可选显示
	QObject::connect(ui->ckb_queya, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_queya_checked);
	QObject::connect(ui->ckb_tangshang, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_tangshang_checked);
	QObject::connect(ui->ckb_zangwu, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_zangwu_checked);
	QObject::connect(ui->ckb_suoxiao, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_suoxiao_checked);
	QObject::connect(ui->ckb_huawen, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_huawen_checked);
	QObject::connect(ui->ckb_yuan, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_yuan_checked);
	QObject::connect(ui->ckb_huapo, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_huapo_checked);
	QObject::connect(ui->ckb_duanxian, &QCheckBox::clicked,
		this, &DlgProductSet::ckb_duanxian_checked);
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
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	std::vector<int> values = {
		setConfig.chongkongOut,
		setConfig.tuojiOut,
		setConfig.xiangjichufapaizhao1Out,
		setConfig.xiangjichufapaizhao2Out,
		setConfig.DOWarnRed,
		setConfig.DOWarnGreen
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
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	bool isChongKongSet = zmotion->setIOOut(ControlLines::chongkongOUT, false);

	// 冲孔
	if (!isChongKongSet)
	{
		//QMessageBox::warning(this, "警告", "手动冲孔失败!");
	}

	// 脱机
	bool isTuoJiSet = zmotion->setIOOut(ControlLines::tuojiOut, false);
	if (!isTuoJiSet)
	{
		//QMessageBox::warning(this, "警告", "设置脱机失败!");
	}
}

void DlgProductSet::setDOErrorInfo(const std::vector<std::vector<int>>& index)
{
	ui->lb_chongkong->clear();
	ui->lb_tuoji->clear();
	ui->lb_xiangjichufa1->clear();
	ui->lb_xiangjichufa2->clear();
	ui->lb_hongdeng->clear();
	ui->lb_lvdeng->clear();

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
	case 2:
		ui->lb_xiangjichufa1->setText(text);
		break;
	case 3:
		ui->lb_xiangjichufa2->setText(text);
		break;
	case 4:
		ui->lb_hongdeng->setText(text);
		break;
	case 5:
		ui->lb_lvdeng->setText(text);
		break;
	}
}

std::vector<std::vector<int>> DlgProductSet::DIFindAllDuplicateIndices()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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

void DlgProductSet::updateMonitorIOThread()
{
	auto& monitorStartOrStopThread = Modules::getInstance().motionControllerModule.monitorStartOrStopThread;
	auto& monitorZMotionMonitorThread = Modules::getInstance().motionControllerModule.monitorMotionIoStateThread;
	QVector<size_t> monitorIList = { ControlLines::qidonganniuIn,ControlLines::lalianlawanIn,ControlLines::jitingIn,ControlLines::guanjiIn };
	QVector<size_t> monitorOList = { ControlLines::chongkongOUT,ControlLines::tuojiOut,ControlLines::xiangjichufaOut1 ,ControlLines::xiangjichufaOut2,ControlLines::DOWarnRed,ControlLines::DOWarnGreen };
	monitorZMotionMonitorThread->setMonitorIList(monitorIList);
	monitorZMotionMonitorThread->setMonitorOList(monitorOList);

	QVector<size_t> monitorIList1 = { ControlLines::qidonganniuIn,ControlLines::jitingIn };
	monitorStartOrStopThread->setMonitorIList(monitorIList);
}

void DlgProductSet::pbtn_close_clicked()
{
	auto& monitorZMotionMonitorThread = Modules::getInstance().motionControllerModule.monitorMotionIoStateThread;
	auto& _isUpdateMonitorInfo = Modules::getInstance().motionControllerModule._isUpdateMonitorInfo;
	// 关闭所有可以点动的IO按钮
	closeAllIOBtn();

	// 关闭监控IO线程
	_isUpdateMonitorInfo = false;
	monitorZMotionMonitorThread->setRunning(false);

	cbox_debugMode_checked(false);

	this->close();
}

void DlgProductSet::pbtn_warningForm_clicked()
{
#ifdef NDEBUG
	dlgWarningManager->showFullScreen();
#else
	dlgWarningManager->show();
#endif
}


void DlgProductSet::pbtn_tifeijuli1_clicked()
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_tifeijuli1->setText(value);
		setConfig.tifeijuli1 = value.toDouble();
	}
}

void DlgProductSet::pbtn_tifeijuli2_clicked()
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_tifeijuli2->setText(value);
		setConfig.tifeijuli2 = value.toDouble();
	}
}

void DlgProductSet::pbtn_tifeirongyufangdou_clicked()
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_tifeirongyufangdou->setText(value);
		setConfig.tifeirongyufangdou = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_shangxianwei1->setText(value);
		setConfig.shangXianWei1 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_xiaxianwei1->setText(value);
		setConfig.xiaXianWei1 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_zuoxianwei1->setText(value);
		setConfig.zuoXianWei1 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_youxianwei1->setText(value);
		setConfig.youXianWei1 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_xiangsudangliang1->setText(value);
		setConfig.xiangSuDangLiang1 = value.toDouble();
		emit
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_shangxianwei2->setText(value);
		setConfig.shangXianWei2 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_xiaxianwei2->setText(value);
		setConfig.xiaXianWei2 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_zuoxianwei2->setText(value);
		setConfig.zuoXianWei2 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_youxianwei2->setText(value);
		setConfig.youXianWei2 = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->pbtn_xiangsudangliang2->setText(value);
		setConfig.xiangSuDangLiang2 = value.toDouble();
		emit
	}
}

void DlgProductSet::pbtn_qiangbaoguang1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;

		ui->pbtn_qiangbaoguang1->setText(value);
		setConfig.qiangBaoGuang1 = value.toDouble();
		if (generalConfig.qiangGuang == true)
		{
			if (camera1)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang1));
			}
		}
	}
}

void DlgProductSet::pbtn_qiangzengyi1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;
		ui->pbtn_qiangzengyi1->setText(value);
		setConfig.qiangZengYi1 = value.toDouble();
		if (generalConfig.qiangGuang == true)
		{
			if (camera1)
			{
				camera1->setGain(static_cast<size_t>(setConfig.qiangZengYi1));
			}
		}
	}
}

void DlgProductSet::pbtn_zhongbaoguang1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;
		ui->pbtn_zhongbaoguang1->setText(value);
		setConfig.zhongBaoGuang1 = value.toDouble();
		if (generalConfig.zhongGuang == true)
		{
			if (camera1)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang1));
			}
		}
	}
}

void DlgProductSet::pbtn_ruobaoguang1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;
		ui->pbtn_ruobaoguang1->setText(value);
		setConfig.ruoBaoGuang1 = value.toDouble();
		if (generalConfig.ruoGuang == true)
		{
			if (camera1)
			{
				camera1->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang1));

			}
		}
	}
}

void DlgProductSet::pbtn_zhongzengyi1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;
		ui->pbtn_zhongzengyi1->setText(value);
		setConfig.zhongZengYi1 = value.toDouble();
		if (generalConfig.zhongGuang == true)
		{
			if (camera1)
			{
				camera1->setGain(static_cast<size_t>(setConfig.zhongZengYi1));

			}
		}
	}
}

void DlgProductSet::pbtn_ruozengyi1_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera1 = Modules::getInstance().cameraModule.camera1;
		ui->pbtn_ruozengyi1->setText(value);
		setConfig.ruoZengYi1 = value.toDouble();
		if (generalConfig.ruoGuang == true)
		{
			if (camera1)
			{
				camera1->setGain(static_cast<size_t>(setConfig.ruoZengYi1));

			}
		}
	}
}

void DlgProductSet::pbtn_qiangbaoguang2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_qiangbaoguang2->setText(value);
		setConfig.qiangBaoGuang2 = value.toDouble();
		if (generalConfig.qiangGuang == true)
		{
			if (camera2)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.qiangBaoGuang2));
			}
		}
	}
}

void DlgProductSet::pbtn_qiangzengyi2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_qiangzengyi2->setText(value);
		setConfig.qiangZengYi2 = value.toDouble();
		if (generalConfig.qiangGuang == true)
		{
			if (camera2)
			{
				camera2->setGain(static_cast<size_t>(setConfig.qiangZengYi2));
			}
		}
	}
}

void DlgProductSet::pbtn_zhongbaoguang2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_zhongbaoguang2->setText(value);
		setConfig.zhongBaoGuang2 = value.toDouble();
		if (generalConfig.zhongGuang == true)
		{
			if (camera2)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.zhongBaoGuang2));
			}
		}
	}
}

void DlgProductSet::pbtn_ruobaoguang2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_ruobaoguang2->setText(value);
		setConfig.ruoBaoGuang2 = value.toDouble();
		if (generalConfig.ruoGuang == true)
		{
			if (camera2)
			{
				camera2->setExposureTime(static_cast<size_t>(setConfig.ruoBaoGuang2));
			}
		}
	}
}

void DlgProductSet::pbtn_zhongzengyi2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_zhongzengyi2->setText(value);
		setConfig.zhongZengYi2 = value.toDouble();
		if (generalConfig.zhongGuang == true)
		{
			if (camera2)
			{
				camera2->setGain(static_cast<size_t>(setConfig.zhongZengYi2));
			}
		}
	}
}

void DlgProductSet::pbtn_ruozengyi2_clicked()
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
		auto& generalConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto& camera2 = Modules::getInstance().cameraModule.camera2;
		ui->pbtn_ruozengyi2->setText(value);
		setConfig.ruoZengYi2 = value.toDouble();
		if (generalConfig.ruoGuang == true)
		{
			if (camera2)
			{
				camera2->setGain(static_cast<size_t>(setConfig.ruoZengYi2));
			}
		}
	}
}

void DlgProductSet::cBox_takeNgPictures_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.saveNGImg = ui->cBox_takeNgPictures->isChecked();
}

void DlgProductSet::cBox_takeMaskPictures_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.saveMaskImg = ui->cBox_takeMaskPictures->isChecked();
}

void DlgProductSet::cBox_takeOkPictures_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.saveOKImg = ui->cBox_takeOkPictures->isChecked();
}

void DlgProductSet::cbox_debugMode_checked(bool ischecked)
{
	auto& isDebug = Modules::getInstance().configManagerModule.setConfig.debugMode;
	auto& monitorZMotionMonitorThread = Modules::getInstance().motionControllerModule.monitorMotionIoStateThread;
	isDebug = ischecked;
	isDebugIO = ischecked;
	if (isDebugIO)
	{
		ui->cbox_DIqidonganniu->setEnabled(true);
		ui->cbox_DIjiting->setEnabled(true);
		ui->cbox_DIlalianlawan->setEnabled(true);
		ui->cbox_DObujindianjimaichong->setEnabled(true);
		ui->cbox_DOchongkong->setEnabled(true);
		ui->cbox_DOtuoji->setEnabled(true);
		ui->cbox_DOchufapaizhao1->setEnabled(true);
		ui->cbox_DOchufapaizhao2->setEnabled(true);
		ui->cbox_DOhongdeng->setEnabled(true);
		ui->cbox_DOlvdeng->setEnabled(true);

		monitorZMotionMonitorThread->setRunning(false);
	}
	else
	{
		ui->cbox_DIqidonganniu->setEnabled(false);
		ui->cbox_DIjiting->setEnabled(false);
		ui->cbox_DIlalianlawan->setEnabled(false);
		ui->cbox_DObujindianjimaichong->setEnabled(false);
		ui->cbox_DOchongkong->setEnabled(false);
		ui->cbox_DOtuoji->setEnabled(false);
		ui->cbox_DOchufapaizhao1->setEnabled(false);
		ui->cbox_DOchufapaizhao2->setEnabled(false);
		ui->cbox_DOhongdeng->setEnabled(false);
		ui->cbox_DOlvdeng->setEnabled(false);

		monitorZMotionMonitorThread->setRunning(true);
	}
}

void DlgProductSet::cBox_takeCamera1Pictures_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.takeWork1Pictures = ui->cBox_takeCamera1Pictures->isChecked();
}

void DlgProductSet::cBox_takeCamera2Pictures_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.takeWork2Pictures = ui->cBox_takeCamera2Pictures->isChecked();
}

void DlgProductSet::rbtn_saveJpeg_checked()
{
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::JPEG);
	setConfig.imgIsSaveJpeg = true;
	setConfig.imgIsSavePng = false;
	setConfig.imgIsSaveBmp = false;
}

void DlgProductSet::rbtn_savePng_checked()
{
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::PNG);
	setConfig.imgIsSavePng = true;
	setConfig.imgIsSaveJpeg = false;
	setConfig.imgIsSaveBmp = false;
}

void DlgProductSet::rbtn_saveBmp_checked()
{
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	imageSaveEngine->setSaveImgFormat(rw::rqw::ImageSaveFormat::BMP);
	setConfig.imgIsSaveBmp = true;
	setConfig.imgIsSaveJpeg = false;
	setConfig.imgIsSavePng = false;
}

void DlgProductSet::btn_saveQuality_clicked()
{
	auto& imageSaveEngine = Modules::getInstance().imgSaveModule.imageSaveEngine;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.imgSaveQuality = value.toInt();
		imageSaveEngine->setSaveImgQuality(setConfig.imgSaveQuality);
	}
}

void DlgProductSet::cbox_qiyongerxiangji_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.qiyongerxiangji = ui->cbox_qiyongerxiangji->isChecked();
}

void DlgProductSet::cbox_qiyongyundongkongzhiqi_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.qiyongyundongkongzhiqi = ui->cbox_qiyongyundongkongzhiqi->isChecked();
}

void DlgProductSet::cbox_yundongkongzhiqichonglian_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.yundongkongzhiqichonglian = ui->cbox_yundongkongzhiqichonglian->isChecked();
}

void DlgProductSet::btn_xiangjichufachangdu_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.xiangjichufachangdu = value.toDouble();
		bool isSet = zmotion->setModbus(4, 1, value.toFloat());

		if (!isSet)
		{
			QMessageBox::warning(this, "警告", "设定拉袋长度失败!");
		}
	}
}

void DlgProductSet::btn_shoudongladai_pressed()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	auto setConfig = Modules::getInstance().configManagerModule.setConfig;
	auto value = setConfig.meizhuanmaichongshu / setConfig.shedingzhouchang;

	// 启动电机
	auto isAxisType = zmotion->setAxisType(0, 1);
	double unit = value;
	auto isAxisPulse = zmotion->setAxisPulse(0, unit);
	double acc = setConfig.jiajiansushijian;
	auto isAxisAcc = zmotion->setAxisAcc(0, acc);
	auto isAxisDec = zmotion->setAxisDec(0, acc * 2);
	double speed = setConfig.shoudongsudu;
	auto isAxisRunSpeed = zmotion->setAxisRunSpeed(0, speed);
	auto isAxisRun = zmotion->setAxisRun(0, -1);

	if (!isAxisType || !isAxisPulse || !isAxisAcc || !isAxisDec || !isAxisRunSpeed || !isAxisRun)
	{
		QMessageBox::warning(this, "警告", "电机参数设置失败");
	}
}

void DlgProductSet::btn_shoudongladai_released()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	// 停止电机
	bool isStop = zmotion->stopAllAxis();

	if (!isStop)
	{
		QMessageBox::warning(this, "警告", "手动拉带取消失败!");
	}
}

void DlgProductSet::btn_shoudongchongkong_clicked()
{
	auto future = QtConcurrent::run([this]() {
		auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		auto chongkongshijian = setConfig.chongkongshijian * 1000;
		auto yanchichongkongshijian = setConfig.yanshichongkong * 1000;
		QThread::msleep(yanchichongkongshijian);
		bool isSet = zmotion->SetIOOut(2, ControlLines::chongkongOUT, true, chongkongshijian);

		if (!isSet) {
			QMetaObject::invokeMethod(this, [this]() {
				QMessageBox::warning(this, "警告", "手动冲孔失败!");
				}, Qt::QueuedConnection);
		}
		});
}

void DlgProductSet::btn_tuoji_clicked()
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	bool isGetTuoJiOut = false;
	bool tuojiState = zmotion->getIOOut(ControlLines::tuojiOut, isGetTuoJiOut);
	bool isSuccess = zmotion->setIOOut(ControlLines::tuojiOut, !tuojiState);
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
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.shoudongsudu = value.toDouble();
	}
}

void DlgProductSet::btn_meizhuanmaichongshu_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.meizhuanmaichongshu = value.toDouble();
	}
}

void DlgProductSet::btn_zidongladaisudu_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.zidongladaisudu = value.toDouble();
	}
}

void DlgProductSet::btn_shedingzhouchang_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.shedingzhouchang = value.toDouble();
	}
}

void DlgProductSet::btn_yanshichongkong_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.yanshichongkong = value.toDouble();
	}
}

void DlgProductSet::btn_chongkongshijian_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.chongkongshijian = value.toDouble();
	}
}

void DlgProductSet::btn_yanshiziqi_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.yanshiziqi = value.toDouble();
	}
}

void DlgProductSet::btn_jiajiansushijian_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		setConfig.jiajiansushijian = value.toDouble();
	}
}

void DlgProductSet::cbox_DIqidonganniu_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::qidonganniuIn, isChecked);
	}
}

void DlgProductSet::cbox_DIjiting_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::jitingIn, isChecked);
	}
}

void DlgProductSet::cbox_DIlalianlawan_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::lalianlawanIn, isChecked);
	}
}


void DlgProductSet::cbox_DOchongkong_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::chongkongOUT, isChecked);
	}
}

void DlgProductSet::cbox_DOtuoji_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::tuojiOut, isChecked);
	}
}

void DlgProductSet::cbox_DOchufapaizhao1_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		bool isXiangJiChuFaSet = zmotion->SetIOOut(3, ControlLines::xiangjichufaOut1, true, 100);
		ui->cbox_DOchufapaizhao1->setChecked(false);
	}
}

void DlgProductSet::cbox_DOchufapaizhao2_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		bool isXiangJiChuFaSet = zmotion->SetIOOut(3, ControlLines::xiangjichufaOut2, true, 100);
		ui->cbox_DOchufapaizhao2->setChecked(false);
	}
}

void DlgProductSet::cbox_DOhongdeng_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::DOWarnRed, isChecked);
	}
}

void DlgProductSet::cbox_DOlvdeng_clicked(bool isChecked)
{
	auto& zmotion = Modules::getInstance().motionControllerModule.zmotion;
	if (isDebugIO)
	{
		auto isSuccess = zmotion->setIOOut(ControlLines::DOWarnGreen, isChecked);
	}
}

void DlgProductSet::btn_setqidonganniu_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::qidonganniuIn = value.toInt();
		setConfig.qidonganniuIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setlalianlawan_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::lalianlawanIn = value.toInt();
		setConfig.lalianlawanIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setjiting_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::jitingIn = value.toInt();
		setConfig.jitingIn = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setchongkong_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::chongkongOUT = value.toInt();
		setConfig.chongkongOut = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_settuoji_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::tuojiOut = value.toInt();
		setConfig.tuojiOut = value.toDouble();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_guanji_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ControlLines::guanjiIn = value.toInt();
		setConfig.guanjiIn = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setxiangjichufa1_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ui->btn_setxiangjichufa1->setText(value);
		ControlLines::xiangjichufaOut1 = value.toInt();
		setConfig.xiangjichufapaizhao1Out = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setxiangjichufa2_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ui->btn_setxiangjichufa2->setText(value);
		ControlLines::xiangjichufaOut2 = value.toInt();
		setConfig.xiangjichufapaizhao2Out = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_sethongdeng_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ui->btn_sethongdeng->setText(value);
		ControlLines::DOWarnRed = value.toInt();
		setConfig.DOWarnRed = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::btn_setlvdeng_clicked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
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
		ui->btn_setlvdeng->setText(value);
		ControlLines::DOWarnGreen = value.toInt();
		setConfig.DOWarnGreen = value.toInt();
		auto indicesDO = DOFindAllDuplicateIndices();
		setDOErrorInfo(indicesDO);
		auto indicesDI = DIFindAllDuplicateIndices();
		setDIErrorInfo(indicesDI);
		updateMonitorIOThread();
	}
}

void DlgProductSet::tabWidget_indexChanged(int index)
{
	auto& monitorZMotionMonitorThread = Modules::getInstance().motionControllerModule.monitorMotionIoStateThread;
	auto& _isUpdateMonitorInfo = Modules::getInstance().motionControllerModule._isUpdateMonitorInfo;
	switch (index) {
	case 2:
		_isUpdateMonitorInfo = true;
		monitorZMotionMonitorThread->setRunning(true);
		break;
	default:
		_isUpdateMonitorInfo = false;
		monitorZMotionMonitorThread->setRunning(false);
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
		else if (index == ControlLines::guanjiIn) // 拉链拉完按钮
		{
			if (state)
			{
				ui->cbox_DIguanji->setChecked(true);
			}
			else
			{
				ui->cbox_DIguanji->setChecked(false);
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
		else if (index == ControlLines::xiangjichufaOut1) // 脱机按钮
		{
			if (state)
			{
				ui->cbox_DOchufapaizhao1->setChecked(true);
			}
			else
			{
				ui->cbox_DOchufapaizhao1->setChecked(false);
			}
		}
		else if (index == ControlLines::xiangjichufaOut2) // 脱机按钮
		{
			if (state)
			{
				ui->cbox_DOchufapaizhao2->setChecked(true);
			}
			else
			{
				ui->cbox_DOchufapaizhao2->setChecked(false);
			}
		}
	}
}

void DlgProductSet::ckb_queya_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isQueya = isChecked;
}

void DlgProductSet::ckb_tangshang_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isTangshang = isChecked;
}

void DlgProductSet::ckb_zangwu_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isZangwu = isChecked;
}

void DlgProductSet::ckb_suoxiao_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isSuoxiao = isChecked;
}

void DlgProductSet::ckb_huawen_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra1 = isChecked;
}

void DlgProductSet::ckb_yuan_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra2 = isChecked;
}

void DlgProductSet::ckb_huapo_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra3 = isChecked;
}

void DlgProductSet::ckb_duanxian_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra4 = isChecked;
}

void DlgProductSet::ckb_extra5_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra5 = isChecked;
}

void DlgProductSet::ckb_extra6_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra6 = isChecked;
}

void DlgProductSet::ckb_extra7_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra7 = isChecked;
}

void DlgProductSet::ckb_extra8_checked(bool isChecked)
{
	auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
	setConfig.isExtra8 = isChecked;
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->btn_rotateImgCount1->setText(value);
		setConfig.imgRotateCount1 = value.toInt();
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
		auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
		ui->btn_rotateImgCount2->setText(value);
		setConfig.imgRotateCount2 = value.toInt();
	}
}
