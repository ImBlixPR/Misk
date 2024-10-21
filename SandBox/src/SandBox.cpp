#include <Misk.h>
#include <iostream>


class SandBox : public Misk::Applaction
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Misk::Applaction* Misk::CreateApplaction()
{
	return new SandBox();
}