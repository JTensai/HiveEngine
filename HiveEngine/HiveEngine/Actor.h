#pragma once
class Actor
{
private:
	int _modelHandle;
public:
	Actor();
	void update(float delta);
	void render();
	~Actor();
};

