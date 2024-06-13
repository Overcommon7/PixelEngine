#pragma once

class Commands
{
public:
	virtual string GetName() const { return "Name"; }
	virtual void Invoke(const vector<string>& params) const {};
};

