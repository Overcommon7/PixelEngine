#pragma once
#include "Vector2.h"
#include "Vector3.h"

class Commands
{
public:
	virtual string GetName() const { return "Name"; }
	virtual void Invoke(const vector<string>& params) const {};
};

