#include "stdafx.h"
#include "MessageManager.h"
#include "MapperFactory.h"
#include "ROMLoader.h"
#include "AXROM.h"
#include "CNROM.h"
#include "ColorDreams.h"
#include "MMC1.h"
#include "MMC2.h"
#include "MMC3.h"
#include "MMC3_189.h"
#include "MMC5.h"
#include "Nanjing.h"
#include "NROM.h"
#include "UNROM.h"
#include "VRC2_4.h"
#include "BF909x.h"

BaseMapper* MapperFactory::GetMapperFromID(uint8_t mapperID)
{
#ifdef _DEBUG
	MessageManager::DisplayMessage("Game Info", "Mapper: " + std::to_string(mapperID));
#endif

	switch(mapperID) {
		case 0: return new NROM();
		case 1: return new MMC1();
		case 2: return new UNROM();
		case 3: return new CNROM();
		case 4: return new MMC3();
		case 5: return new MMC5();
		case 7: return new AXROM();
		case 9: return new MMC2();
		case 11: return new ColorDreams();
		case 16: break; //18 games
		case 19: break; //16 games
		case 21: return new VRC2_4(VRCVariant::VRC4a);  //Conflicts: VRC4c
		case 22: return new VRC2_4(VRCVariant::VRC2a);
		case 23: return new VRC2_4(VRCVariant::VRC2b);  //Conflicts: VRC4e
		case 25: return new VRC2_4(VRCVariant::VRC4b);  //Conflicts: VRC2c, VRC4d
		case 27: return new VRC2_4(VRCVariant::VRC4_27);  //Untested
		case 71: return new BF909x();
		case 163: return new Nanjing();
		case 189: return new MMC3_189();
		default: MessageManager::DisplayMessage("Error", "Unsupported mapper, cannot load game.");
	}

	return nullptr;
}

shared_ptr<BaseMapper> MapperFactory::InitializeFromFile(string romFilename, stringstream *filestream, string ipsFilename)
{
	ROMLoader loader;

	if(loader.LoadFile(romFilename, filestream, ipsFilename)) {
		uint8_t mapperID = loader.GetMapperID();

		shared_ptr<BaseMapper> mapper(GetMapperFromID(mapperID));

		if(mapper) {
			mapper->Initialize(loader);
			return mapper;
		}
	}
	return nullptr;
}

