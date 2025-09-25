#include "ImgProModule.hpp"

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

#pragma region  build base
	
#pragma endregion

#pragma region build index get
	
#pragma endregion

#pragma region build elimination config

#pragma endregion

#pragma region build defect config
	
#pragma endregion

#pragma region build defect draw
	
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
