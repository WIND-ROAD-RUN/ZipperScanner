#pragma once

#include <QDialog>
#include "ui_DlgProductScore.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgProductScoreClass; };
QT_END_NAMESPACE

class DlgProductScore : public QDialog
{
	Q_OBJECT

public:
	DlgProductScore(QWidget* parent = nullptr);
	~DlgProductScore();

public:
	void build_ui();
	void read_config();
	void build_connect();

private slots:
	void btn_close_clicked();

	void ckb_queya_checked();
	void btn_queyascore_clicked();
	void btn_queyaarea_clicked();
	void ckb_tangshang_checked();
	void btn_tangshangscore_clicked();
	void btn_tangshangarea_clicked();
	void ckb_zangwu_checked();
	void btn_zangwuscore_clicked();
	void btn_zangwuarea_clicked();
	void ckb_suoxiao_checked();
	void btn_suoxiaoscore_clicked();
	void btn_suoxiaoarea_clicked();
	void ckb_huawen_checked();
	void btn_huawenscore_clicked();
	void btn_huawenarea_clicked();
	void ckb_yuan_checked();
	void btn_yuanscore_clicked();
	void btn_yuanarea_clicked();
	void ckb_huapo_checked();
	void btn_huaposcore_clicked();
	void btn_huapoarea_clicked();

	// 暂未启用的额外缺陷
	void ckb_duanxian_checked();
	void btn_duanxianscore_clicked();
	void btn_duanxianarea_clicked();
	void ckb_extra5_checked();
	void btn_extra5score_clicked();
	void btn_extra5area_clicked();
	void ckb_extra6_checked();
	void btn_extra6score_clicked();
	void btn_extra6area_clicked();
	void ckb_extra7_checked();
	void btn_extra7score_clicked();
	void btn_extra7area_clicked();
	void ckb_extra8_checked();
	void btn_extra8score_clicked();
	void btn_extra8area_clicked();

signals:
	void scoreFormClosed();

public:
	Ui::DlgProductScoreClass* ui;
};

