#pragma once
class PixelFloat
{
	float currentValue;
	float resetValue;
	string currentValueAsString;
public:
	const float& GetValue() const { return currentValue; };
	const float& GetResetValue() const { return resetValue; }
	const string& GetStringValue() const { return currentValueAsString; }

	void ResetCurrentValue() { currentValue = resetValue; currentValueAsString = to_string(resetValue); }
	void SetCurrentValue(const float& f);
	void ChangeResetValue(const float& f) { resetValue = f; }
	
	void AddTo(const float& f);
	void AddTo(const PixelFloat& p);
	void SubtractTo(const float& f);
	void SubtractTo(const PixelFloat& p);
	void DivideTo(const float& f);
	void MultiplyTo(const float& f);

	PixelFloat(const string& s) : currentValue(stof(s)), resetValue(stof(s)), currentValueAsString(s) {}
	PixelFloat(const float& f) : currentValue(f), resetValue(f), currentValueAsString(to_string(f)) {}
	PixelFloat(const PixelFloat& f) = default;
	PixelFloat& operator=(const PixelFloat& f) = default;
};

