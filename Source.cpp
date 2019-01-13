
#include "Header.h"

#include <conio.h>
#include <time.h>

#include <Windows.h>
#include <iostream>


void init() {

	SetConsoleTitle("ciscoSim");

	// reading and loading to config file
	{
		cout << "C2960 Boot Loader (C2960-HBOOT-M) Version 12.2(25r)FX, RELEASE SOFTWARE (fc4)" << endl;
		cout << "Cisco WS-C2960-24TT (RC32300) processor (revision C0) with 21039K bytes of memory." << endl;
		cout << "2960-24TT starting..." << endl;

		cout << "Base ethernet MAC Address: ";
		for (int i = 3; i < 6; i++) { MACADDR[i] = rand() % 255; }
		printf("%02X%02X.%02X%02X.%02X%02X\n", MACADDR[0], MACADDR[1], MACADDR[2], MACADDR[3], MACADDR[4], MACADDR[5]);

		cout << "Xmodem file system is available." << endl;
		cout << "Initializing Flash..." << endl;
		cout << "flashfs[0]: 1 files, 0 directories" << endl;
		cout << "flashfs[0]: 0 orphaned files, 0 orphaned directories" << endl;
		cout << "flashfs[0]: Total bytes: 64016384" << endl;
		cout << "flashfs[0]: Bytes used: 4414921" << endl;
		cout << "flashfs[0]: Bytes available: 59601463" << endl;
		cout << "flashfs[0]: flashfs fsck took 1 seconds." << endl;
		cout << "...done Initializing Flash.\n" << endl;

		cout << "Boot Sector Filesystem (bs:) installed, fsid: 3" << endl;
		cout << "Parameter Block Filesystem (pb:) installed, fsid: 4\n\n" << endl;

		cout << "Loading \"flash:/c2960-lanbase-mz.122-25.FX.bin\"..." << endl;
			for (int i = 0; i++ < 74; cout << (i<74?"#":" [OK]\n")) Sleep(32);
//		cout << "########################################################################## [OK]" << endl;
		cout << "              Restricted Rights Legend\n" << endl;

		cout << "Use, duplication, or disclosure by the Government is" << endl;
		cout << "subject to restrictions as set forth in subparagraph" << endl;
		cout << "(c) of the Commercial Computer Software - Restricted" << endl;
		cout << "Rights clause at FAR sec. 52.227-19 and subparagraph" << endl;
		cout << "(c) (1) (ii) of the Rights in Technical Data and Computer" << endl;
		cout << "Software clause at DFARS sec. 252.227-7013.\n" << endl;

		cout << "           cisco Systems, Inc." << endl;
		cout << "           170 West Tasman Drive" << endl;
		cout << "           San Jose, California 95134-1706\n\n\n\n" << endl;

		cout << "Cisco IOS Software, C2960 Software (C2960-LANBASE-M), Version 12.2(25)FX, RELEASE SOFTWARE (fc1)" << endl;
		cout << "Copyright (c) 1986-2005 by Cisco Systems, Inc." << endl;
		cout << "Compiled Wed 12-Oct-05 22:05 by pt_team" << endl;
		cout << "Image text-base: 0x80008098, data-base: 0x814129C4\n\n\n" << endl;

		cout << "Cisco WS-C2960-24TT (RC32300) processor (revision C0) with 21039K bytes of memory.\n\n" << endl;

		cout << "24 FastEthernet/IEEE 802.3 interface(s)" << endl;
		cout << "2 Gigabit Ethernet/IEEE 802.3 interface(s)\n" << endl;

		cout << "63488K bytes of flash-simulated non-volatile configuration memory." << endl;
		cout << "Base ethernet MAC Address       : ";
		printf("%02X%02X.%02X%02X.%02X%02X\n", MACADDR[0], MACADDR[1], MACADDR[2], MACADDR[3], MACADDR[4], MACADDR[5]);
		cout << "Motherboard assembly number     : 73-9832-06" << endl;
		cout << "Power supply part number        : 341-0097-02" << endl;
		cout << "Motherboard serial number       : FOC103248MJ" << endl;
		cout << "Power supply serial number      : DCA102133JA" << endl;
		cout << "Model revision number           : B0" << endl;
		cout << "Motherboard revision number     : C0" << endl;
		cout << "Model number                    : WS-C2960-24TT" << endl;
		cout << "System serial number            : FOC1033Z1EY" << endl;
		cout << "Top Assembly Part Number        : 800-26671-02" << endl;
		cout << "Top Assembly Revision Number    : B0" << endl;
		cout << "Version ID                      : V02" << endl;
		cout << "CLEI Code Number                : COM3K00BRA" << endl;
		cout << "Hardware Board Revision Number  : 0x01\n\n" << endl;

		cout << "Switch   Ports  Model              SW Version              SW Image" << endl;
		cout << "------   -----  -----              ----------              ----------" << endl;
		cout << "*    1   26     WS-C2960-24TT      12.2                    C2960-LANBASE-M\n" << endl;

		cout << "Cisco IOS Software, C2960 Software (C2960-LANBASE-M), Version 12.2(25)FX, RELEASE SOFTWARE (fc1)" << endl;
		cout << "Copyright (c) 1986-2005 by Cisco Systems, Inc." << endl;
		cout << "Compiled Wed 12-Oct-05 22:05 by pt_team\n" << endl;

		cout << "Press RETURN to get started!\n" << endl;
		while (suspend) {
			switch (_getch())
			{
			case RETURN:
				suspend = false;
				break;
			//case ESC:
      case CTRL_C:
				exit(0);
			default:
				break;
			}
		}
		suspend = true;
		cout << endl;
	}

	{ // varriable  _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

		if (bunner != "") cout << bunner;
		h = "Switch";
		mode = USER_EXEC_MODE;
		PS1 = h + prompto[mode];

		limitM = 10;
		limitS = 0;

		histMax = 10;

		// like memcpy(runningconfig, startupconfig, sizeos(startupconfig));

	} // _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


	reload = false;
	curX = sizeof(PS1);

	limit = (limitM * 60) + limitS;

	//commandBuffer->clear();
	for (int i = 0; i < MODE_MAX; i++)
		commandBuffer[i].clear();

	lastTouch = time(nullptr);
}

void prediction(string &_s) {
	// コマンド表から渡された文字列を元に検索し、候補を出力。


	// 補完候補が見つからない場合、エラー出力 or ignore ??
	// if(一致行数 == 0)
	{
		cout << "\n\% Unrecognized command" << endl;
	}
}

void completion(string &_s) {
	int matchLine = 0;
	string predicted;

	{
		//if(find) matchLine++;

		if (matchLine == 1) _s = predicted;
	}
}

void inputConsole(string &_s) {

	_s.clear();
	char _c;
	int cnt = 0;
	int pLen;
	int cb;
	string sb;


	PS1 = h + prompto[mode];
	pLen = curX = sizeof(PS1);


	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;


	cout << "\r" + PS1;


	while (1) {
		if (_kbhit() && (_c = _getch())) {
			if (_c == 0xFFFFFFE0)
			{
				_c = _getch();
				if ((cb = commandBuffer[mode].size()) != 0) {
					if (_c == UP) {
						if (cb > cnt) {
							cnt++;
							sb = commandBuffer[mode][cb - cnt];
							curX = sizeof(sb) + pLen;
							_s = sb;
							cout << "\r" + loopS(" ", columns - 1);
							cout << "\r" + PS1 + sb;
						}
					}
					else if (_c == DOWN) {
						if (cnt > 1) {
							cnt--;
							sb = commandBuffer[mode][cb - cnt];
							cout << "\r" + loopS(" ", curX);
							cout << "\r" + PS1 + sb;
							curX = sizeof(sb) + pLen;
							_s = sb;
						}
						else if (cnt == 1) {
							cout << "\r" + loopS(" ", columns - 1);
							cout << "\r" + PS1;
							cnt = 0;
							_s = "";
						}
					}
				}

				continue;
			}

			//keybd_event()

			switch (_c)
			{
			case BACK:
				if ((curX > pLen) && !_s.empty()) {
					cout << "\b ";
					_s.erase(_s.end() - 1);
					curX--;
					cout << _c;
				}
				break;
			case COMPLETION: completion(_s); break;
			case RETURN:
				cout << endl;
				if (s != "") return;
				cout << PS1;
				break;
			case CTRL_C: exit(0); break;
			default:
        if (_c >= 32 && _c <= 125) {
          _s += _c;
          curX++;
          cout << _c;
          break;
        }
			}
			//display(_s);

			if (_c == '?') {
				//system("pause");
				prediction(_s);
				cout << "\b ";
				_s.erase(_s.end() - 1);
				display(_s);
				curX--;
			}

			lastTouch = time(nullptr);
		}
		timer();
	}
}

void display(string &_s) {
	cout << "\r" + PS1 + _s;
}

string loopS(string _s, const int _n) {
	string _str;
	for (int i = 0; i < _n; i++)
		_str += _s;
	return _str;
}

void title() {
	cout << loopS("\n",10) << "Switch con0 is now available" << endl;
	cout << loopS("\n",6) << "Press RETURN to get started!" << loopS("\n",12) << endl;
	while (suspend) {
		switch (_getch())
		{
		case RETURN:
			suspend = false;
			break;
		//case ESC:
    case CTRL_C:
			exit(0);
		default:
			break;
		}
	}
	cout << endl;
	mode = USER_EXEC_MODE;
	lastTouch = time(nullptr);
	suspend = true;
	PS1 = h + prompto[mode];
	cout << "\r" + PS1;
}

void checkCommand(string _s) {

	int i = 0;
	vector<string> idxBuffer;
	invalidCommand = false;
	ambiguousCommand = false;



	// Pack space
	for (i = 0; _s[i] != '\0'; i++)
		if (_s[i] == ' ') if (_s[i + 1] == ' ') _s.erase(_s.begin()+i--);

	// Comment
	if (_s[0] == '!') return;

	// Prohibit single space
	if (_s == " ") return;

	// Add space to last
	if (*_s.rbegin() != ' ') _s = _s + " ";



	commandBuffer[mode].push_back(""); // initiarization

	for (i = 0; _s[i] != '\0'; i++) {
	if (_s[0] == ' ') _s.erase(_s.begin() + 0);
		if (_s[i] == ' ') {
			idxBuffer.push_back(_s.substr(0, i));


			// Add to last element
			commandBuffer[mode][commandBuffer[mode].size() - 1] += _s.substr(0, i + 1);


			_s.erase(_s.begin() + 0, _s.begin() + i);
			i = 0;
		}
	}


	// If over histMax, delete fisrt element
	if (commandBuffer[mode].size() > (unsigned int)histMax)
		commandBuffer[mode].erase(commandBuffer[mode].begin());

	// Erase last space
	commandBuffer[mode].back().pop_back();

	int cb = commandBuffer[mode].size();
	if (cb > 1 && commandBuffer[mode][cb - 1] == commandBuffer[mode][cb - 2])
		commandBuffer[mode].pop_back();



	// Provisional => JSON  database
	i = 0;
	switch (mode) {
	case USER_EXEC_MODE: {
		if (idxBuffer[i] == "en" || idxBuffer[i] == "ena" || idxBuffer[i] == "enab" || idxBuffer[i] == "enabl" || idxBuffer[i] == "enable") {
			mode = PRIVILEGED_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "ex" || idxBuffer[i] == "exi" || idxBuffer[i] == "exit") {
			title();
			break;
		}

		invalidCommand = true;
		break;
	}

	case PRIVILEGED_EXEC_MODE: {
		if (idxBuffer[i] == "disa" || idxBuffer[i] == "disab" || idxBuffer[i] == "disable") {
			mode = USER_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "conf" || idxBuffer[i] == "configure") {
			if (idxBuffer.size() != 1) {
				i++;
				if (idxBuffer[i] == "t" || idxBuffer[i] == "terminal") {
					mode = GLOBAL_CONFIGURATION_MODE;
					cout << "Enter configuration commands, one per line.  End with CNTL/Z." << endl;
					break;
				}
			}
			ambiguousCommand = true;
		}
		if (idxBuffer[i] == "reload") {
			reload = true;
			cout << "System configuration has been modified.Save ? [yes / no] : ";
			string yn;
			cin >> yn;
			//if (yn == "yes") memcpy(startupconfig, runningconfig, sizeof(runningconfig));
			//else if (yn == "no")
			cout << "Proceed with reload ? [confirm]";
			cin >> yn;
			break;
		}

		invalidCommand = true;
		break;
	}

	case GLOBAL_CONFIGURATION_MODE: {
		if (idxBuffer[i] == "exi" || idxBuffer[i] == "exit" || idxBuffer[i] == "end") {
			mode = PRIVILEGED_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "hostname") {
			h = idxBuffer[++i];
			break;
		}

		invalidCommand = true;
		break;
	}

	case INTERFACE_CONFIGURATION_MODE: {
		if (idxBuffer[i] == "end") {
			mode = PRIVILEGED_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "ex" || idxBuffer[i] == "exi" || idxBuffer[i] == "exit") {
			mode = GLOBAL_CONFIGURATION_MODE;
			break;
		}

		invalidCommand = true;
		break;
	}

	case CONFIG_VLAN_MODE: {
		if (idxBuffer[i] == "end") {
			mode = PRIVILEGED_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "ex" || idxBuffer[i] == "exi" || idxBuffer[i] == "exit") {
			mode = GLOBAL_CONFIGURATION_MODE;
			break;
		}

		invalidCommand = true;
		break;
	}

	case LINE_CONFIGURATION_MODE: {
		if (idxBuffer[i] == "end") {
			mode = PRIVILEGED_EXEC_MODE;
			break;
		}
		if (idxBuffer[i] == "ex" || idxBuffer[i] == "exi" || idxBuffer[i] == "exit") {
			mode = GLOBAL_CONFIGURATION_MODE;
			break;
		}

		invalidCommand = true;
		break;
	}

	case ROM_MONITOR: {

	}break;
	default:
		break;
	} //*/

	if (invalidCommand) {
		//cout << "% Unknown command or computer name, or unable to find computer address" << endl;
		cout << loopS(" ", PS1.length()) + "^" << endl;
		cout << "\% Invalid input detected at '^' marker.\n" << endl;
		commandBuffer[mode].pop_back();
	}
	else if (ambiguousCommand) {
		cout << "\% Ambiguous command: \"" << idxBuffer[i] << "\"" << endl;
		commandBuffer[mode].pop_back();
	}

}

void timer() {
	if (now != time(nullptr)) {
		now = time(nullptr);
		if (now - lastTouch == limit) title();
	}
}

void test() {
	for (int i=0;;) {
		printf("\rSwitch>i:%d\nRouter>i:%d",i++ , i++);
	}
}

int main() {
  //test();
  init();
	while (1) {
		inputConsole(s);
		checkCommand(s);
		if (reload) init();
	}
	//system("cls");

	return 0;
}
