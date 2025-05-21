#pragma once
#include <vector>

#define CONSTANT_NORMAL 0
#define CONSTANT_T 1
#define FUNCTION_SQRT 2
#define FUNCTION_ADD 3
#define FUNCTION_SUBTRACT 4
#define FUNCTION_MULTIPLY 5
#define FUNCTION_DIVIDE 6
#define FUNCTION_EXPONENT 7
#define FUNCTION_CAPIFMAX 8
#define FUNCTION_CAPIFMIN 9
#define FUNCTION_LN 10
#define FUNCTION_ABS 11

struct StackCommand {
public:
	int Type;
	double AdditionalValue;

	StackCommand(int type, double additionalValue) {
		Type = type;
		AdditionalValue = additionalValue;
	}
};

class CallStack
{
public:
	CallStack(std::vector<StackCommand> commands) {
		m_commands = commands;
		SetMaxStackSize();
	}

	double GetValue(double tConstant) {
		double* memory = (double*)_alloca(m_maxStackSize * sizeof(double));
		int index = -1;

		for (int i = 0; i < m_commands.size(); i++) {
			StackCommand command = m_commands[i];
			switch (command.Type){
				case CONSTANT_NORMAL:
					memory[++index] = command.AdditionalValue;
					break;
				case CONSTANT_T:
					memory[++index] = tConstant;
					break;
				case FUNCTION_SQRT:
					if (memory[index] < 0) return 0;
					memory[index] = sqrt(memory[index]);
					break;
				case FUNCTION_ADD:
					memory[--index] = memory[index] + memory[index + 1];
					break;
				case FUNCTION_SUBTRACT:
					memory[--index] = memory[index] - memory[index + 1];
					break;
				case FUNCTION_MULTIPLY:
					memory[--index] = memory[index] * memory[index + 1];
					break;
				case FUNCTION_DIVIDE:
					memory[--index] = memory[index] / memory[index + 1];
					break;
				case FUNCTION_EXPONENT:
					memory[--index] = pow(memory[index], memory[index + 1]);
					break;
				case FUNCTION_CAPIFMAX:
					memory[--index] = fmin(memory[index], memory[index + 1]);
					break;
				case FUNCTION_CAPIFMIN:
					memory[--index] = fmax(memory[index], memory[index + 1]);
					break;
				case FUNCTION_LN:
					if (memory[index] <= 0) return 0;
					memory[index] = log(memory[index]);
					break;
				case FUNCTION_ABS:
					memory[index] = fabsf(memory[index]);
					break;
			}
		}

		return memory[index];
	}
private:
	int m_maxStackSize = 0;
	std::vector<StackCommand> m_commands = std::vector<StackCommand>();

	void SetMaxStackSize() {
		int currentStackSize = 0;
		for (int i = 0; i < m_commands.size(); i++) {
			StackCommand command = m_commands[i];

			switch (command.Type) {
				case CONSTANT_NORMAL:
				case CONSTANT_T:
					currentStackSize++;
					break;
				case FUNCTION_ADD:
				case FUNCTION_SUBTRACT:
				case FUNCTION_MULTIPLY:
				case FUNCTION_DIVIDE:
				case FUNCTION_EXPONENT:
				case FUNCTION_CAPIFMAX:
				case FUNCTION_CAPIFMIN:
					currentStackSize--;
					break;
			}

			m_maxStackSize = fmax(m_maxStackSize, currentStackSize);
		}
	}
};