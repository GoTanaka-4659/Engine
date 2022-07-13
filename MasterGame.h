#pragma once

#include "Framework.h"

#include <vector>

class MasterGame : public Framework
{
private:

	std::vector<Sprite *>sprites;
public:
	void Initilize() override;
	void Update()override;
	void Draw();
	void Finalize()override;
	

};
