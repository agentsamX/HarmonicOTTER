#pragma once

#include "Graphics/Post/PostEffect.h"

class Blur : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	//apply effect
	void ApplyEffect(PostEffect* buffer) override;

	//applies effect to screeen
	void DrawToScreen() override;

	int GetPasses() const;

	void SetPasses(int passes);
	
private:
	int _passes = 5;
};