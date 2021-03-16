#pragma once

#include "Graphics/Post/PostEffect.h"

class Pixelate : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	//apply effect
	void ApplyEffect(PostEffect* buffer) override;

	//applies effect to screeen
	//void DrawToScreen() override;

	int GetFactor() const;
	
	void SetFactor(int factor);

private:
	int pixelFactor = 2;
	float _width;
	float _height;
};