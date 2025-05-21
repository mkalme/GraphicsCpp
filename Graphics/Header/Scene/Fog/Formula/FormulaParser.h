#pragma once
#include "CallStack.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class StringStream {
public:
	std::string String;
	int Index = 0;

	StringStream(std::string string) {
		String = string;
	}

	char Next() {
		return String[Index++];
	}

	bool HasNext() {
		return Index < String.size();
	}
};

class FormulaParser
{
public:
	std::map<std::string, int> Functions = {
		{"sqrt", FUNCTION_SQRT},
		{"add", FUNCTION_ADD},
		{"subtract", FUNCTION_SUBTRACT},
		{"multiply", FUNCTION_MULTIPLY},
		{"divide", FUNCTION_DIVIDE},
		{"exponent", FUNCTION_EXPONENT},
		{"capifmax", FUNCTION_CAPIFMAX},
		{"capifmin", FUNCTION_CAPIFMIN},
		{"ln", FUNCTION_LN},
		{"abs", FUNCTION_ABS}
	};

	virtual CallStack* Parse(std::string formula) {
		std::vector<StackCommand> commands = std::vector<StackCommand>();
		StringStream stream = StringStream(formula);

		ParseFunction(stream, commands);

		return new CallStack(commands);
	}
protected:
	virtual void ParseFunction(StringStream &stream, std::vector<StackCommand> &commands) {
		while (stream.HasNext() && stream.Next() != ')') {
			stream.Index--;

			if (stream.Next() == '.') {
				std::string functionName = GetFunctionName(stream);				
				ParseFunction(stream, commands);
				
				commands.push_back(StackCommand(Functions[functionName], NAN));
			}else {
				stream.Index--;
				commands.push_back(GetConstant(stream));
			}
		}
	}

	virtual std::string GetFunctionName(StringStream& stream) {
		int begin = stream.Index;
		while (stream.Next() != '(');
		return stream.String.substr(begin, stream.Index - begin - 1);
	}

	virtual StackCommand GetConstant(StringStream& stream) {
		int begin = stream.Index;

		while (stream.HasNext()) {
			char c = stream.Next();
			if (c == 'T') break;

			if (c == ')') {
				stream.Index--;
				break;
			}

			char cc = stream.Next();
			bool nextIsFunction = c == '.' && cc < '0' || cc > '9';
			stream.Index--;

			if (nextIsFunction) {
				stream.Index--;
				break;
			}
		}

		std::string constant = stream.String.substr(begin, stream.Index - begin);

		if (constant == "T") return StackCommand(CONSTANT_T, NAN);
		return StackCommand(CONSTANT_NORMAL, std::stod(constant));
	}
};

