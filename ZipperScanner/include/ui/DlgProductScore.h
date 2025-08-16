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

	// 暂未启用的额外缺陷
	void ckb_extra1_checked();
	void btn_extra1score_clicked();
	void btn_extra1area_clicked();
	void ckb_extra2_checked();
	void btn_extra2score_clicked();
	void btn_extra2area_clicked();
	void ckb_extra3_checked();
	void btn_extra3score_clicked();
	void btn_extra3area_clicked();
	void ckb_extra4_checked();
	void btn_extra4score_clicked();
	void btn_extra4area_clicked();
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

private:
	Ui::DlgProductScoreClass* ui;
};

