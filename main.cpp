
#include "Header.h"

#include <time.h>
#include <filesystem>

#ifdef _WIN32
  #include <conio.h>
  #include <Windows.h>
#else
// ToDo
char _getch(){
  #include <unistd.h>   //_getch*/
  #include <termios.h>  //_getch*/
  char buf=0;
  struct termios old={0};
  fflush(stdout);
  if(tcgetattr(0, &old)<0)
    perror("tcsetattr()");
  old.c_lflag&=~ICANON;
  old.c_lflag&=~ECHO;
  old.c_cc[VMIN]=1;
  old.c_cc[VTIME]=0;
  if(tcsetattr(0, TCSANOW, &old)<0)
    perror("tcsetattr ICANON");
  if(read(0,&buf,1)<0)
    perror("read()");
  old.c_lflag|=ICANON;
  old.c_lflag|=ECHO;
  if(tcsetattr(0, TCSADRAIN, &old)<0)
    perror ("tcsetattr ~ICANON");
  printf("%c\n",buf);
  return buf;
 }
#endif

void init() {
	// reading and loading to config file
	{
    boot(IOS);

    //copyFile("flash/config.text", "flash/running-config");

//std::ifstream ifs(running_config, std::ios::in | std::ios::binary);
//char c;
//if(!ifs) std::cout << "error!" << std::endl;
//while (ifs.get(c)) {
//  std::cout << c ;
//}

    std::cout << "Press RETURN to get started!\n\n";

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
    std::cout << std::endl;
	}

	{ // varriable  _/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

		if (bunner != "") std::cout << bunner;
		h = "Switch";
		mode = USER_EXEC_MODE;
		PS1 = h + prompto[mode];

		limitM = 10;
		limitS = 0;
		//limitM = 0;   // for debug
		//limitS = 10;  // for debug

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

void prediction(std::string &_s) {
	// コマンド表から渡された文字列を元に検索し、候補を出力。


	// 補完候補が見つからない場合、エラー出力 or ignore ??
	// if(一致行数 == 0)
	{
    std::cout << "\n\% Unrecognized command" << std::endl;
	}
}

void completion(std::string &_s) {
	int matchLine = 0;
  std::string predicted;

	{
		//if(find) matchLine++;

		if (matchLine == 1) _s = predicted;
	}
}

void inputConsole(std::string &_s) {

	_s.clear();
	char _c;
	int cnt = 0;
	int pLen;
	int cb;
  std::string sb;


	PS1 = h + prompto[mode];
	pLen = curX = sizeof(PS1);


	CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;


  std::cout << "\r" << PS1;


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
              std::cout << "\r" + loopC(" ", columns - 1);
              std::cout << "\r" + PS1 + sb;
						}
					}
					else if (_c == DOWN) {
						if (cnt > 1) {
							cnt--;
							sb = commandBuffer[mode][cb - cnt];
              std::cout << "\r" + loopC(" ", curX);
							std::cout << "\r" + PS1 + sb;
							curX = sizeof(sb) + pLen;
							_s = sb;
						}
						else if (cnt == 1) {
							std::cout << "\r" + loopC(" ", columns - 1);
							std::cout << "\r" + PS1;
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
				//if ((curX > pLen) && !_s.empty()) {
				if (!_s.empty()) {
					std::cout << "\b \b";
					_s.erase(_s.end() - 1);
					curX--;
				}
				break;
			case COMPLETION: completion(_s); break;
			case RETURN:
				std::cout << std::endl;
				if (s != "") return;
				std::cout << PS1;
				break;
			case CTRL_C: exit(0); break;
			default:
        if (_c >= 32 && _c <= 125) {
          _s += _c;
          curX++;
          std::cout << _c;
          break;
        }
			}
			//display(_s);

			if (_c == '?') {
				prediction(_s);
				_s.erase(_s.end() - 1);
				display(_s);
				curX--;
			}

			lastTouch = time(nullptr);
		}
		timer();
	}
}

void display(std::string &_s) {
	std::cout << "\r" + PS1 + _s << std::flush;
}

std::string loopC(std::string _s, const int _n) {
  std::string _str;
	for (int i = 0; i < _n; i++)
		_str += _s;
	return _str;
}

void title() {
	s.clear();
	std::cout << loopC("\n",10) << "Switch con0 is now available\n";
	std::cout << loopC("\n",6) << "Press RETURN to get started!" << loopC("\n",13);
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
	std::cout << std::endl;
	mode = USER_EXEC_MODE;
	lastTouch = time(nullptr);
	suspend = true;
	PS1 = h + prompto[mode];
	std::cout << PS1;
}

void checkCommand(std::string _s) {

	int i = 0;
  std::vector<std::string> idxBuffer;
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
					std::cout << "Enter configuration commands, one per line.  End with CNTL/Z." << std::endl;
					break;
				}
			}
			ambiguousCommand = true;
		}
		if (idxBuffer[i] == "reload") {
			reload = true;
			std::cout << "System configuration has been modified.Save ? [yes / no] : ";
      std::string yn;
      std::cin >> yn;
			//if (yn == "yes") memcpy(startupconfig, runningconfig, sizeof(runningconfig));
			//else if (yn == "no")
			std::cout << "Proceed with reload ? [confirm]";
      std::cin >> yn;
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
		//std::cout << "% Unknown command or computer name, or unable to find computer address" << std::endl;
		std::cout << loopC(" ", PS1.length()) + "^" << std::endl;
		std::cout << "\% Invalid input detected at '^' marker.\n" << std::endl;
		commandBuffer[mode].pop_back();
	}
	else if (ambiguousCommand) {
		std::cout << "\% Ambiguous command: \"" << idxBuffer[i] << "\"" << std::endl;
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

void boot(std::string _IOS){
  // IOSのファイルはテキストファイルでは無く、実行ファイルにし、
  // この boot関数 では、その実行ファイルを実行する
  std::ifstream ifs(_IOS, std::ios::in);
  std::string st;
  if (!ifs) {
    mode = ROM_MONITOR;
    return;
  }
  while (getline(ifs, st)) {
    st = Replace(st, "\\n", "\n");
    if (st == "!roading!") {
      getline(ifs, st);
      st = Replace(st, "\\n", "\n");
      std::cout << "Loading \"flash:/" << IOS << "\"...\n";
		  for (int i = 0; i++ < 74; std::cout << (i<74?"#":" [OK]\n")) Sleep(32);
    }
    std::cout << st ;
  }
}

std::string Replace( std::string String1, std::string String2, std::string String3 ) {
    std::string::size_type  Pos( String1.find( String2 ) );
    while( Pos != std::string::npos ) {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
    return String1;
}

bool is_file_exists(const std::string& str) {
  std::ifstream fs(str);
  return fs.is_open();
}

/*
bool copyFile(std::string src, std::string dst){
  char c;
  std::ifstream ifs(src, std::ios::in | std::ios::binary);
  std::ofstream ofs(dst, std::ios::out);
  if (!ifs) return false;
  if (!ofs) return false;

  std::filesystem::copy(src, dst);

  ifs.close();
  ofs.close();

  if (!ifs) return false;
  if (!ofs) return false;

  return true;
} //*/

int main(int argc, char* argv[]) {
	SetConsoleTitle("ciscoSim");
  if (argc == 2) {
    if (is_file_exists(argv[1])) {
      IOS=argv[1];
    } else {
      std::cout << "invalid args..." << std::endl;
		  exit(0);
    }
  }
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
