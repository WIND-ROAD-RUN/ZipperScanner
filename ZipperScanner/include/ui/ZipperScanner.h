#pragma once

#include <QMainWindow>
#include "ui_ZipperScanner.h"
#include <rqw_LabelWarning.h>
#include <opencv2/core/mat.hpp>
#include "PictureViewerThumbnails.h"
#include "ImageEnlargedDisplay.h"
#include"rqw_LabelClickable.h"
#include <QSpinBox>


QT_BEGIN_NAMESPACE
namespace Ui { class ZipperScannerClass; };
QT_END_NAMESPACE

class ZipperScanner : public QMainWindow
{
	Q_OBJECT
#ifdef BUILD_WITHOUT_HARDWARE
public:
	QCheckBox* cBox_testPushImg{ nullptr };
public slots:
	void cBox_testPushImg_checked(bool checked);
#endif
public:
	ZipperScanner(QWidget* parent = nullptr);
	~ZipperScanner();
public:
	QMutex produceInfoMutex;
	bool isSendProduceInfo{false};
public:

private:
	PictureViewerThumbnails* _picturesViewer = nullptr;
	rw::rqw::ClickableLabel* clickableTitle = nullptr;
public:
	void build_ui();
	void build_connect();
	void getCameraStateAndUpdateUi();
	void getZMotionStateAndUpdateUi();

	void build_ZipperScannerData();
	void ini_clickableTitle();

public:
	void destroyComponents();

public:
	void read_config();
	void read_config_GeneralConfig();
	void updateControllines();

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
	void shibiekuangChanged();
	void wenziChanged();


public slots:
	void updateCameraLabelState(int cameraIndex, bool state);

	void onCameraDisplay(QPixmap image, size_t index, bool isbad);

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
	bool _isConnnectCard{ false };
public slots:
	void onFinishProduce();
	void onUpdateStatisticalInfo();
public slots:
	void shutdownComputerTrigger(int time);
};
