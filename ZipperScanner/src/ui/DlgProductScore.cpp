#include "DlgProductScore.h"

#include <QMessageBox>

#include "GlobalStruct.hpp"
#include "Modules.hpp"
#include "NumberKeyboard.h"

DlgProductScore::DlgProductScore(QWidget* parent)
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
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	// 初始化参数

	// 缺牙
	ui->ckb_queya->setChecked(setConfig.queYa);
	ui->btn_queyascore->setText(QString::number(setConfig.queYaScore));
	ui->btn_queyaarea->setText(QString::number(setConfig.queYaArea));

	// 烫伤
	ui->ckb_tangshang->setChecked(setConfig.tangShang);
	ui->btn_tangshangscore->setText(QString::number(setConfig.tangShangScore));
	ui->btn_tangshangarea->setText(QString::number(setConfig.tangShangArea));

	// 脏污
	ui->ckb_zangwu->setChecked(setConfig.zangWu);
	ui->btn_zangwuscore->setText(QString::number(setConfig.zangWuScore));
	ui->btn_zangwuarea->setText(QString::number(setConfig.zangWuArea));

	// 缩小
	ui->ckb_suoxiao->setChecked(setConfig.suoXiao);
	ui->btn_suoxiaoscore->setText(QString::number(setConfig.suoXiaoScore));
	ui->btn_suoxiaoarea->setText(QString::number(setConfig.suoXiaoArea));

	// 花纹
	ui->ckb_huawen->setChecked(setConfig.huaWen);
	ui->btn_huawenscore->setText(QString::number(setConfig.huaWenScore));
	ui->btn_huawenarea->setText(QString::number(setConfig.huaWenArea));

	// 圆
	ui->ckb_yuan->setChecked(setConfig.yuan);
	ui->btn_yuanscore->setText(QString::number(setConfig.yuanScore));
	ui->btn_yuanarea->setText(QString::number(setConfig.yuanArea));

	// 划破
	ui->ckb_huapo->setChecked(setConfig.huaPo);
	ui->btn_huaposcore->setText(QString::number(setConfig.huaPoScore));
	ui->btn_huapoarea->setText(QString::number(setConfig.huaPoArea));

	// 额外4
	ui->ckb_duanxian->setChecked(setConfig.duanXian);
	ui->btn_duanxianscore->setText(QString::number(setConfig.duanXianScore));
	ui->btn_duanxianarea->setText(QString::number(setConfig.duanXianArea));

	// 额外5
	ui->ckb_extra5->setChecked(setConfig.extra5);
	ui->btn_extra5score->setText(QString::number(setConfig.extra5Score));
	ui->btn_extra5area->setText(QString::number(setConfig.extra5Area));

	// 额外6
	ui->ckb_extra6->setChecked(setConfig.extra6);
	ui->btn_extra6score->setText(QString::number(setConfig.extra6Score));
	ui->btn_extra6area->setText(QString::number(setConfig.extra6Area));

	// 额外7
	ui->ckb_extra7->setChecked(setConfig.extra7);
	ui->btn_extra7score->setText(QString::number(setConfig.extra7Score));
	ui->btn_extra7area->setText(QString::number(setConfig.extra7Area));

	// 额外8
	ui->ckb_extra8->setChecked(setConfig.extra8);
	ui->btn_extra8score->setText(QString::number(setConfig.extra8Score));
	ui->btn_extra8area->setText(QString::number(setConfig.extra8Area));
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
	QObject::connect(ui->ckb_duanxian, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_duanxian_checked);
	QObject::connect(ui->btn_duanxianscore, &QPushButton::clicked,
		this, &DlgProductScore::btn_duanxianscore_clicked);
	QObject::connect(ui->btn_duanxianarea, &QPushButton::clicked,
		this, &DlgProductScore::btn_duanxianarea_clicked);
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
	emit scoreFormClosed();
	this->close();
}

void DlgProductScore::ckb_queya_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.queYa = ui->ckb_queya->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;

		ui->btn_queyascore->setText(value);
		setConfig.queYaScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_queyaarea->setText(value);
		setConfig.queYaArea = value.toDouble();
	}
}

void DlgProductScore::ckb_tangshang_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.tangShang = ui->ckb_tangshang->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_tangshangscore->setText(value);
		setConfig.tangShangScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_tangshangarea->setText(value);
		setConfig.tangShangArea = value.toDouble();
	}
}

void DlgProductScore::ckb_zangwu_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.zangWu = ui->ckb_zangwu->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_zangwuscore->setText(value);
		setConfig.zangWuScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_zangwuarea->setText(value);
		setConfig.zangWuArea = value.toDouble();
	}
}

void DlgProductScore::ckb_suoxiao_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.suoXiao = ui->ckb_suoxiao->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_suoxiaoscore->setText(value);
		setConfig.suoXiaoScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_suoxiaoarea->setText(value);
		setConfig.suoXiaoArea = value.toDouble();
	}
}

void DlgProductScore::ckb_huawen_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.huaWen = ui->ckb_huawen->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_huawenscore->setText(value);
		setConfig.huaWenScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_huawenarea->setText(value);
		setConfig.huaWenArea = value.toDouble();
	}
}

void DlgProductScore::ckb_yuan_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.yuan = ui->ckb_yuan->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_yuanscore->setText(value);
		setConfig.yuanScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_yuanarea->setText(value);
		setConfig.yuanArea = value.toDouble();
	}
}

void DlgProductScore::ckb_huapo_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.huaPo = ui->ckb_huapo->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_huaposcore->setText(value);
		setConfig.huaPoScore = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_huapoarea->setText(value);
		setConfig.huaPoArea = value.toDouble();
	}
}

void DlgProductScore::ckb_duanxian_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.duanXian = ui->ckb_duanxian->isChecked();
}

void DlgProductScore::btn_duanxianscore_clicked()
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_duanxianscore->setText(value);
		setConfig.duanXianScore = value.toDouble();
	}
}

void DlgProductScore::btn_duanxianarea_clicked()
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_duanxianarea->setText(value);
		setConfig.duanXianArea = value.toDouble();
	}
}

void DlgProductScore::ckb_extra5_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.extra5 = ui->ckb_extra5->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra5score->setText(value);
		setConfig.extra5Score = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra5area->setText(value);
		setConfig.extra5Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra6_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.extra6 = ui->ckb_extra6->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra6score->setText(value);
		setConfig.extra6Score = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra6area->setText(value);
		setConfig.extra6Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra7_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.extra7 = ui->ckb_extra7->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra7score->setText(value);
		setConfig.extra7Score = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra7area->setText(value);
		setConfig.extra7Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra8_checked()
{
	auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
	setConfig.extra8 = ui->ckb_extra8->isChecked();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra8score->setText(value);
		setConfig.extra8Score = value.toDouble();
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
		auto& setConfig = Modules::getInstance().configManagerModule.scoreConfig;
		ui->btn_extra8area->setText(value);
		setConfig.extra8Area = value.toDouble();
	}
}