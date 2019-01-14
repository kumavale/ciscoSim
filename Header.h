#pragma once

#include <iostream>

#include <vector>


#define	CTRL_C			  0x03
#define	BACK				  0x08
#define	COMPLETION		0x09
#define	RETURN				0x0d
#define ESC				  	0x1b
#define UP					  0x48	// or Ctrl+P
#define DOWN				  0x50	// or Ctrl+N

//using namespace std;

enum {
	USER_EXEC_MODE,
	PRIVILEGED_EXEC_MODE,
	GLOBAL_CONFIGURATION_MODE,
	INTERFACE_CONFIGURATION_MODE,
	CONFIG_VLAN_MODE,
	LINE_CONFIGURATION_MODE,
	ROM_MONITOR,
	MODE_MAX,
};

std::string prompto[MODE_MAX] = {
	"> ",				        // USER_EXEC_MODE,
	"# ",				        // PRIVILEGED_EXEC_MODE,
	"(config)# ",	  	  // GLOBAL_CONFIGURATION_MODE,
	"(config-if)# ",		// INTERFACE_CONFIGURATION_MODE,
	"(config-vlan)# ",	// CONFIG_VLAN_MODE,
	"(config-line)# ",	// LINE_CONFIGURATION_MODE,
	"ROM> ",				    // ROM_MONITOR,
};



int curX;  // PS1 + command Length
int mode;
int histMax = 10;

unsigned int limit;
unsigned int limitM;
unsigned int limitS;

std::string s; // current command
std::string h; // hostname
std::string PS1 = prompto[USER_EXEC_MODE];
std::string bunner;
std::string MAC = "00.00.00.00.00.00";

//  In fact, the default is only 10.    But for learning ;)
std::vector<std::string> commandBuffer[MODE_MAX];

bool suspend = true;
bool reload;
bool invalidCommand;
bool ambiguousCommand;

time_t now;
time_t lastTouch;

int main();
void init();
void title();
void timer();
void display(std::string &_s);
void prediction(std::string &_s);
void completion(std::string &_s);
void checkCommand(std::string _s);
void inputConsole(std::string &_s);

std::string loopC(std::string _s, const int _n);
