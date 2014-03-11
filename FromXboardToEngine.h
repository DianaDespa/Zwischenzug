#pragma once
class FromXboardToEngine
{
public:
	FromXboardToEngine(void);
	~FromXboardToEngine(void);

	void xboardCommand(void);
	void newCommand(void);
	void quitCommand(void);
	void resignCommand(void);
	void forceCommand(void);
	void goCommand(void);
	void whiteCommand(void);
	void blackCommand(void);
	void moveCommand(char* command);
}