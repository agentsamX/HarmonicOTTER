#pragma once

#include "Graphics/Post/PostEffect.h"

class CubeCoCoEffect : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;

	//apply effect
	void ApplyEffect(PostEffect* buffer) override;

	//applies effect to screeen
	void DrawToScreen() override;

	float GetIntensity() const;

	void SetIntensity(float intensity);

private:
	float _intensity = 1.0f;
};