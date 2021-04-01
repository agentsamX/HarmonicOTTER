#pragma once

#include "Graphics/Post/PostEffect.h"
enum BlurType
{
	GAUSS,
	BOX,
	RADIAL
};

class CombinedBloom : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	//apply effect
	void ApplyEffect(PostEffect* buffer) override;

	//applies effect to screeen
	void DrawToScreen() override;

	float GetThreshold() const;

	void SetThreshold(float threshold);

	int GetPasses() const;

	void SetPasses(int passes);

	void SetBlurType(int type);

	int GetBlurType();
	
private:
	BlurType _blurType = GAUSS;
	int widShader=2;
	int heiShader=3;
	float _threshold = 0.5f;
	int _passes = 5;
};