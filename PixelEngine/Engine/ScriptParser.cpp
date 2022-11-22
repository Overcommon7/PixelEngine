#include "pch.h"
#include "ScriptParser.h"
#include "Utilities.h"

void ScriptParser::LoadFloat(const string& line, unordered_map<string, PixelFloat>& variables)
{
	auto params = GetParams(line);
	if (params.size() < 4)
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return;
	}
	if (!isRefresh && variables.contains(params[1]))
	{
		cout << "Variable Already Defined - Sytax Error On line: " << lineNumber << '\n';
		return;
	}
	if (variables.contains(params.back()))
	{
		variables.insert({ params[1], variables.at(params.back()) });
		return;
	}
	if (!Utils::IsFloat(params.back()))
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return;
	}
	variables.insert({ params[1], params.back()});
}

void ScriptParser::Print(const Command& command)
{
	++printStatemets;
	cout << "Print Statement #" << printStatemets << ":\n";
	short i = 0;
	for (; i < command.params.size() - 1; i++)
		cout << command.params[i] << ", ";
	cout << command.params[i] << "\n\n";
}

void ScriptParser::LoadCommand(string line, unordered_map<string, PixelFloat>& variables)
{
	Command command;	
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

			auto it = substr.begin();
			while (it != substr.end() && *it == ' ')
				it = substr.erase(it);
			if (substr.empty()) continue;

			if (substr.find_first_of("/*-+", 1) != string::npos)
			{
				float total = GetTotal("", variables, GetParams(substr), true, true);
				if (total != NAN)
					command.params.push_back(to_string(total));
			}
			else
			{
				substr.erase(remove(substr.begin(), substr.end(), ' '), substr.end());
				if (variables.contains(substr))
					command.params.push_back(variables.at(substr).GetStringValue());
				else command.params.push_back(substr);
			}
		}
	}
	if (command.funcitonName == "Print")
	{
		Print(command);
		return;
	}
	if (command.funcitonName.empty()) return;
	auto it = command.params.begin();
	while (it != command.params.end())
		if (it->empty())it = command.params.erase(it);
		else ++it;

	commands.push_back(command);
}

void ScriptParser::InternalFloatCommand(const string& line, unordered_map<string, PixelFloat>& variables, const OperationType& type)
{
	auto params = GetParams(line);
	float total = GetTotal(line, variables, params, true);
	if (total == NAN || total == -NAN) return;
	if (type == OperationType::PlusEquals) variables.at(params.front()).AddTo(total);
	else if (type == OperationType::MinusEquals) variables.at(params.front()).SubtractTo(total);
	else if (type == OperationType::MultiplyEquals) variables.at(params.front()).MultiplyTo(total);
	else if (type == OperationType::PlusEquals) variables.at(params.front()).DivideTo(total);
}

float ScriptParser::GetTotal(const string& line, unordered_map<string, PixelFloat>& variables, const vector<string>& params, const bool& skipCheck, const bool& skipCheck2)
{

	if (!skipCheck && params.size() < 5)
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return NAN;
	}

	if (!skipCheck2 && !variables.contains(params.front()))
	{
		cout << "Variable does not exists on line: " << lineNumber << '\n';
		return NAN;
	}
	float total = 0;
	short start = 2;
	if (skipCheck2) start -= 2;
	if (variables.contains(params[start])) total = variables.at(params[start]).GetValue();
	else if (Utils::IsFloat(params[start])) total = stof(params[start]);
	else
	{
		cout << "Syntax Error on line: " << lineNumber << '\n';
		return NAN;
	}
	for (short i = start + 2; i < params.size(); i += 2)
	{
		bool isValid = true;
		if (variables.contains(params[i])) isValid = Arithmetic(params[i - 1].front(), total, variables.at(params[i]).GetValue());
		else if (Utils::IsFloat(params[i])) isValid = Arithmetic(params[i - 1].front(), total, stof(params[i]));
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
	if (!Utils::IsFloat(params.back()))
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
	//variables.clear();
	lineNumber = 0;
	printStatemets = 0;
	for (const auto& line : instructions)
	{
		++lineNumber;
		if (line.length() < 2) continue;
		if (line[0] == '/' && line[1] == '/') continue;

		bool equals = line.find('=') != string::npos;
		bool add = line.find('+') != string::npos;
		bool sub = line.find('-') != string::npos;
		bool div = line.find('/') != string::npos;
		bool mul = line.find('*') != string::npos;

		OperationType type = OperationType::Null;
		if (line.find("+=") != string::npos) type = OperationType::PlusEquals;
		else if (line.find("-=") != string::npos) type = OperationType::MinusEquals;
		else if (line.find("*=") != string::npos) type = OperationType::MultiplyEquals;
		else if (line.find("/=") != string::npos) type = OperationType::DivideEquals;


		if (line.find("float ") != string::npos || line.find("int ") != string::npos) LoadFloat(line, variables);
		else if (type != OperationType::Null) InternalFloatCommand(line, variables, type);
		else if (equals && (add || sub || div || mul)) ArithmeticFloatCommand(line, variables);
		else if (equals) SetFloatCommand(line, variables);
		else LoadCommand(line, variables);	
	}
	return commands;
}
