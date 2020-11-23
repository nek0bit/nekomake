#pragma once

struct Timer {
	Timer(int FPS);
	~Timer();

	int frameDelay;
	float deltaTime;
	
	void setFPS(int FPS);
	void setCurrentTime(float time);
	int getSleepTime(float time);
private:
	float lastFrame;
};