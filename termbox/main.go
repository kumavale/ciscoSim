package main

import (
	"fmt"
	"github.com/nsf/termbox-go"
)

var PS1 string = "Switch> "
var io string = ""
var cl int = 0
var bufio = ""
var bufp = ""

func drawLine(x, y int, str string) {
	//color := termbox.ColorDefault
	color := termbox.Attribute(16)
	backgroundColor := termbox.ColorDefault
	runes := []rune(str)

	for i := 0; i < len(runes); i += 1 {
		termbox.SetCell(x+i, y, runes[i], color, backgroundColor)
	}
}

func draw() {
	//termbox.Clear(termbox.ColorDefault, termbox.ColorDefault)

	drawLine(0, cl, fmt.Sprintf("%s%s", PS1, io))

	termbox.Flush()
}

func pollEvent() {
	draw()
	for {
		switch ev := termbox.PollEvent(); ev.Type {
		case termbox.EventKey:
			switch ev.Key {
			case termbox.KeyCtrlC:
				return
			case termbox.KeyEnter:
				cl++
				if io == "exit" {
					return
				}
				bufio = io
				bufp = PS1
				io = ""
				draw()
			case termbox.KeyBackspace:
				if io != "" {
					io = io[0 : len(io)-1]
					drawLine(len(PS1)+len(io), cl, " ")
					draw()
				}
			default:
				io += fmt.Sprintf("%c", ev.Ch)
				draw()
			}
		default:
			draw()
		}
	}
}

func main() {
	err := termbox.Init()
	if err != nil {
		panic(err)
	}

	defer termbox.Close()

	termbox.SetOutputMode(termbox.Output256)

	pollEvent()
}
