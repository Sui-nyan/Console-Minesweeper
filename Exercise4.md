# Exercise 4

## Minesweeper

In the previous exercise we layed the groundwork for the minesweeper game. In this exercise we will finish it!
We have included an .exe file containing an example solution, so feel free to use it as a reference (references folder).

Most of the game logic is pretty simple to implement. Here are the rules as a recap:

- The player can either flag or reveal a cell.
- Only cells that have not been revealed yet, can be flagged
- Flagged cells will return to being regular not revealed cells, when they are flagged again (flags can be removed by pressing the same button again)
- When a bomb is revealed the game is instantly lost
- When a cell that is not a bomb is revealed, two things may happen:
  - a. The cell has atleast one bomb as its neighbor, in which case only this cell will be revealed
  - b. The cell has no bombs as its neighbor, so all adjacent cells will be revealed. If any of the adjacent cells also have no bombs as their neighbor, they will also reveal all of their adjacent cells.
- When all non-bomb cells are revealed and all bomb cells are flagged, the game is won
- The player will continously reveal or flag cells until the game is either won or lost through the conditions described above.

## Implementation Tips

Most of the rules above are relatively straight forward to implement, with the exception of the cascading reveal of cells with no bombs as their neighbors. There are multiple approaches for this.
You could for example use a flood-fill algorithm (https://www.geeksforgeeks.org/flood-fill-algorithm/) for this.

In general you should think about how you can split up the different rules into their own seperate functions, e.g. a function that checks if the game is lost or won, a function that handles flagging a cell and one that handles revealing a cell etc.

Another more complex topic is Input Handling. Ususally we only take keyboard inputs using std::cin, but in our case, it would be nice to use mouse inputs as well. Unfortunately, since we are using a console application the code for handling such inputs is usually platform specific.

Here is some example code, how you could handle inputs in windows.

```cpp
#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hIn;
	INPUT_RECORD InRec;
	DWORD NumRead;
	DWORD fdwMode;

	hIn = GetStdHandle(STD_INPUT_HANDLE);

	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, fdwMode))
		return -1;

	while (true)
	{
		ReadConsoleInput(hIn,
			&InRec,
			1,
			&NumRead);

		switch (InRec.EventType)
		{
		case MOUSE_EVENT:
			COORD mPos = InRec.Event.MouseEvent.dwMousePosition; //where is the mouse in the window
			DWORD mouseState = InRec.Event.MouseEvent.dwButtonState; //which mouse button is pressed
		}
	}
}
```

Using the mouse is nice, but do not worry too much about it, if you cannot get it running. You can also use simple keyboard inputs using std::cin and specifying the coordinates where you want to reveal/flag, by typing them in.

![The application running](./img/minesweeper_ex04.gif)

## Submission

Submission is due until 01.06.2024. Please upload the source code as a .zip file, as well as an executable binary containing the minesweeper game.