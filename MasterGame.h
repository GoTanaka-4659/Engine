#pragma once

#include "Framework.h"

#include <vector>

class MasterGame : public Framework
{
private:

	std::vector<Sprite *>sprites;
public:
	void Initilize();
	void Update();
	void Draw();
	void Finalize();
	
};
