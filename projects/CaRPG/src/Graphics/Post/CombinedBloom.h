#pragma once

#include "Graphics/Post/PostEffect.h"

class CombinedBloom : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	//apply effect
	void ApplyEffect(PostEffect* buffer) override;

	//applies effect to screeen
	void DrawToScreen() override;

	float GetIntensity() const;

	void SetIntensity(float intensity);

	float GetThreshold() const;

	void SetThreshold(float threshold);

	int GetPasses() const;

	void SetPasses(int passes);
	
private:
	float _intensity = 0.5f;
	float _threshold = 0.5f;
	int _passes = 5;
};