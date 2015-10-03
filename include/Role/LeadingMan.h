#ifndef _LEADING_MAN_H__
#define _LEADING_MAN_H__

#include "Role.h"

namespace tds{

	class LeadingMan : public Role
	{
	public:
		static LeadingMan* create(std::string name = "");

	public:
		void onMove();
		void updateSelf(float duration);

	private:
		virtual bool init();
		LeadingMan(std::string name);
		~LeadingMan();

	};

};//end namespace tds;

#endif
