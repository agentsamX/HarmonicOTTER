#pragma once
#include "Graphics/Post/PostEffect.h"
class DeferredLighting : public PostEffect
{
public:
	void Init(unsigned width, unsigned height) override;
	void ApplyEffect(PostEffect* buffer) override;
	void DrawToScreen();
	void UpdateUniforms(glm::vec3 camPos, bool spec, bool ambi, bool diff, bool tex, bool toon, int bands);
private:
	glm::vec3 cameraPosition;
	bool specularOn;
	bool ambientOn;
	bool diffuseOn;
	bool textureOn;
	bool toonOn;
	int toonBands;

};
