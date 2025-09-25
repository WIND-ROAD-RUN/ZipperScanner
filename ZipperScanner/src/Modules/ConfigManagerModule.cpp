#include "ConfigManagerModule.hpp"

#include "Utilty.hpp"
#include "Modules.hpp"

bool ConfigManagerModule::build()
{
    storeContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	//auto& runtimeModule = Modules::getInstance().runtimeInfoModule;

#pragma region readHandleScannerCfg
	auto loadMainWindowConfig = storeContext->loadSafe(globalPath.generalConfigPath.toStdString());
	if (loadMainWindowConfig)
	{
		zipperScannerConfig = *loadMainWindowConfig;
		//runtimeModule.isTakePictures = zipperScannerConfig.isSaveImg;
		/*runtimeModule.statisticalInfo.produceCount = zipperScannerConfig.;
		runtimeModule.statisticalInfo.wasteCount = zipperScannerConfig.totalDefectiveVolume;
		runtimeModule.statisticalInfo.productionYield = zipperScannerConfig.productionYield;
		runtimeModule.statisticalInfo.handleCountForStop = zipperScannerConfig.tingjigeshu;*/
	}
#pragma endregion

#pragma region readscoreCfg
	loadMainWindowConfig = storeContext->loadSafe(globalPath.scoreConfigPath.toStdString());
	if (loadMainWindowConfig)
	{
		scoreConfig = *loadMainWindowConfig;
	}
#pragma endregion

#pragma region readsetCfg
	loadMainWindowConfig = storeContext->loadSafe(globalPath.setConfigPath.toStdString());
	if (loadMainWindowConfig)
	{
		setConfig = *loadMainWindowConfig;
	}
#pragma endregion

	return true;
}

void ConfigManagerModule::destroy()
{
	storeContext->saveSafe(zipperScannerConfig, globalPath.generalConfigPath.toStdString());
	storeContext->saveSafe(scoreConfig, globalPath.scoreConfigPath.toStdString());
	storeContext->saveSafe(setConfig, globalPath.setConfigPath.toStdString());
	storeContext.reset();
}

void ConfigManagerModule::start()
{
	zipperScannerConfig.isDebug = false;
}

void ConfigManagerModule::stop()
{

}
