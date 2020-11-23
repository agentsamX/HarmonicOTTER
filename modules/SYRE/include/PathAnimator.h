#pragma once
#include "Transform.h"
#include <vector>

namespace syre
{
	enum class PathType
	{
		LERP,
		BEZIER,
		CATMULL
	};
	class PathAnimator
	{
	public:
		PathAnimator(PathType initType);
		PathAnimator(PathType initType, bool speedCont);
		PathAnimator(PathType initType, bool speedCont,glm::vec3 startPoint);
		void AddPoint(glm::vec3 pos, glm::vec3 rot);
		void AddPoint(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& rot);
		void Update(Transform* curTrans, float delta);
		void Reset();
	private:
		PathType pathType;
		bool speedControl = true;
		bool absolutePos = true;
		std::vector<glm::mat2x3> points;
		glm::vec3 startPoint;
		int currentIndex = 0;
		int handleIndex1 = 1;
		int handleIndex2 = 2;
		int nextIndex = 1;
	};
}