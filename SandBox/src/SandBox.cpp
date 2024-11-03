#include <Misk.h>
#include <iostream>


class SandBox : public Misk::Appliction
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Misk::Appliction* Misk::CreateAppliction()
{
	return new SandBox();
}