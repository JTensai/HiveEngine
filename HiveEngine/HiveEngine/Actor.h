#pragma once
class Actor
{
private:
	int _modelHandle;
public:
	Actor();
	void draw();
	void update(float delta);
	~Actor();
};

