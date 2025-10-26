#include <iostream>
#include <unordered_map>
#include <string>
#include "olcConsoleGameEngine.h"
#include "InputHandler.h"

#define MOTIONS_1_SIZE 4
#define MOTIONS_5_SIZE 1

template <std::size_t N>
struct MotionInput {
	CommandSequence validCommands[N];
	std::string name = "INPUT_623";


	MotionInput() {}

	MotionInput(const std::string& name_)
		:name(name_) {}

	void checkValidCommands(std::unordered_map<std::string, bool>& buttonMap, InputHandler* inputHandler) {
		buttonMap[name] = false;
		for (std::size_t i = 0; i < N; ++i) {
			if (inputHandler->checkCommand(validCommands[i])) {
				buttonMap[name] = true;
			}
		}
	}

	void resetCommands() {
		for (std::size_t i = 0; i < N; ++i) {
			validCommands[i].commandTimer = 0;
			validCommands[i].commandNumber = 0;
			validCommands[i].executeTimer = 0;
		}

	}

};


class Demo : public olcConsoleGameEngine
{
public:
	Demo() 
	{
	}

	int ReadInputs()
	{
		int inputs = 0;

		if (m_keys[0x55].bHeld)
		{
			inputs |= ButtonIDs::LPH;
		}
		if (m_keys[0x49].bHeld)
		{
			inputs |= ButtonIDs::MP;
		}
		if (m_keys[0x4F].bHeld)
		{
			inputs |= ButtonIDs::HP;
		}

		if (m_keys[0x4A].bHeld)
		{
			inputs |= ButtonIDs::LK;
		}
		if (m_keys[0x4B].bHeld)
		{
			inputs |= ButtonIDs::MK;
		}
		if (m_keys[0x4C].bHeld)
		{
			inputs |= ButtonIDs::HK;
		}

		if (m_keys[0x44].bHeld)
		{
			inputs |= ButtonIDs::FORWARD;
		}
		if (m_keys[0x41].bHeld)
		{
			inputs |= ButtonIDs::BACK;
		}
		if (m_keys[0x53].bHeld)
		{
			inputs |= ButtonIDs::DOWN;
		}
		if (m_keys[0x57].bHeld)
		{
			inputs |= ButtonIDs::UP;
		}

		return inputs;
	}

protected:

	void clearCommands() {
		for (std::size_t i = 0; i < MOTIONS_1_SIZE; ++i) {
			_motions1[i].resetCommands();
		}
		for (std::size_t i = 0; i < MOTIONS_5_SIZE; ++i) {
			_motions5[i].resetCommands();
		}
	}

	virtual bool OnUserCreate()
	{
		input_Count = 0;
		m_fPlayerX = 10.0f;
		m_fPlayerY = 10.0f;
		tick = 0;

		buttons["INPUT_PRESS_LP"] = Button(FK_Input_Buttons.LP, false);
		buttons["INPUT_PRESS_MP"] = Button(FK_Input_Buttons.MP, false);
		buttons["INPUT_PRESS_HP"] = Button(FK_Input_Buttons.HP, false);

		buttons["INPUT_HOLD_LP"] = Button(FK_Input_Buttons.LP, true);
		buttons["INPUT_HOLD_MP"] = Button(FK_Input_Buttons.MP, true);
		buttons["INPUT_HOLD_HP"] = Button(FK_Input_Buttons.HP, true);

		buttons["INPUT_PRESS_LK"] = Button(FK_Input_Buttons.LK, false);
		buttons["INPUT_PRESS_MK"] = Button(FK_Input_Buttons.MK, false);
		buttons["INPUT_PRESS_HK"] = Button(FK_Input_Buttons.HK, false);

		buttons["INPUT_HOLD_LK"] = Button(FK_Input_Buttons.LK, true);
		buttons["INPUT_HOLD_MK"] = Button(FK_Input_Buttons.MK, true);
		buttons["INPUT_HOLD_HK"] = Button(FK_Input_Buttons.HK, true);

		_motions1[0] = MotionInput<1>("INPUT_236");
		_motions1[0].validCommands[0] = CommandSequence({ FK_Input_Buttons.DOWN, FK_Input_Buttons.DOWN_FORWARD, FK_Input_Buttons.FORWARD}, { -5, 10, 10 });
		_motions1[1] = MotionInput<1>("INPUT_214");
		_motions1[1].validCommands[0] = CommandSequence({ FK_Input_Buttons.DOWN, FK_Input_Buttons.DOWN_BACK, FK_Input_Buttons.BACK }, { -5, 10, 10 });
		_motions1[2] = MotionInput<1>("INPUT_63214");
		_motions1[2].validCommands[0] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN_FORWARD, FK_Input_Buttons.DOWN_BACK, FK_Input_Buttons.BACK }, { -5,12,12,12 });
		_motions1[3] = MotionInput<1>("INPUT_623");
		_motions1[3].validCommands[0] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN, FK_Input_Buttons.DOWN_FORWARD }, { -8,-12,-7 });

		_motions1[4] = MotionInput<1>("INPUT_CHARGE_BACK_FORWARD_30F");
		_motions1[4].validCommands[0] = CommandSequence({ FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { 130,10 });


		_motions5[0] = MotionInput<5>("INPUT_632146");
		_motions5[0].validCommands[0] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN_FORWARD, FK_Input_Buttons.DOWN, FK_Input_Buttons.DOWN_BACK, FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { -6,12,12,12,12,12 });
		_motions5[0].validCommands[1] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN, FK_Input_Buttons.DOWN_BACK, FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { -4,8,8,8,8 });
		_motions5[0].validCommands[2] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN_FORWARD, FK_Input_Buttons.DOWN, FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { -4,8,8,8,8 });
		_motions5[0].validCommands[3] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN, FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { -6,12,12,12 });
		_motions5[0].validCommands[4] = CommandSequence({ FK_Input_Buttons.FORWARD, FK_Input_Buttons.DOWN_FORWARD, FK_Input_Buttons.DOWN_BACK, FK_Input_Buttons.BACK, FK_Input_Buttons.FORWARD }, { -4,12,8,8,8 });

		for (const auto& element : buttons) {
			const auto& key = element.first;
			const auto& value = element.second;
			buttonMap[key] = false;
		}

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		tick++;
		inputs = ReadInputs();
		_handler.registerInputs(inputs);

		for (const auto& element : buttons) {
			const auto& key = element.first;
			const auto& value = element.second;
			if (_handler.checkCommand(buttons[key].ID, buttons[key].hold))
				buttonMap[key] = true;
			else
				buttonMap[key] = false;
		}

		for (std::size_t i = 0; i < MOTIONS_1_SIZE; ++i) {
			_motions1[i].checkValidCommands(buttonMap, &_handler);
		}
		for (std::size_t i = 0; i < MOTIONS_5_SIZE; ++i) {
			_motions5[i].checkValidCommands(buttonMap, &_handler);
		}
		//_motions1[1].checkValidCommands(buttonMap, &_handler);
		std::vector<std::string> possibleInputs = {
			"INPUT_632147896", "INPUT_412369874", "INPUT_63214", "INPUT_41236", "INPUT_623", "INPUT_421",
			"INPUT_214",  "INPUT_236",
			 
		};
		std::vector<std::string> possibleButton = {
			"INPUT_PRESS_LP", "INPUT_PRESS_MP", "INPUT_PRESS_HP",
			"INPUT_PRESS_LK", "INPUT_PRESS_MK", "INPUT_PRESS_HK"
		};

		for (std::size_t i = 0; i < 6; ++i) {
			if (buttonMap[possibleButton[i]]) {
				for (std::size_t j = 0; j < 8; ++j) {
					if (buttonMap[possibleInputs[j]]) {
						m_fPlayerX += 2.0f;
						commandList.push_back(possibleInputs[j]);
						buttonList.push_back(possibleButton[i]);
						clearCommands();
						++input_Count;
						break;
					}
				}
			}
		}


		Fill(0, 0, m_nScreenWidth, m_nScreenHeight, PIXEL_SOLID, 0);
		std::string var = ". . . .";
		Fill((int)m_fPlayerX, (int)m_fPlayerY, (int)m_fPlayerX + 5, (int)m_fPlayerY + 5, PIXEL_SOLID, 1);
		/*for (std::size_t i = input_Count; i > -1; i--) {
			FillCircle((int)m_fPlayerX, (int)m_fPlayerY, 10, PIXEL_SOLID, 1);
		}*/

		bool matching = helperFunction();
		
		std::string passwordDisplay = "";

		if (m_keys[0x52].bHeld) {
			passwordDisplay.clear();
			m_fPlayerX = 0.0f;
		}
		passwordDisplay.reserve(input_Count);
		for (std::size_t i = 0; i < input_Count; i++) {
			if (matching) {
				passwordDisplay.append("YES");
			}
			passwordDisplay.append(commandList[input_Count-1]);
		}
		std::wstring wsTmp(passwordDisplay.begin(), passwordDisplay.end());
		std::wstring wideString = std::to_wstring(input_Count);
		DrawString((int)m_fPlayerX, (int)m_fPlayerY, wsTmp, 1);
		_handler.update(tick);

		return true;
	}

	bool helperFunction() {
		if (targetcommandList.size() == commandList.size()) {
			for (int i = 0; i < commandList.size(); ++i) {
				if ((targetcommandList[i] != commandList[i]) || (targetbuttonList[i] != buttonList[i])) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

private:
	float m_fPlayerX;
	float m_fPlayerY;
	int input_Count;
	std::vector<std::string> commandList = {};
	std::vector<std::string> buttonList = {};
	std::vector<std::string> targetcommandList = {"INPUT_236", "INPUT_623", "INPUT_63214"};
	std::vector<std::string> targetbuttonList = {"INPUT_PRESS_LP","INPUT_PRESS_LP","INPUT_PRESS_LP" };
	InputHandler _handler = InputHandler();
	MotionInput<1> _motions1[MOTIONS_1_SIZE];
	MotionInput<5> _motions5[MOTIONS_1_SIZE];
	std::unordered_map<std::string, bool> buttonMap;
	std::unordered_map<std::string, Button> buttons;
	int inputs;
	int tick;
};

int main()
{
	Demo game;

	game.ConstructConsole(160, 100, 8, 8);
	game.Start();

	return 0;
}
