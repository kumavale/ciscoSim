package main

import (
	"fmt"
)

/*
#ifdef _WIN64
	#include <conio.h>
#endif

#ifdef __linux__
	#include <stdio.h>
	#include <termios.h>
	#include <unistd.h>
	int _getch( ) {
		struct termios oldt,
		newt;
		int ch;
		tcgetattr( STDIN_FILENO, &oldt );
		newt = oldt;
		newt.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newt );
		ch = getchar();
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
		return ch;
	}


int getch(){
    #include <unistd.h>
    int buf=0;
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
    //printf("%c",buf);
    return buf;
 }
#endif
//*/
import "C"

var h = "Switch"
var pr = "> "
var PS1 = h + pr
var io = ""
var his [][]string
var m = USER_EXEC

const (
	USER_EXEC = iota
	PRIVILEGED_EXEC
	GLOBAL_CONFIGURATION
	INTERFACE_CONFIGURATION
	CONFIG_VLAN
	VLAN_CONFIGURATION
	LINE_CONFIGURATION
)

func draw() {
	fmt.Printf("\r%s%s", PS1, io)
}

func pollEvent() {
	draw()
	for {
		c := C.getch()
		switch c {
		case 3:
			return
		case 13:
			fmt.Printf("\n")
			if io == "exit" {
				return
			}
			//his[m] = append(his[m], io)
			io = ""
			draw()
		case 8:
			if io != "" {
				io = io[0 : len(io)-1]
				fmt.Printf("\033[D \033[D")
				draw()
			}
		default:
			if c >= 32 && c <= 125 {
				io += fmt.Sprintf("%c", c)
				draw()
			}
		}
	}
}

func main() {
	pollEvent()
	fmt.Printf("\n")
}
