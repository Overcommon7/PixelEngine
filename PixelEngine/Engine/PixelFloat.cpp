#include "pch.h"
#include "PixelFloat.h"

void PixelFloat::SetCurrentValue(const float& f)
{
	currentValue = f;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::AddTo(const float& f)
{
	currentValue += f;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::AddTo(const PixelFloat& p)
{
	currentValue += p.currentValue;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::SubtractTo(const float& f)
{
	currentValue -= f;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::SubtractTo(const PixelFloat& p)
{
	currentValue -= p.currentValue;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::DivideTo(const float& f)
{
	if (f == 0) return;
	currentValue /= f;
	currentValueAsString = to_string(currentValue);
}

void PixelFloat::MultiplyTo(const float& f)
{
	currentValue *= f;
	currentValueAsString = to_string(currentValue);
}
