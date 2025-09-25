#include "UIModule.hpp"

#include "DlgCloseForm.h"
#include "DlgIOTrigger.h"
#include "DlgProductSet.h"
#include "DlgProductScore.h"
#include "DlgShutdownWarn.h"
#include "rqw_LabelWarning.h"
#include "ui_DlgProductScore.h"
#include "ui_DlgProductSet.h"

void UIModule::build()
{
	_dlgProductSet = new DlgProductSet();
	_dlgProductScore = new DlgProductScore();
	labelWarning = new rw::rqw::LabelWarning();
	_dlgIOTrigger = new DlgIOTrigger();
	_dlgShutdownWarn = new DlgShutdownWarn();
	_dlgCloseForm = new DlgCloseForm();

	// 构建分数界面与设置界面的UI联动
	ini_dlgProductScoreGroupList();
	ini_dlgProductSetCheckList();
	connectSetAndScore();
}

void UIModule::destroy()
{
	delete _dlgProductSet;
	delete _dlgProductScore;
	delete labelWarning;
	delete _dlgIOTrigger;
	delete _dlgShutdownWarn;
	delete _dlgCloseForm;
}

void UIModule::start()
{

}

void UIModule::stop()
{

}

void UIModule::ini_dlgProductScoreGroupList()
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

void UIModule::ini_dlgProductSetCheckList()
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

void UIModule::connectSetAndScore()
{
	for (int i = 0; i < _dlgProductSetCheckList.size(); ++i) {
		connect(_dlgProductSetCheckList[i], &QCheckBox::toggled, _dlgProductScoreGroupList[i], &QWidget::setVisible);
		_dlgProductScoreGroupList[i]->setVisible(_dlgProductSetCheckList[i]->isChecked());
	}
}
