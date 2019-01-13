#pragma once

#include <string>

#include <vector>


//#define USER_EXEC_MODE					        ">"
//#define PRIVILEGED_EXEC_MODE				    "#"
//#define GLOBAL_CONFIGURATION_MODE			  "(config)#"
//#define INTERFACE_CONFIGURATION_MODE		"(config-if)#"
//#define CONFIG_VLAN_MODE					      "(config-vlan)#"
//#define LINE_CONFIGURATION_MODE			    "(config-line)#"
//#define ROM_MONITOR						          "ROM>"

#define	CTRL_C			  0x03
#define	BACK				  0x08
#define	COMPLETION		0x09
#define	RETURN				0x0d
#define ESC				  	0x1b
#define UP					  0x48	// or Ctrl+P
#define DOWN				  0x50	// or Ctrl+N


using namespace std;


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

string prompto[MODE_MAX] = {
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
int MACADDR[6] = {
	0x43, 0x49, 0x53	// OUI
};

unsigned int limit;
unsigned int limitM;
unsigned int limitS;

string s; // current command
string h; // hostname
string PS1 = prompto[USER_EXEC_MODE];
string bunner;
string MAC;

//  In fact, the default is only 10.    But for learning ;)
vector<string> commandBuffer[MODE_MAX];

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
void display(string &_s);
void prediction(string &_s);
void completion(string &_s);
void checkCommand(string _s);
void inputConsole(string &_s);

string loopS(string _s, const int _n);
