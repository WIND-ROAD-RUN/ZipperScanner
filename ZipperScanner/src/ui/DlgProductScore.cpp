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
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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

	QObject::connect(ui->ckb_extra1, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra1_checked);
	QObject::connect(ui->btn_extra1score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra1score_clicked);
	QObject::connect(ui->btn_extra1area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra1area_clicked);
	QObject::connect(ui->ckb_extra2, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra2_checked);
	QObject::connect(ui->btn_extra2score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra2score_clicked);
	QObject::connect(ui->btn_extra2area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra2area_clicked);
	QObject::connect(ui->ckb_extra3, &QCheckBox::clicked,
		this, &DlgProductScore::ckb_extra3_checked);
	QObject::connect(ui->btn_extra3score, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra3score_clicked);
	QObject::connect(ui->btn_extra3area, &QPushButton::clicked,
		this, &DlgProductScore::btn_extra3area_clicked);
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
	auto& GlobalStructData = GlobalStructDataZipper::getInstance();
	GlobalStructData.saveDlgProductScoreConfig();
	emit scoreFormClosed();
	this->close();
}

void DlgProductScore::ckb_queya_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.queYa = ui->ckb_queya->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_queyaarea->setText(value);
		globalStructScoreConfig.queYaArea = value.toDouble();
	}
}

void DlgProductScore::ckb_tangshang_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.tangShang = ui->ckb_tangshang->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_tangshangarea->setText(value);
		globalStructScoreConfig.tangShangArea = value.toDouble();
	}
}

void DlgProductScore::ckb_zangwu_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.zangWu = ui->ckb_zangwu->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_zangwuarea->setText(value);
		globalStructScoreConfig.zangWuArea = value.toDouble();
	}
}

void DlgProductScore::ckb_suoxiao_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.suoXiao = ui->ckb_suoxiao->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_suoxiaoarea->setText(value);
		globalStructScoreConfig.suoXiaoArea = value.toDouble();
	}
}

void DlgProductScore::ckb_extra1_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra1 = ui->ckb_extra1->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra1score_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra1score->setText(value);
		globalStructScoreConfig.extra1Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra1area_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra1area->setText(value);
		globalStructScoreConfig.extra1Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra2_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra2 = ui->ckb_extra2->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra2score_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra2score->setText(value);
		globalStructScoreConfig.extra2Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra2area_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra2area->setText(value);
		globalStructScoreConfig.extra2Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra3_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra3 = ui->ckb_extra3->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
}

void DlgProductScore::btn_extra3score_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra3score->setText(value);
		globalStructScoreConfig.extra3Score = value.toDouble();
	}
}

void DlgProductScore::btn_extra3area_clicked()
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra3area->setText(value);
		globalStructScoreConfig.extra3Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra4_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra4 = ui->ckb_extra4->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra4area->setText(value);
		globalStructScoreConfig.extra4Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra5_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra5 = ui->ckb_extra5->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra5area->setText(value);
		globalStructScoreConfig.extra5Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra6_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra6 = ui->ckb_extra6->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra6area->setText(value);
		globalStructScoreConfig.extra6Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra7_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra7 = ui->ckb_extra7->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra7area->setText(value);
		globalStructScoreConfig.extra7Area = value.toDouble();
	}
}

void DlgProductScore::ckb_extra8_checked()
{
	auto& globalScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
	globalScoreConfig.extra8 = ui->ckb_extra8->isChecked();
	GlobalStructDataZipper::getInstance().saveDlgProductScoreConfig();
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
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
		auto& globalStructScoreConfig = GlobalStructDataZipper::getInstance().scoreConfig;
		ui->btn_extra8area->setText(value);
		globalStructScoreConfig.extra8Area = value.toDouble();
	}
}




