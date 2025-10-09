#include "DlgWarningManager.h"

#include "Modules.hpp"
#include "ui_DlgWarningManager.h"

DlgWarningManager::DlgWarningManager(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgWarningManagerClass())
{
	ui->setupUi(this);
	this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
	build_ui();
	build_connect();
}

DlgWarningManager::~DlgWarningManager()
{
	delete ui;
}

void DlgWarningManager::build_connect()
{
	connect(ui->pbtn_exit, &QPushButton::clicked, this, &DlgWarningManager::pbtn_exit_clicked);
	connect(ui->cbox_cameraDisconnect1, &QCheckBox::clicked, this, &DlgWarningManager::cbox_cameraDisconnect1_clicked);
	connect(ui->cbox_cameraDisconnect2, &QCheckBox::clicked, this, &DlgWarningManager::cbox_cameraDisconnect2_clicked);
	connect(ui->cbox_lalianlawan, &QCheckBox::clicked, this, &DlgWarningManager::cbox_lalianlawan_clicked);
	connect(ui->cbox_zmotionDisconnect, &QCheckBox::clicked, this, &DlgWarningManager::cbox_zmotionDisconnect_clicked);
}

void DlgWarningManager::build_ui()
{
	auto& config = Modules::getInstance().configManagerModule.dlgWarningManagerConfig;
	ui->cbox_lalianlawan->setChecked(config.lalianlawan);
	ui->cbox_cameraDisconnect1->setChecked(config.yigongweixiangjiduanlian);
	ui->cbox_cameraDisconnect2->setChecked(config.ergongweixiangjiduanlian);
	ui->cbox_zmotionDisconnect->setChecked(config.zmotionduanlian);
}

void DlgWarningManager::pbtn_exit_clicked()
{
	this->close();
}

void DlgWarningManager::cbox_cameraDisconnect1_clicked(bool checked)
{
	auto& config = Modules::getInstance().configManagerModule.dlgWarningManagerConfig;
	config.yigongweixiangjiduanlian = checked;
}

void DlgWarningManager::cbox_cameraDisconnect2_clicked(bool checked)
{
	auto& config = Modules::getInstance().configManagerModule.dlgWarningManagerConfig;
	config.ergongweixiangjiduanlian = checked;
}

void DlgWarningManager::cbox_zmotionDisconnect_clicked(bool checked)
{
	auto& config = Modules::getInstance().configManagerModule.dlgWarningManagerConfig;
	config.zmotionduanlian = checked;
}

void DlgWarningManager::cbox_lalianlawan_clicked(bool checked)
{
	auto& config = Modules::getInstance().configManagerModule.dlgWarningManagerConfig;
	config.lalianlawan = checked;
}
