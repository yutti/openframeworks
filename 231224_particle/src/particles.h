#pragma once
#include "ofMain.h"

enum particleMode {
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE,
	PARTICLE_MODE_NOISE_RAIN,
	PARTICLE_MODE_NOISE_STAR
};

class particles {

public:
	particles();

	void setMode(particleMode newMode);
	void setAttractPoints(vector <glm::vec3>* attract);

	void reset();
	void update();
	void draw();

	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 color;
	glm::vec3 frc;

	float drag;
	float uniqueVal;
	float scale;

	particleMode mode;

	vector <glm::vec3>* attractPoints;
};
