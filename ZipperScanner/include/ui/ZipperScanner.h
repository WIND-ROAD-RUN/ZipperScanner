#pragma once

#include <QMainWindow>
#include "ui_ZipperScanner.h"
#include "DlgProductSet.h"
#include "DlgProductScore.h"
#include "DlgExposureTimeSet.h"
#include "DlgIOTrigger.h"
#include <rqw_LabelWarning.h>
#include <opencv2/core/mat.hpp>

#include "PictureViewerThumbnails.h"
#include "ImageEnlargedDisplay.h"
#include"rqw_LabelClickable.h"
#include <QSpinBox>
#include"DlgShutdownWarn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ZipperScannerClass; };
QT_END_NAMESPACE

class ZipperScanner : public QMainWindow
{
	Q_OBJECT
#ifdef BUILD_WITHOUT_HARDWARE
private:
	QCheckBox* _testIfPushImg;
	QSpinBox* _pushImgTime;
public slots:
	void cbox_testIfPushImg_clicked(bool states);
	void sBox_pushImgTime_valueChanged(int value);
#endif
public:
	ZipperScanner(QWidget* parent = nullptr);
	~ZipperScanner();

public:
	void build_detachThread();
	void destory_detachThread();
public:
	DlgProductSet* _dlgProductSet = nullptr;
	QVector<QCheckBox*> _dlgProductSetCheckList{};
	DlgProductScore* _dlgProductScore = nullptr;
	QVector<QWidget*> _dlgProductScoreGroupList{};
	DlgExposureTimeSet* _dlgExposureTimeSet = nullptr;
	DlgIOTrigger* _dlgIOTrigger = nullptr;
	DlgShutdownWarn* _dlgShutdownWarn = nullptr;
private:
	PictureViewerThumbnails* _picturesViewer = nullptr;
	rw::rqw::ClickableLabel* clickableTitle = nullptr;
public:
	void build_ui();
	void build_connect();
	void build_camera();
	void build_motion();

	void build_ZipperScannerData();
	void build_DlgProductSetData();
	void ini_dlgProductSetCheckList();
	void build_DlgProductScore();
	void ini_dlgProductScoreGroupList();
	void connectSetAndScore();
	void build_DlgExposureTimeSet();
	void build_DlgIOTrigger();
	void ini_clickableTitle();

	void build_imageProcessorModule();
	void build_imageSaveEngine();

	void start_Threads();

	void start_CameraMonitor();

public:
	void destroyComponents();

public:
	void read_config();
	void read_config_GeneralConfig();
	void read_config_ScoreConfig();
	void read_config_SetConfig();

private:
	void changeRemoveFucState(bool state);

private slots:
	void pbtn_exit_clicked();
	void pbtn_set_clicked();
	void pbtn_score_clicked();
	void rbtn_debug_checked(bool checked);
	void rbtn_strongLight_checked(bool checked);
	void rbtn_mediumLight_checked(bool checked);
	void rbtn_weakLight_checked(bool checked);
	void pbtn_openSaveLocation_clicked();
	void rbtn_takePicture_checked();
	void rbtn_removeFunc_checked(bool checked);
	void ckb_shibiekuang_checked(bool checked);
	void ckb_wenzi_checked(bool checked);
	void rbtn_start_clicked(bool checked);
	void rbtn_stop_clicked(bool checked);
	void pbtn_IOTrigger_clicked();
	void btn_shedingladaichangdu_clicked();
	void pbtn_resetProduct_clicked();

	void lb_title_clicked();
signals:
	void shibiekaungChanged();
	void wenziChanged();


private slots:
	void updateCameraLabelState(int cameraIndex, bool state);

	void onCamera1Display(QPixmap image);
	void onCamera2Display(QPixmap image);

	void onCameraNGDisplay(QPixmap image, size_t index, bool isbad);

	// 更新UI
	void updateUiLabels(int index, bool isConnected);

	// 监控启停IO
	void getStartOrStopSignal(size_t index, bool state);

private:
	bool _isImageEnlargedDisplay{ false };
	int _currentImageEnlargedDisplayIndex{ 0 };
	std::map<int, QString> _workStationTitleMap{};

	QPixmap _lastImage1{};
	QPixmap _lastImage2{};
	QPixmap _lastNgImage1{};
	QPixmap _lastNgImage2{};

	rw::rqw::ClickableLabel* imgDis1 = nullptr;
	rw::rqw::ClickableLabel* imgDis2 = nullptr;
	rw::rqw::ClickableLabel* imgNgDis1 = nullptr;
	rw::rqw::ClickableLabel* imgNgDis2 = nullptr;
private slots:
	void imgDis1_clicked();
	void imgDis2_clicked();
	void imgNgDis1_clicked();
	void imgNgDis2_clicked();

	void refreshShowImages();
private:
	ImageEnlargedDisplay* _imageEnlargedDisplay = nullptr;
public:
	void build_ImageEnlargedDisplay();
	void destroy_ImageEnlargedDisplay();

private:
	Ui::ZipperScannerClass* ui;
	int minimizeCount{ 3 };
private:
	bool isShutdownByIO{ false };
	bool isConnnectCard{ false };
public slots:
	void onFinishProduce();
	void onUpdateStatisticalInfo();
public slots:
	void shutdownComputerTrigger(int time);
};
