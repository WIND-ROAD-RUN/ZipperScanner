#include "ImgProModule.hpp"

#include "imgPro_ImagePainter.hpp"
#include "Modules.hpp"
#include "osoFIleUtiltyFunc.hpp"
#include "Utilty.hpp"

bool ImgProModule::build()
{
	buildImgProContext();
	buildImageProcessingModule(imgProSignalWorkThreadNum);
	for (int i = 0; i < 4; i++)
	{
		imgProIsUpdate[i] = true;
	}
	return true;
}

void ImgProModule::destroy()
{
	destroyImageProcessingModule();
}

void ImgProModule::start()
{

}

void ImgProModule::stop()
{

}

void ImgProModule::buildImgProContext()
{
	buildImgProContextMain();
}

void ImgProModule::buildImgProContextMain()
{
	auto& runningState = Modules::getInstance().runtimeInfoModule.runningState;
	auto& zipperScannerConfig = Modules::getInstance().configManagerModule.zipperScannerConfig;

#pragma region  build base

	imageProcessContext_Main.imageProcessPrepare = [this, &runningState, &zipperScannerConfig](rw::imgPro::ImageProcessContext& context)
		{
			auto& setConfig = Modules::getInstance().configManagerModule.setConfig;
			auto& scoreConfig = Modules::getInstance().configManagerModule.scoreConfig;

			if (context.customFields.find("ImgProcessIndex") == context.customFields.end()) {
				return;
			}
			auto ImgProcessIndex = std::any_cast<int>(context.customFields["ImgProcessIndex"]);

			if (context.customFields.find("stationIdx") == context.customFields.end()) {
				return;
			}
			auto stationIdx = std::any_cast<int>(context.customFields["stationIdx"]);

			double currentPixToWorld{ 0 };

			// initial context.customFields["leftLocationX"]
			{
				context.customFields["leftLocationX"] = 0;
			}

			//update pixToWorld
			{
				if (1 == ImgProcessIndex)
				{
					currentPixToWorld = setConfig.xiangSuDangLiang1;
				}
				else if (2 == ImgProcessIndex)
				{
					currentPixToWorld = setConfig.xiangSuDangLiang2;
				}
				context.customFields["CurrentPixToWorld"] = static_cast<double>(currentPixToWorld);
			}

			//update Config
			{
				if (imgProIsUpdate[stationIdx])
				{
					context.eliminationCfg = cdm::ScoreConfigConvert::toClassIdWithEliConfigMap(scoreConfig, currentPixToWorld * currentPixToWorld, 100);
					context.defectCfg = cdm::ScoreConfigConvert::toClassIdWithDefConfigMap(scoreConfig);
					imgProIsUpdate[stationIdx] = false;
				}
			}

			// update limite
			{
				int limitLeft{ 0 };
				int limitRight{ 0 };
				int limitTop{ 0 };
				int limitBottom{ 0 };

				if (1 == ImgProcessIndex)
				{
					limitLeft = static_cast<int>(setConfig.zuoXianWei1);
					limitRight = static_cast<int>(setConfig.youXianWei1);
					limitTop = static_cast<int>(setConfig.shangXianWei1);
					limitBottom = static_cast<int>(setConfig.xiaXianWei1);
					currentPixToWorld = setConfig.xiangSuDangLiang1;
				}
				else if (2 == ImgProcessIndex)
				{
					limitLeft = static_cast<int>(setConfig.zuoXianWei2);
					limitRight = static_cast<int>(setConfig.youXianWei2);
					limitTop = static_cast<int>(setConfig.shangXianWei2);
					limitBottom = static_cast<int>(setConfig.xiaXianWei2);
					currentPixToWorld = setConfig.xiangSuDangLiang2;
				}

				context.customFields["LimitLeft"] = static_cast<int>(limitLeft);
				context.customFields["LimitRight"] = static_cast<int>(limitRight);
				context.customFields["LimitTop"] = static_cast<int>(limitTop);
				context.customFields["LimitBottom"] = static_cast<int>(limitBottom);
			}

			// update drawConfig
			{
				if (RunningState::Debug == runningState)
				{
					context.defectDrawCfg.textLocate = rw::imgPro::ConfigDrawRect::TextLocate::LeftTopIn;

					if (zipperScannerConfig.isshibiekuang)
					{
						context.defectDrawCfg.isDrawDefects = true;
						context.defectDrawCfg.isDrawDisableDefects = true;
						context.defectDrawCfg.isDisAreaText = true;
						context.defectDrawCfg.isDisScoreText = true;
					}
					else
					{
						context.defectDrawCfg.isDrawDefects = false;
						context.defectDrawCfg.isDrawDisableDefects = false;
						context.defectDrawCfg.isDisAreaText = false;
						context.defectDrawCfg.isDisScoreText = false;
					}

					if (zipperScannerConfig.iswenzi)
					{
						context.runTextCfg.isDrawExtraText = true;
					}
					else
					{
						context.runTextCfg.isDrawExtraText = false;
					}
				}
				else if (RunningState::OpenRemoveFunc == runningState)
				{
					context.defectDrawCfg.isDrawDefects = true;
					context.defectDrawCfg.isDrawDisableDefects = true;
					context.defectDrawCfg.isDisAreaText = true;
					context.defectDrawCfg.isDisScoreText = true;

					context.runTextCfg.isDrawExtraText = false;
				}
			}
		};

#pragma endregion

#pragma region build index get
	imageProcessContext_Main.indexGetContext.removeIndicesIfByInfo = [this](
		const rw::DetectionRectangleInfo& info,
		rw::imgPro::ImageProcessContext& context)
		{
			bool isInShieldWires = false;
			int limitLeft{ -1 };
			int limitRight{ -1 };
			int limitTop{ -1 };
			int limitBottom{ -1 };

			if (context.customFields.find("LimitLeft") != context.customFields.end()) {
				limitLeft = std::any_cast<int>(context.customFields["LimitLeft"]);
			}
			if (context.customFields.find("LimitRight") != context.customFields.end()) {
				limitRight = std::any_cast<int>(context.customFields["LimitRight"]);
			}
			if (context.customFields.find("LimitTop") != context.customFields.end()) {
				limitTop = std::any_cast<int>(context.customFields["LimitTop"]);
			}
			if (context.customFields.find("LimitBottom") != context.customFields.end()) {
				limitBottom = std::any_cast<int>(context.customFields["LimitBottom"]);
			}

			if (-1 == limitLeft || -1 == limitRight || -1 == limitTop || -1 == limitBottom)
			{
				return false;
			}
			// 判断缺陷框中心点是否在屏蔽线区域内
			if (info.center_x < limitRight && info.center_x > limitLeft)
			{
				if (info.center_y > limitTop && info.center_y < limitBottom)
				{
					isInShieldWires = true;
				}
			}

			return !isInShieldWires;
		};
#pragma endregion

#pragma region build elimination config
	imageProcessContext_Main.eliminationInfoGetContext.getEliminationItemFuncSpecialOperator = [this](
		rw::imgPro::EliminationItem& item,
		const rw::DetectionRectangleInfo& info,
		const rw::imgPro::EliminationInfoGetConfig& cfg) {
			item.customFields["LocationX"] = static_cast<int>(info.center_x);
		};
#pragma endregion

#pragma region build defect config
	imageProcessContext_Main.defectResultGetContext.getDefectResultExtraOperateWithFullInfo = [this]
	(const rw::DetectionRectangleInfo& detectionRectangleInfo,
		const rw::imgPro::EliminationInfoGetConfig& eliminationInfoGetConfig,
		const rw::imgPro::EliminationItem& eliminationItem,
		const rw::imgPro::DefectResultGetConfig& defectResultGetConfig,
		rw::imgPro::DefectResultInfo& defectResultInfo,
		rw::imgPro::ImageProcessContext& context)
		{
			if (!defectResultInfo.isBad) {
				return;
			}
			auto find = eliminationItem.customFields.find("LocationX");
			if (find != eliminationItem.customFields.end())
			{
				auto findLeftLocationX = context.customFields.find("leftLocationX");
				if (findLeftLocationX != context.customFields.end())
				{
					auto leftLocationX = std::any_cast<int>(findLeftLocationX->second);
					context.customFields["leftLocationX"] = (std::max)(leftLocationX, std::any_cast<int>(find->second));
				}
			}
		};
#pragma endregion

#pragma region build defect draw
	imageProcessContext_Main.defectDrawCfg.classIdNameMap = ClassId::classIdNameMap;

	rw::imgPro::DefectDrawConfigItem drawItemConfig;

	drawItemConfig.fontSize = 50;
	drawItemConfig.textLocate = rw::imgPro::ConfigDrawRect::TextLocate::LeftTopIn;

	for (size_t i = ClassId::minNum; i <= ClassId::maxNum; i++)
	{
		imageProcessContext_Main.defectDrawCfg.classIdWithConfigMap[i] = drawItemConfig;
	}

	imageProcessContext_Main.defectDrawFuncContext.postOperateFunc = [](
		QImage& img,
		rw::imgPro::ImageProcessContext& context) {

			int limitLeft{ 0 };
			int limitRight{ 0 };
			int limitTop{ 0 };
			int limitBottom{ 0 };

			if (context.customFields.find("LimitLeft") != context.customFields.end()) {
				limitLeft = std::any_cast<int>(context.customFields["LimitLeft"]);
			}
			if (context.customFields.find("LimitRight") != context.customFields.end()) {
				limitRight = std::any_cast<int>(context.customFields["LimitRight"]);
			}
			if (context.customFields.find("LimitTop") != context.customFields.end()) {
				limitTop = std::any_cast<int>(context.customFields["LimitTop"]);
			}
			if (context.customFields.find("LimitBottom") != context.customFields.end()) {
				limitBottom = std::any_cast<int>(context.customFields["LimitBottom"]);
			}

			rw::imgPro::ConfigDrawLine configDrawLine;
			configDrawLine.color = rw::imgPro::Color::Red;
			configDrawLine.thickness = 5;

			configDrawLine.position = limitTop;
			rw::imgPro::ImagePainter::drawHorizontalLine(img, configDrawLine);
			configDrawLine.position = limitBottom;
			rw::imgPro::ImagePainter::drawHorizontalLine(img, configDrawLine);
			configDrawLine.position = limitLeft;
			rw::imgPro::ImagePainter::drawVerticalLine(img, configDrawLine);
			configDrawLine.position = limitRight;
			rw::imgPro::ImagePainter::drawVerticalLine(img, configDrawLine);


		};
#pragma endregion

#pragma region build running time text
	imageProcessContext_Main.runTextCfg.isDisProcessImgTime = false;
	imageProcessContext_Main.runTextCfg.isDrawExtraText = false;
#pragma endregion
}

void ImgProModule::resetImgProIsUpdate(bool state)
{
	for (auto& flag : imgProIsUpdate) {
		flag.store(state);
	}
}

void ImgProModule::buildImageProcessingModule(size_t num)
{
	imageProcessingModule1 = std::make_unique<ImageProcessingModule>(num, this);
	imageProcessingModule1->modelEnginePath = globalPath.modelPath;
	imageProcessingModule1->index = 1;
	imageProcessingModule1->BuildModule();

	imageProcessingModule2 = std::make_unique<ImageProcessingModule>(num, this);
	imageProcessingModule2->modelEnginePath = globalPath.modelPath;
	imageProcessingModule2->index = 2;
	imageProcessingModule2->BuildModule();
}

void ImgProModule::destroyImageProcessingModule()
{
	imageProcessingModule1.reset();
	imageProcessingModule2.reset();
}

void ImgProModule::onUpdateImgProContext()
{
	buildImgProContext();
	resetImgProIsUpdate(true);
}
