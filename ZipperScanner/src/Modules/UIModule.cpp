#include "UIModule.hpp"
#include "DlgProductSet.h"
#include "DlgProductScore.h"
#include "rqw_LabelWarning.h"
#include "ui_DlgProductScore.h"
#include "ui_DlgProductSet.h"

void UIModule::build()
{
	_dlgProductSet = new DlgProductSet();
	_dlgProductScore = new DlgProductScore();
	labelWarning = new rw::rqw::LabelWarning();

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
		/*_dlgProductScore->ui->widget_tangshang,
		_dlgProductScore->ui->widget_queliao,
		_dlgProductScore->ui->widget_yiwu,
		_dlgProductScore->ui->widget_zangwu,
		_dlgProductScore->ui->widget_extra2,
		_dlgProductScore->ui->widget_extra3,
		_dlgProductScore->ui->widget_extra4,
		_dlgProductScore->ui->widget_extra5,
		_dlgProductScore->ui->widget_extra6,
		_dlgProductScore->ui->widget_extra7,
		_dlgProductScore->ui->widget_extra8,
		_dlgProductScore->ui->widget_extra9*/
	};
}

void UIModule::ini_dlgProductSetCheckList()
{
	_dlgProductSetCheckList = {
		/*_dlgProductSet->ui->ckb_tangshang,
		_dlgProductSet->ui->ckb_queliao,
		_dlgProductSet->ui->ckb_yiwu,

		_dlgProductSet->ui->ckb_zangwu,
		_dlgProductSet->ui->ckb_extra2,
		_dlgProductSet->ui->ckb_extra3,
		_dlgProductSet->ui->ckb_extra4,
		_dlgProductSet->ui->ckb_extra5,
		_dlgProductSet->ui->ckb_extra6,
		_dlgProductSet->ui->ckb_extra7,
		_dlgProductSet->ui->ckb_extra8,
		_dlgProductSet->ui->ckb_extra9*/
	};
}

void UIModule::connectSetAndScore()
{
	for (int i = 0; i < _dlgProductSetCheckList.size(); ++i) {
		connect(_dlgProductSetCheckList[i], &QCheckBox::toggled, _dlgProductScoreGroupList[i], &QWidget::setVisible);
		_dlgProductScoreGroupList[i]->setVisible(_dlgProductSetCheckList[i]->isChecked());
	}
}
