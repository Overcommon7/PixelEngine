#include "pch.h"
#include "ScriptParser.h"

bool ScriptParser::IsDigit(const string& str)
{
	short i = 0;
	if (str.front() == '+' || str.front() == '-') ++i;
	for (; i < str.length(); i++)
		if (!isdigit(str[i])) return false;
	return true;
}

bool ScriptParser::IsFloat(const string& str)
{
	short numOfDeciamls = 0;
	short i = 0, j = 0;
	if (str.front() == '+' || str.front() == '-') ++i;
	if (str.back() == 'f') ++j;
	for (; i < str.length() - j; i++)
	{
		if (str[i] != '.' && !isdigit(str[i])) return false;
		if (str[i] == '.') ++numOfDeciamls;
		if (numOfDeciamls > 1) return false;
	}
	return true;
}

void ScriptParser::LoadFloat(const string& line, unordered_map<string, PixelFloat>& variables)
{
	auto params = GetParams(line);
	if (params.size() < 4)
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return;
	}
	if (variables.contains(params[1]))
	{
		cout << "Variable Already Defined - Sytax Error On line: " << lineNumber << '\n';
		return;
	}
	if (variables.contains(params.back()))
	{
		variables.insert({ params[1], variables.at(params.back()) });
		return;
	}
	if (!IsFloat(params.back()))
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return;
	}
	variables.insert({ params[1], params.back()});
}

void ScriptParser::LoadCommand(string line, unordered_map<string, PixelFloat>& variables)
{
	Command command;
	line.erase(remove(line.begin(), line.end(), ' '), line.end());
	const size_t firstBrakcet = line.find_first_of('(');
	const size_t lastBrakcet = line.find_last_of(')');
	if (firstBrakcet == string::npos || lastBrakcet == string::npos)
	{
		command.funcitonName = line;
		command.params = {};
	}
	else
	{
		command.funcitonName = line.substr(0, firstBrakcet);
		stringstream ss(line.substr(firstBrakcet + 1, lastBrakcet - firstBrakcet - 1));
		while (ss.good())
		{
			string substr;
			getline(ss, substr, ',');
			if (variables.contains(substr))
				command.params.push_back(variables.at(substr).GetStringValue());
			else command.params.push_back(substr);
		}
	}
	bool valid = true;
	if (command.funcitonName == "Print")
	{
		++printStatemets;
		cout << "Print Statement #" << printStatemets << ":\n";
		short i = 0;
		for (; i < command.params.size() - 1; i++)
			cout << command.params[i] << ", ";
		cout << command.params[i] << "\n\n";
		return;
	}
	if (command.funcitonName.empty()) return;
	for (const auto& p : command.params)
		if (p.empty())
		{
			valid = false;
			break;
		}
	if (valid)
		commands.push_back(command);
}

void ScriptParser::InternalFloatCommand(string line, unordered_map<string, PixelFloat>& variables)
{
	auto params = GetParams(line);
	line.erase(line.begin() + line.find('='));
	line.insert(0, params.front() + " = ");
	params.insert(params.begin(), { params.front(), " = " });
	float total = GetTotal(line, variables, params);
	if (total == NAN) return;
	variables.at(params.front()).SetCurrentValue(total);
}

float ScriptParser::GetTotal(const string& line, unordered_map<string, PixelFloat>& variables, const vector<string>& params)
{
	if (params.size() < 5)
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return NAN;
	}
	if (!variables.contains(params.front()))
	{
		cout << "Variable does not exists on line: " << lineNumber << '\n';
		return NAN;
	}
	float total = 0;
	if (variables.contains(params[2])) total = variables.at(params[2]).GetValue();
	else if (IsFloat(params[2])) total = stof(params[2]);
	else
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return NAN;
	}
	for (short i = 4; i < params.size(); i += 2)
	{
		bool isValid = true;
		if (variables.contains(params[i])) isValid = Arithmetic(params[i - 1].front(), total, variables.at(params[i]).GetValue());
		else if (IsFloat(params[i])) isValid = Arithmetic(params[i - 1].front(), total, stof(params[i]));
		else
		{
			cout << "Syntax Error on line: " << lineNumber << '\n';
			return NAN;
		}
		if (!isValid) return NAN;
	}
	return total;
}

bool ScriptParser::Arithmetic(const char& c, float& total, const float& value)
{
	switch (c)
	{
	case '+':
		total += value;
		break;
	case '-':
		total -= value;
		break;
	case '/':
		if (value == 0) return false;
		total /= value;
			break;
	case '*':
		total *= value;
		break;
	default:
		cout << "Syntax Error On line: " << lineNumber << '\n';
		return false;
		break;
	}
	return true;

}

void ScriptParser::ArithmeticFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables)
{
	auto params = GetParams(line);
	float total = GetTotal(line, variables, params);
	if (total == NAN) return;
	variables.at(params.front()).SetCurrentValue(total);
}

void ScriptParser::SetFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables)
{
	auto params = GetParams(line);
	if (!variables.contains(params.front()))
	{
		cout << "Variable does not exists on line: " << lineNumber << '\n';
		return;
	}
	if (variables.contains(params.back()))
	{
		variables.at(params.front()) = variables.at(params.back());
		return;
	}
	if (!IsFloat(params.back()))
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return;
	}
	variables.at(params.front()).SetCurrentValue(stof(params.back()));
}

vector<string> ScriptParser::GetParams(const string& line)
{
	stringstream ss(line);
	vector<string> params;
	while (ss.good())
	{
		string buffer;
		getline(ss, buffer, ' ');
		if (buffer.empty()) continue;
		params.push_back(buffer);
	}
	return params;
}

vector<Command> ScriptParser::ParseText(const vector<string>& instructions, unordered_map<string, PixelFloat>& variables)
{
	commands.clear();
	variables.clear();
	lineNumber = 0;
	printStatemets = 0;
	for (const auto& line : instructions)
	{
		++lineNumber;
		bool equals = line.find('=') != string::npos;
		bool add = line.find('+') != string::npos;
		bool sub = line.find('-') != string::npos;
		bool div = line.find('/') != string::npos;
		bool mul = line.find('*') != string::npos;
		bool plusEqual = line.find("+=") != string::npos;
		bool minusEqual = line.find("-=") != string::npos;
		bool mulEqual = line.find("*=") != string::npos;
		bool divideEqual = line.find("/=") != string::npos;


		if (line.find("float ") != string::npos || line.find("int ") != string::npos)	LoadFloat(line, variables);
		else if (plusEqual || divideEqual || minusEqual || mulEqual) InternalFloatCommand(line, variables);
		else if (equals && (add || sub || div || mul)) ArithmeticFloatCommand(line, variables);
		else if (equals) SetFloatCommand(line, variables);
		else LoadCommand(line, variables);


				
	}
	return commands;
}
