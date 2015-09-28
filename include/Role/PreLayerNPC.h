
#ifndef _PRELAYERNPC_H__
#define _PRELAYERNPC_H__

#include "NPC.h"

namespace tds{

	class PreLayerNPC : public BaseNPC
	{
	public:
		CREATE_FUNC(PreLayerNPC);
		virtual std::string getPath(){ return "PreLayerNPC.png"; }
	private:
		PreLayerNPC();
	};


};//end namespace tds;



#endif