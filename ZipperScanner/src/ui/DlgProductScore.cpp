#include "DlgProductScore.h"

#include <QMessageBox>

#include "GlobalStruct.hpp"
#include "NumberKeyboard.h"

DlgProductScore::DlgProductScore(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgProductScoreClass())
{
	ui->setupUi(this);

	build_ui();

	build_connect();
}

DlgProductScore::~DlgProductScore()
{
	delete ui;
}

void DlgProductScore::build_ui()
{
	read_config();
}

void DlgProductScore::read_config()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	// 初始化参数

	// 缺牙
	ui->ckb_queya->setChecked(globalScoreConfig.queYa);
	ui->btn_queyascore->setText(QString::number(globalScoreConfig.queYaScore));
	ui->btn_queyaarea->setText(QString::number(globalScoreConfig.queYaArea));

	// 烫伤
	ui->ckb_tangshang->setChecked(globalScoreConfig.tangShang);
	ui->btn_tangshangscore->setText(QString::number(globalScoreConfig.tangShangScore));
	ui->btn_tangshangarea->setText(QString::number(globalScoreConfig.tangShangArea));

	// 脏污
	ui->ckb_zangwu->setChecked(globalScoreConfig.zangWu);
	ui->btn_zangwuscore->setText(QString::number(globalScoreConfig.zangWuScore));
	ui->btn_zangwuarea->setText(QString::number(globalScoreConfig.zangWuArea));

	// 缩小
	ui->ckb_suoxiao->setChecked(globalScoreConfig.suoXiao);
	ui->btn_suoxiaoscore->setText(QString::number(globalScoreConfig.suoXiaoScore));
	ui->btn_suoxiaoarea->setText(QString::number(globalScoreConfig.suoXiaoArea));

	// 花纹
	ui->ckb_huawen->setChecked(globalScoreConfig.huaWen);
	ui->btn_huawenscore->setText(QString::number(globalScoreConfig.huaWenScore));
	ui->btn_huawenarea->setText(QString::number(globalScoreConfig.huaWenArea));

	// 圆
	ui->ckb_yuan->setChecked(globalScoreConfig.yuan);
	ui->btn_yuanscore->setText(QString::number(globalScoreConfig.yuanScore));
	ui->btn_yuanarea->setText(QString::number(globalScoreConfig.yuanArea));

	// 划破
	ui->ckb_huapo->setChecked(globalScoreConfig.huaPo);
	ui->btn_huaposcore->setText(QString::number(globalScoreConfig.huaPoArea));
	ui->btn_huapoarea->setText(QString::number(globalScoreConfig.huaPoArea));

	// 额外4
	ui->ckb_extra4->setChecked(globalScoreConfig.extra4);
	ui->btn_extra4score->setText(QString::number(globalScoreConfig.extra4Score));
	ui->btn_extra4area->setText(QString::number(globalScoreConfig.extra4Area));

	// 额外5
	ui->ckb_extra5->setChecked(globalScoreConfig.extra5);
	ui->btn_extra5score->setText(QString::number(globalScoreConfig.extra5Score));
	ui->btn_extra5area->setText(QString::number(globalScoreConfig.extra5Area));

	// 额外6
	ui->ckb_extra6->setChecked(globalScoreConfig.extra6);
	ui->btn_extra6score->setText(QString::number(globalScoreConfig.extra6Score));
	ui->btn_extra6area->setText(QString::number(globalScoreConfig.extra6Area));

	// 额外7
	ui->ckb_extra7->setChecked(globalScoreConfig.extra7);
	ui->btn_extra7score->setText(QString::number(globalScoreConfig.extra7Score));
	ui->btn_extra7area->setText(QString::number(globalScoreConfig.extra7Area));

	// 额外8
	ui->ckb_extra8->setChecked(globalScoreConfig.extra8);
	ui->btn_extra8score->setText(QString::number(globalScoreConfig.extra8Score));
	ui->btn_extra8area->setText(QString::number(globalScoreConfig.extra8Area));
}

void DlgProductScore::build_connect()
{
	QObject::connect(ui->btn_close, &QPushButton::clicked,
		this, &DlgProductScore::btn_close_clicked);
	QObject::connect(ui->ckb_queya, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_queya_checked);
	QObject::connect(ui->btn_queyascore, &QPushButton::clicked,
		this, &DlgProductScore::btn_queyascore_clicked);
	QObject::connect(ui->btn_queyaarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_queyaarea_clicked);
	QObject::connect(ui->ckb_tangshang, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_tangshang_checked);
	QObject::connect(ui->btn_tangshangscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_tangshangscore_clicked);
	QObject::connect(ui->btn_tangshangarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_tangshangarea_clicked);
	QObject::connect(ui->ckb_zangwu, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_zangwu_checked);
	QObject::connect(ui->btn_zangwuscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_zangwuscore_clicked);
	QObject::connect(ui->btn_zangwuarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_zangwuarea_clicked);
	QObject::connect(ui->ckb_suoxiao, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_suoxiao_checked);
	QObject::connect(ui->btn_suoxiaoscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_suoxiaoscore_clicked);
	QObject::connect(ui->btn_suoxiaoarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_suoxiaoarea_clicked);

	QObject::connect(ui->ckb_huawen, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_huawen_checked);
	QObject::connect(ui->btn_huawenscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_huawenscore_clicked);
	QObject::connect(ui->btn_huawenarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_huawenarea_clicked);
	QObject::connect(ui->ckb_yuan, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_yuan_checked);
	QObject::connect(ui->btn_yuanscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_yuanscore_clicked);
	QObject::connect(ui->btn_yuanarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_yuanarea_clicked);
	QObject::connect(ui->ckb_huapo, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_huapo_checked);
	QObject::connect(ui->btn_huaposcore, &QPushButton::clicked,
		this, &DlgProductScore::btn_huaposcore_clicked);
	QObject::connect(ui->btn_huapoarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_huapoarea_clicked);
	QObject::connect(ui->ckb_extra4, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra4_checked);
	QObject::connect(ui->btn_extra4score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra4score_clicked);
	QObject::connect(ui->btn_extra4area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra4area_clicked);
	QObject::connect(ui->ckb_extra5, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra5_checked);
	QObject::connect(ui->btn_extra5score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra5score_clicked);
	QObject::connect(ui->btn_extra5area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra5area_clicked);
	QObject::connect(ui->ckb_extra6, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra6_checked);
	QObject::connect(ui->btn_extra6score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra6score_clicked);
	QObject::connect(ui->btn_extra6area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra6area_clicked);
	QObject::connect(ui->ckb_extra7, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra7_checked);
	QObject::connect(ui->btn_extra7score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra7score_clicked);
	QObject::connect(ui->btn_extra7area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra7area_clicked);
	QObject::connect(ui->ckb_extra8, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra8_checked);
	QObject::connect(ui->btn_extra8score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra8score_clicked);
	QObject::connect(ui->btn_extra8area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra8area_clicked);
}

void DlgProductScore::btn_close_clicked()
{
	auto& GlobalStructData = GlobalData::getInstance();
	GlobalStructData.saveDlgProductScoreConfig();
	emit scoreFormClosed();
	this->close();
}

void DlgProductScore::ckb_queya_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.queYa = ui->ckb_queya->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_queyascore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_queyascore->setText(value);
		globalStructScoreConfig.queYaScore = value.toDouble();
	}
}

void DlgProductScore::btn_queyaarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_queyaarea->setText(value);
		globalStructScoreConfig.queYaArea = value.toDouble();
	}
}

void DlgProductScore::ckb_tangshang_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.tangShang = ui->ckb_tangshang->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_tangshangscore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_tangshangscore->setText(value);
		globalStructScoreConfig.tangShangScore = value.toDouble();
	}
}

void DlgProductScore::btn_tangshangarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_tangshangarea->setText(value);
		globalStructScoreConfig.tangShangArea = value.toDouble();
	}
}

void DlgProductScore::ckb_zangwu_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.zangWu = ui->ckb_zangwu->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_zangwuscore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_zangwuscore->setText(value);
		globalStructScoreConfig.zangWuScore = value.toDouble();
	}
}

void DlgProductScore::btn_zangwuarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_zangwuarea->setText(value);
		globalStructScoreConfig.zangWuArea = value.toDouble();
	}
}

void DlgProductScore::ckb_suoxiao_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.suoXiao = ui->ckb_suoxiao->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_suoxiaoscore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_suoxiaoscore->setText(value);
		globalStructScoreConfig.suoXiaoScore = value.toDouble();
	}
}

void DlgProductScore::btn_suoxiaoarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_suoxiaoarea->setText(value);
		globalStructScoreConfig.suoXiaoArea = value.toDouble();
	}
}

void DlgProductScore::ckb_huawen_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.huaWen = ui->ckb_huawen->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_huawenscore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_huawenscore->setText(value);
		globalStructScoreConfig.huaWenScore = value.toDouble();
	}
}

void DlgProductScore::btn_huawenarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_huawenarea->setText(value);
		globalStructScoreConfig.huaWenArea = value.toDouble();
	}
}

void DlgProductScore::ckb_yuan_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.yuan = ui->ckb_yuan->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_yuanscore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_yuanscore->setText(value);
		globalStructScoreConfig.yuanScore = value.toDouble();
	}
}

void DlgProductScore::btn_yuanarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_yuanarea->setText(value);
		globalStructScoreConfig.yuanArea = value.toDouble();
	}
}

void DlgProductScore::ckb_huapo_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.huaPo = ui->ckb_huapo->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_huaposcore_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_huaposcore->setText(value);
		globalStructScoreConfig.huaPoScore = value.toDouble();
	}
}

void DlgProductScore::btn_huapoarea_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_huapoarea->setText(value);
		globalStructScoreConfig.huaPoArea = value.toDouble();
	}
}

void DlgProductScore::ckb_extra4_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.extra4 = ui->ckb_extra4->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra4score_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra4score->setText(value);
		globalStructScoreConfig.extra4Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra4area_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra4area->setText(value);
		globalStructScoreConfig.extra4Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra5_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.extra5 = ui->ckb_extra5->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra5score_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra5score->setText(value);
		globalStructScoreConfig.extra5Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra5area_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra5area->setText(value);
		globalStructScoreConfig.extra5Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra6_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.extra6 = ui->ckb_extra6->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra6score_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra6score->setText(value);
		globalStructScoreConfig.extra6Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra6area_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra6area->setText(value);
		globalStructScoreConfig.extra6Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra7_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.extra7 = ui->ckb_extra7->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra7score_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra7score->setText(value);
		globalStructScoreConfig.extra7Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra7area_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra7area->setText(value);
		globalStructScoreConfig.extra7Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra8_checked()
{
	auto& globalScoreConfig = GlobalData::getInstance().scoreConfig;
	globalScoreConfig.extra8 = ui->ckb_extra8->isChecked();
	GlobalData::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra8score_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra8score->setText(value);
		globalStructScoreConfig.extra8Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra8area_clicked()
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
		auto& globalStructScoreConfig = GlobalData::getInstance().scoreConfig;
		ui->btn_extra8area->setText(value);
		globalStructScoreConfig.extra8Area = value.toDouble();
	}
}




