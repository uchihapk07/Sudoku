#include <iostream>  //For input and output.
#include <iomanip>   //For ouput manipulations
#include <windows.h> //For colored text and ot
#include <conio.h>   //For Getch.
#include <cmath>     //For mathematical purpose
#include<bits/stdc++.h>
using namespace std; // Standard Naming Convent //To avoid namespace conf

// VOID FUNCTIONS

void playSudoku();
void exitMenu();
void checkGame();
void upKey();
void downKey();
void leftKey();
void rightKey();
void pauseGame();
void helpSudoku(string located);
void setPuzzle(int level);
void makePuzzle(string target, string puzzle);
void setNumberKey(string value);
void showProgressHardMode(double final_progress);
void hideCursor(bool condition);
void gotoMenu(char choice);
void colorSet(int tint);
void gamePart(string part);
void mainGame();

// OTHER FUNCTIONS

char gameLevel();

// GLOBAL VARIABLES
int level = 0;
int correct = 0;
int sudokuPointer = 0;
int sudokuPuzzleSize;
int sudokuBuildNumber;
double final_progress = 0;
string sudokuStatus;
string sudokuPuzzle[81];
string sudokuHighlights[81];
string sudokuSolution[81];

// MAIN PROGRAM

int main()
{
    // HIDE CURSOR
    hideCursor(true);

    // SET TITLE
    SetConsoleTitle(("Sudoku"));

    // VARIABLE
    int choice;

    // DISPLAY
    while (true)
    {
        system("cls");
        colorSet(4); // DARK RED
        gamePart("line_small_left");
        colorSet(15); // WHITE
        cout << "SUDOKU";
        colorSet(4); // DARK RED
        gamePart("line_small_right");
        colorSet(15); // WHITE
        cout << "[1] ";
        colorSet(11); // LIGHT CYAN
        cout << "START" << endl;
        colorSet(15);                // WHITE
        cout << "[2] ";
        colorSet(14); // YELLOW
        cout << "INSTRUCTIONS" << endl;
        colorSet(15); // WHITE
        cout << "[3] ";
        colorSet(12); // LIGHT RED
        cout << "EXIT" << endl;
        colorSet(4); // RED
        gamePart("seperator");
        colorSet(7); // LIGHT GRAY
        cout << "(Press the number of your choice!) ";
        colorSet(15); // WHITE
        // GET USER CHOICE
        char select = getch();
        if (!(select < '1' || select > '3'))
        {
            choice = select;
            break;
        }
    }
    // GO TO MENU OF USER CHOICE
    gotoMenu(choice);
}



// MENU CENTRAL
void gotoMenu(char choice)
{
    if (choice == '1')
    {
        playSudoku(); // GO TO PLAY MENU
    }
    else if (choice == '2')
    {
        helpSudoku("main"); // GO TO INSTRUCTIONS MENU
    }
    else if (choice == '3')
    {
        exitMenu(); // GO TO EXIT MENU
    }
}

// PLAY

void playSudoku()
{
    // GAME LEVEL
    char setLevel = gameLevel();
    // CONDITION LEVEL
    if (setLevel == '4')
    {
        // GO TO MENU
        main();
    }
    else
    {
        // GAME START
        level = (int)setLevel - 48; // Initialize Level
        setPuzzle(level);           // SET LEVEL
        sudokuStatus = "playing";   // SET STATUS
        sudokuPointer = 0;          // RESET POINTER
        checkGame();                // For Progress
        mainGame();                 // Enter the Game
    }
    // PAUSE
    getch();
    // GO TO MAIN MENU
    main();
}

// GAME CENTRAL
char gameLevel()
{
    char choice;
    do
    {
        system("cls");
        colorSet(4); // DARK RED
        gamePart("line_small_left");
        colorSet(15); // 15
        cout << "SUDOKU";
        colorSet(4); // DARK RED
        gamePart("line_small_right");
        colorSet(13); // 13
        cout << setw(29) << right << "SELECT A DIFFICULTY" << endl;
        colorSet(4); // DARK RED
        gamePart("seperator");
        colorSet(15);
        cout << "[1] "; // WHITE
        colorSet(10);  // LIGHT GREEN
        cout << "EASY" << endl;
        colorSet(15); // WHITE
        cout << "[2] ";
        colorSet(14); // YELLOW
        cout << "MEDIUM" << endl;
        colorSet(15); // WHITE
        cout << "[3] ";
        colorSet(12); // LIGHT RED
        cout << "HARD" << endl;
        colorSet(4); // 4
        gamePart("seperator");
        colorSet(15); // WHITE
        cout << "[4] ";
        colorSet(11); // LIGHT CYAN
        cout << "BACK" << endl;
        colorSet(4); // 4
        gamePart("seperator");
        colorSet(7); // LIGHT GRAY
        cout << "(Press the number of your choice!) ";
        colorSet(15); // WHITE

        // GET USER CHOICE
        char select = getch();
        if (!(select < '1' || select > '4'))
        {
            choice = select;
            break;
        }
    }while (true);
    return choice;
}

// SHOW PROGRESS FOR HARD MODE
void showProgressHardMode(double final_progress)
{
    if (final_progress >= 69)
    {
        if (final_progress >= 84)
        {
            if (final_progress >= 94)
            {
                cout << "Just a little bit!";
            }
            else
            {
                cout << "Almost there!";
            }
        }
        else
        {
            cout << "Half-way there!";
        }
    }
    else
    {
        cout << "Unfinshed";
    }
}

// SET PUZZLE
void setPuzzle(int level)
{
    // Variable
    string dot = ".";
    string puzzle, highlight, solution;
    // Condition

    // EASY
    if (level == 1)
    {
        puzzle = (" .7.8|3.1. | . . " + dot 
        + " .4. | .2.6|5. . " + dot 
        + "6. . |9.4.7|8. .1" + dot

        + "2. . | . . |1.4. " + dot 
        + "5. . |7. . |1. .2" + dot 
        + " .1. | . . | . .3" + dot

        + "4. .5| . . | . .9" + dot 
        + " . .1|4.5. | .2. " + dot 
        + " . . | .9.2|4.7. ");

        highlight = ("0.F.F|F.F.0|F.0.0" + dot 
        + "0.F.0|0.F.F|F.0.0" + dot 
        + "F.0.0|F.F.F|F.0.F" + dot

        + "F.0.0|0.0.0|0.F.0" + dot 
        + "F.0.0|F.0.F|0.0.F" + dot 
        + "0.F.0|0.0.0|0.0.F" + dot

        + "F.0.F|0.0.0|0.0.F" + dot 
        + "0.0.F|F.F.0|0.F.0" + dot 
        + "0.0.0|0.F.F|F.F.0");

        solution = ("9.7.8|3.1.5|2.6.4" + dot 
        + "1.4.3|8.2.6|5.9.7" + dot 
        + "6.5.2|9.4.7|8.3.1" + dot

        + "2.3.7|5.8.9|1.4.6" + dot 
        + "5.6.4|7.3.1|9.8.2" + dot 
        + "8.1.9|2.6.4|7.5.3" + dot

        + "4.2.5|6.7.8|3.1.9" + dot 
        + "7.9.1|4.5.3|6.2.8" + dot 
        + "3.8.6|1.9.2|4.7.5");
    }
    // MEDIUM
    else if (level == 2)
    {
        puzzle = (" .8.4|2. . | . .9" + dot 
        + "1. .2|8. . |5. . " + dot 
        + "9. . | .6. | . .3" + dot

        + " .9. | . . |2.7. " + dot 
        + "5. . | . . | . .8" + dot 
        + " .4.8| . . | .3. " + dot

        + "7. . | .2. | . .1" + dot 
        + " . .3| . .6|7. .4" + dot 
        + "4. . | . .5| .3.9. ");

        highlight = ("0.F.F|F.0.0|0.0.F" + dot 
        + "F.0.F|F.0.0|F.0.0" + dot 
        + "F.0.0|0.F.0|0.0.F" + dot

        + "0.F.0|0.0.0|F.F.0" + dot 
        + "F.0.0|0.0.0|0.0.F" + dot 
        + "0.F.F|0.0.0|0.F.0" + dot

        + "F.0.0|0.F.0|0.0.F" + dot 
        + "0.0.F|0.0.F|F.0.F" + dot 
        + "F.0.0|0.0.F|F.F.0");

        solution = ("3.8.4|2.5.7|1.6.9" + dot 
        + "1.6.2|8.3.9|5.4.7" + dot 
        + "9.7.5|1.6.4|8.2.3" + dot

        + "6.9.1|3.4.8|2.7.5" + dot 
        + "5.3.7|6.9.2|4.1.8" + dot 
        + "2.4.8|5.7.1|9.3.6" + dot
        
        + "7.5.9|4.2.3|6.8.1" + dot 
        + "8.2.3|9.1.6|7.5.4" + dot 
        + "4.1.6|7.8.5|3.9.2");
    }
    // HARD
    else
    {
        puzzle = (" .8. |5.2. |6.4. " + dot 
        + "7. .6| . . | . .2" + dot 
        + "4.2. | . . | .3. " + dot

        + " .5. | . .1| . . " + dot 
        + "6. . |7.8.3| . .9" + dot 
        + " . . |9. . | .6. " + dot
        
        + " .3. | . . | .2.6" + dot 
        + "1. . | . . |3. .5" + dot 
        + "2.9.2| .3.5| . . ");
        
        highlight = ("0.F.0|F.F.0|F.F.0" + dot 
        + "F.0.F|0.0.0|0.0.F" + dot 
        + "F.F.0|0.0.0|0.F.0" + dot

        + "0.F.0|0.0.F|0.0.0" + dot 
        + "F.0.0|F.F.F|0.0.F" + dot 
        + "0.0.0|F.0.0|0.F.0" + dot

        + "0.F.0|0.0.0|0.F.F" + dot 
        + "F.0.0|0.0.0|F.0.F" + dot 
        + "0.F.F|0.F.F|0.0.0");
        
        solution = ("9.8.3|5.2.7|6.4.1" + dot 
        + "7.1.6|3.4.8|5.9.2" + dot 
        + "4.2.5|1.9.6|7.3.8" + dot

        + "2.5.9|4.6.1|8.7.3" + dot 
        + "6.4.1|7.8.3|2.5.9" + dot 
        + "3.7.8|9.5.2|1.6.4" + dot

        + "5.3.7|8.1.4|9.2.6" + dot 
        + "1.6.4|2.7.9|3.8.5" + dot 
        + "8.9.2|6.3.5|4.1.7");
    }
    // CREATE THE PUZZLE

    makePuzzle("puzzle_layout", puzzle);
    makePuzzle("highlight_layout", highlight);
    makePuzzle("solution_layout", solution);
}

// CONVERT STRING PUZZLE TO ARRAY

void makePuzzle(string target, string puzzle)
{

    // Variables
    char cpuzzle[puzzle.length()];
    int i;
    int pointer = 0;
    // Loop Function
    for (i = 0; i < sizeof(cpuzzle); i++)
    {
        cpuzzle[i] = puzzle[i];
        if (!(cpuzzle[i] == '.' || cpuzzle[i] == '|'))
        {

            string sudokuNumber(1, cpuzzle[i]);
            if (target == "puzzle_layout")
            {
                // cout <<"["<<pointer<<"]: "<<sudokuNumber<<"  ";
                sudokuPuzzle[pointer] = sudokuNumber;
            }
            else if (target == "highlight_layout")
            {
                // cout <<"["<<pointer<<"]: "<<sudokuNumber<<"  ";
                sudokuHighlights[pointer] = sudokuNumber;
            }
            else if (target == "solution_layout")
            {
                // cout <<"["<<pointer<<"]: "<<sudokuNumber<<"  ";
                sudokuSolution[pointer] = sudokuNumber;
            }
            pointer++;
        }
    }
    cout << endl << endl;
}

// GAME CONTROL FUNCTIONS
void upkey()
{
    sudokuPointer = sudokuPointer - 9;
    // TOP BARRIER
    if (sudokuPointer == -9)
    {
        sudokuPointer = 72;
    }
    else if (sudokuPointer == -8)
    {
        sudokuPointer = 73;
    }
    else if (sudokuPointer == -7)
    {
        sudokuPointer = 74;
    }
    else if (sudokuPointer == -6)
    {
        sudokuPointer = 75;
    }
    else if (sudokuPointer == -5)
    {
        sudokuPointer = 76;
    }
    else if (sudokuPointer == -4)
    {
        sudokuPointer = 77;
    }
    else if (sudokuPointer == -3)
    {
        sudokuPointer = 78;
    }
    else if (sudokuPointer == -2)
    {
        sudokuPointer = 79;
    }
    else if (sudokuPointer <= -1)
    {
        sudokuPointer = 80;
    }
}
void downKey()
{
    sudokuPointer = sudokuPointer + 9;
    // BOTTOM BARRIER
    if (sudokuPointer == 81)
    {
        sudokuPointer = 0;
    }
    else if (sudokuPointer == 82)
    {
        sudokuPointer = 1;
    }
    else if (sudokuPointer == 83)
    {
        sudokuPointer = 2;
    }
    else if (sudokuPointer == 84)
    {
        sudokuPointer = 3;
    }
    else if (sudokuPointer == 85)
    {
        sudokuPointer = 4;
    }
    else if (sudokuPointer == 86)
    {
        sudokuPointer = 5;
    }
    else if (sudokuPointer == 87)
    {
        sudokuPointer = 6;
    }
    else if (sudokuPointer == 88)
    {
        sudokuPointer = 7;
    }
    else if (sudokuPointer == 89)
    {
        sudokuPointer = 8;
    }
}

void leftKey()
{
    sudokuPointer = sudokuPointer - 1;
    // LEFT BARRIER

    if (sudokuPointer = -62)
    {
        sudokuPointer = 71;
    }
    else if (sudokuPointer == 71)
    {
        sudokuPointer = 80;
    }
    else if (sudokuPointer == 53)
    {
        sudokuPointer = 62;
    }
    else if (sudokuPointer == 44)
    {
        sudokuPointer = 53;
    }
    else if (sudokuPointer == 35)
    {
        sudokuPointer = 44;
    }
    else if (sudokuPointer == 26)
    {
        sudokuPointer = 35;
    }
    else if (sudokuPointer == 17)
    {
        sudokuPointer = 26;
    }
    else if (sudokuPointer == 8)
    {
        sudokuPointer = 17;
    }
    else if (sudokuPointer == -1)
    {
        sudokuPointer = 8;
    }
}

void rightKey()
{
    sudokuPointer = sudokuPointer + 1;
    // RIGHT BARRIER

    if (sudokuPointer == 81)
    {
        sudokuPointer = 72;
    }
    else if (sudokuPointer == 72)
    {
        sudokuPointer = 63;
    }
    else if (sudokuPointer == 63)
    {
        sudokuPointer = 54;
    }
    else if (sudokuPointer == 54)
    {
        sudokuPointer = 45;
    }
    else if (sudokuPointer == 45)
    {
        sudokuPointer = 36;
    }
    else if (sudokuPointer == 36)
    {
        sudokuPointer = 27;
    }
    else if (sudokuPointer == 27)
    {
        sudokuPointer = 18;
    }
    else if (sudokuPointer == 18)
    {
        sudokuPointer = 9;
    }
    else if (sudokuPointer == 9)
    {
        sudokuPointer = 0;
    }
}

// MAIN GAME

void mainGame()
{
     //-- HEADER --// 
    system("cls");
    colorSet (4); //DARK RED 
    gamePart("line_small_left");
    colorSet (15); 
    cout<<"SUDOKU";
    colorSet (4);
    gamePart("line_small_right"); 
    ///// LEVEL AND COLLECT PARTS ///// 
    switch(level) {
    case 1:
        colorSet (10); cout<<setw(24) <<right<<"EASY LEVEL"<<endl;
        break;
    case 2:
        colorSet (14);
        cout<<setw(25)<<right<<"MEDIUM LEVEL"<<endl;
        break; 
    default:
        colorSet (12);
        cout<<setw(24) <<right<<"HARD LEVEL"<<endl;
    }
    colorSet (4); 
    gamePart("seperator");
    cout<<endl;

    //-- HEADER --//

    //- TABLE GENERATOR --//

    // SET TABLE COLOR // 
    int colorTable = 5;

    //IF PLAYER QUITS

    //SET SUDOKU PUZZLE SIZE 
    sudokuPuzzleSize = (sizeof(sudokuPuzzle)/sizeof(sudokuPuzzle [0]));

    //FETCH SOLUTION

    if(sudokuStatus == "quitted")
    { 
        for (int checker = 0; checker < sudokuPuzzleSize; checker++)
        { 
            sudokuPuzzle[checker] = sudokuSolution[checker];
        }
    }

    // BUILD SUDOKU TABLE
    sudokuBuildNumber = 0; // reset sudoku build number
    for (int tpart = 1; tpart <= 182; tpart++)
    {

        // SUDOKU OUTER BORDER
        if (tpart == 1 || tpart == 62 || tpart == 122 || tpart == 182)
        {
            colorSet(colorTable);
            gamePart("sudoku_outer_border");
        }
        // SUDOKU OUTER VERTICAL BORDER, PART BY PART
        else if (tpart == 2   || tpart == 8   || tpart == 14  || tpart == 22  || tpart == 28  || tpart == 34  ||
                 tpart == 42  || tpart == 49  || tpart == 55  || tpart == 63  || tpart == 69  || tpart == 75  ||
                 tpart == 83  || tpart == 89  || tpart == 95  || tpart == 103 || tpart == 109 || tpart == 115 ||
                 tpart == 123 || tpart == 129 || tpart == 135 || tpart == 143 || tpart == 149 || tpart == 155 ||
                 tpart == 163 || tpart == 169 || tpart == 175)
        {
            colorSet(colorTable);
            gamePart("sudoku_outer_vertical_border_small");
        }
        // SUDOKU OUTER VERTICAL BORDER WITH NEXT LINE, PART BY PART
        else if (tpart == 20  || tpart == 40  || tpart == 61 || tpart == 81 || tpart == 101 || tpart == 121 ||
                 tpart == 141 || tpart == 161 || tpart == 181)
        {
            colorSet(colorTable);
            gamePart("sudoku_outer_vertical_border_next_line");
        }
        // SUDOKU NUMBERS
        else if (tpart == 3   || tpart == 5   || tpart == 7   || tpart == 9   || tpart == 11  || tpart == 13  ||
                 tpart == 15  || tpart == 17  || tpart == 19  || tpart == 23  || tpart == 25  || tpart == 27  ||
                 tpart == 29  || tpart == 31  || tpart == 33  || tpart == 35  || tpart == 37  || tpart == 39  ||
                 tpart == 43  || tpart == 45  || tpart == 47  || tpart == 50  || tpart == 52  || tpart == 54  ||
                 tpart == 56  || tpart == 58  || tpart == 60  || tpart == 64  || tpart == 66  || tpart == 68  ||
                 tpart == 70  || tpart == 72  || tpart == 74  || tpart == 76  || tpart == 78  || tpart == 80  ||
                 tpart == 84  || tpart == 86  || tpart == 88  || tpart == 90  || tpart == 92  || tpart == 94  ||
                 tpart == 96  || tpart == 98  || tpart == 100 || tpart == 104 || tpart == 106 || tpart == 108 ||
                 tpart == 110 || tpart == 112 || tpart == 114 || tpart == 116 || tpart == 118 || tpart == 120 ||
                 tpart == 124 || tpart == 126 || tpart == 128 || tpart == 130 || tpart == 132 || tpart == 134 ||
                 tpart == 136 || tpart == 138 || tpart == 140 || tpart == 144 || tpart == 146 || tpart == 148 ||
                 tpart == 150 || tpart == 152 || tpart == 154 || tpart == 156 || tpart == 158 || tpart == 160 ||
                 tpart == 164 || tpart == 166 || tpart == 168 || tpart == 170 || tpart == 172 || tpart == 174 ||
                 tpart == 176 || tpart == 178 || tpart == 180)
        {

            colorSet(15);
            // COLOR
            if (sudokuHighlights[sudokuBuildNumber] == "0")
            {
                colorSet(15);
            }
            else if (sudokuHighlights[sudokuBuildNumber] == "F")
            {
                colorSet(14);
            }
            // DISPLAY POINTER OR NOT
            if (sudokuStatus == "quitted" || sudokuStatus == "finished")
            {
                // OUTPUT NUMBER
                cout << sudokuPuzzle[sudokuBuildNumber];
            }
            else
            {
                // POINTER
                if (sudokuBuildNumber == sudokuPointer)
                {
                    colorSet(10);
                    if (sudokuHighlights[sudokuPointer] == "F")
                    {
                        colorSet(11);
                        cout << sudokuPuzzle[sudokuBuildNumber];
                    }
                    else
                    {

                        if (sudokuPuzzle[sudokuBuildNumber] == "1" || sudokuPuzzle[sudokuBuildNumber] == "2" ||
                            sudokuPuzzle[sudokuBuildNumber] == "2" || sudokuPuzzle[sudokuBuildNumber] == "3" ||
                            sudokuPuzzle[sudokuBuildNumber] == "4" || sudokuPuzzle[sudokuBuildNumber] == "5" ||
                            sudokuPuzzle[sudokuBuildNumber] == "6" || sudokuPuzzle[sudokuBuildNumber] == "7" ||
                            sudokuPuzzle[sudokuBuildNumber] == "8" || sudokuPuzzle[sudokuBuildNumber] == "9")
                        {
                            cout << sudokuPuzzle[sudokuBuildNumber];
                        }
                        else
                        {
                            cout << "x";
                        }
                    }
                }
                else
                {
                    // OUTPUT NUMBER
                    cout << sudokuPuzzle[sudokuBuildNumber];
                }
            }
            // ADD
            sudokuBuildNumber++;
        }
        // SUDOKU INNER VERTICAL BORDER, PART BY PART
        else if (tpart == 4   || tpart == 6   || tpart == 10  || tpart == 12  || tpart == 16  || tpart == 18  ||
                 tpart == 24  || tpart == 26  || tpart == 30  || tpart == 32  || tpart == 36  || tpart == 38  ||
                 tpart == 44  || tpart == 46  || tpart == 51  || tpart == 53  || tpart == 57  || tpart == 59  ||
                 tpart == 65  || tpart == 67  || tpart == 71  || tpart == 73  || tpart == 77  || tpart == 79  ||
                 tpart == 85  || tpart == 87  || tpart == 91  || tpart == 93  || tpart == 97  || tpart == 99  ||
                 tpart == 105 || tpart == 107 || tpart == 111 || tpart == 113 || tpart == 117 || tpart == 119 ||
                 tpart == 125 || tpart == 127 || tpart == 131 || tpart == 133 || tpart == 137 || tpart == 139 ||
                 tpart == 145 || tpart == 147 || tpart == 151 || tpart == 153 || tpart == 157 || tpart == 159 ||
                 tpart == 165 || tpart == 167 || tpart == 171 || tpart == 173 || tpart == 177 || tpart == 179)
        {
            colorSet(colorTable);
            gamePart("sudoku_inner_vertical_border_small");
        }
        // SUDOKU INNER BORDER
        else if (tpart == 21 || tpart == 41 || tpart == 82 || tpart == 102 || tpart == 142 || tpart == 162)
        {
            colorSet(colorTable);
            gamePart("sudoku_inner_border");
        }
    }
    cout<<endl;
    //-- TABLE GENERATOR --//
    // DETAILS --//
    // SET PROGRESS

    final_progress = round(((double(correct) / 81.8)*100));

    // CHECK PLAYER CONDITION
    if (sudokuStatus == "playing")
    {
        colorSet(11);
        cout << " Progress: ";
        colorSet(15);

        // SWITCH CASE
        switch(level)
        {
            case 1:cout << correct << "/81";
                   break;
            case 2:cout << final_progress << "%";
                   break;
            default:showProgressHardMode(final_progress);
        }
        cout << endl;
        colorSet(14);
        cout << " Press";
        colorSet(12);
        cout << " [Esc]";
        colorSet(15);
        cout << " or ";
        colorSet(12);
        cout << " or ";
        colorSet(12);
        cout << "[P] ";
        colorSet(14);
        cout << "to pause the game";
    }
    else if (sudokuStatus == "quitted")
    {
        colorSet(14);
        cout << " Sorry you did not finish" << endl << " the sudoku puzzle." << endl;
        colorSet(13);
        cout << " Better luck next time!" << endl;
        colorSet(15);
        cout << " By the way, thats the solution." << endl;
        colorSet(7);
        cout << " [Press any key to exit the game]";
        getch(); // pause
        main();  // go to main menu
    }
    else if (sudokuStatus == "finished")
    {
        colorSet(10);
        cout << " Congratulations you solved" << endl << " the sudoku puzzle." << endl;
        colorSet(13);
        cout << " Your sudoku skills are" << endl << " quite impressive!" << endl << endl;
        colorSet(7);
        cout << " [Press any key to exit the game]";
        getch(); // pause
        main();  // go to main menu
    }
    else
    { 
        // HIDDEN DETAILS
        cout << " Pointer: " << sudokuPointer << endl;
        cout << " Highlight: " << sudokuHighlights[sudokuPointer] << endl;
    }
    //-- DETAILS --//
    //--KEYBOARD FUNCTIONS //
    while (true)
    {
        int keyPress; // key code
        colorSet(15);
        keyPress = 0;     // reset
        keyPress = getch(); // get number
        if (keyPress == 0 || keyPress == 224)
        {
           // If arrow keys and delete k keyPress 256+
            getch(); // convert key code
            if (keyPress == 328)
            { 
                // UP
                upkey();
                break;
            }
            else if (keyPress == 336)
            {
                // DOWN
                downKey();
                break;
            }
            else if (keyPress == 331)
            { // LEFT
                leftKey();
                break;
            }
            else if (keyPress == 333)
            {
                // RIGHT
                rightKey();
                break;
            }
            else if (keyPress == 339)
            {
                // DELETE (DeL)
                setNumberKey("clear");
                break;
            }
        }
        else
        {
            // If other key pressed
            // MOVEMENT KEYS
            if (keyPress == 119 | keyPress == 87)
            {
                // Up (W)
                upkey();
                break;
            }
            else if (keyPress == 115 || keyPress == 83)
            {
                // Down (S)
                downKey();
                break;
            }
            else if (keyPress == 97 || keyPress == 65)
            {
                // Left (A)
                leftKey();
                break;
            }
            else if (keyPress == 100 || keyPress == 68)
            {
                // Right (D)
                rightKey();
                break;
            }
            // NUMBER KEYS
            if (keyPress == 49)
            {
                // One (1)
                setNumberKey("1");
                break;
            }
            else if (keyPress == 50)
            {
                // Two (2)
                setNumberKey("2");
                break;
            }
            else if (keyPress == 51)
            {
                // Three (3)
                setNumberKey("3");
                break;
            }
            else if (keyPress == 52)
            {
                // Four (4)
                setNumberKey("4");
                break;
            }
            else if (keyPress == 53)
            {
                // Five (5)
                setNumberKey("5");
                break;
            }
            else if (keyPress == 54)
            {
                // Six (6)
                setNumberKey("6");
                break;
            }
            else if (keyPress == 55)
            {
                // Seven (7)
                setNumberKey("7");
                break;
            }
            else if (keyPress == 56)
            {
                // Eight (8)
                setNumberKey("8");
                break;
            }
            else if (keyPress == 57)
            {
                // Nine (9)
                setNumberKey("9");
                break;
            }
            // DELETE KEY
            else if (keyPress == 8)
            {
                // Backspace
                setNumberKey("clear");
                break;
            }
            // PAUSE KEY
            else if (keyPress == 27 || keyPress == 112 || keyPress == 88)
            {
                // Escap or P
                pauseGame();
                break;
            }
            else
            {
                continue;
            }
        }
    }
    //-- KEYBOARD FUNCTIONS ---//
    //-- CHECKER --//
    checkGame();
    //-- CHECKER --//
}

// CHECK GAME
void checkGame()
{
    // SET SUDOKU PUZZLE SIZE
    sudokuPuzzleSize = (sizeof(sudokuPuzzle) / sizeof(sudokuPuzzle[0]));
    correct = 0; // reset total of correct numbers in the grid
    for (int sudokuPointing = 0; sudokuPointing < sudokuPuzzleSize; sudokuPointing++)
    {
        if (sudokuPuzzle[sudokuPointing] == sudokuSolution[sudokuPointing])
        {
            correct++;
        }
    }
    // GAME FINISHED
    if (correct == sudokuPuzzleSize)
    {
        sudokuStatus = "finished";
    }
    // RESUME TO THE GAME
    mainGame();
}


// SET NUMBER KEY OR CLEAR THE NUMBER IN THE GRID

void setNumberKey(string value)
{
    if (!(value == "clear"))
    {
        if (sudokuHighlights[sudokuPointer] == "0")
        {
            sudokuPuzzle[sudokuPointer] = value;
        }
    }
    else
    {
        if (sudokuHighlights[sudokuPointer] == "0")
        {
            sudokuPuzzle[sudokuPointer] = " ";
        }
    }
}

// PAUSE GAME

void pauseGame()
{
    // DISPLAY
    do
    {
        system("cls");
        colorSet(4); // DARK RED
        gamePart("line_small_left");
        colorSet(15); // 15
        cout << "SUDOKU";
        colorSet(4); // DARK RED
        gamePart("line_small_right");
        colorSet(13); // 13
        cout << setw(24) << right << "GAME PAUSED" << endl;
        colorSet(4); // DARK RED
        gamePart("seperator");
        colorSet(15); // WHITE
        cout << "[1] ";
        colorSet(14); // YELLOW
        cout << "RESUME" << endl;
        colorSet(15); // WHITE
        cout << "[2] ";
        colorSet(10); // LIGHT GREEN 
        cout<<"INSTRUCTIONS"<<endl;
        colorSet(15); // WHITE
        cout << "[3] ";
        colorSet(12); // LIGHT RED
        cout << "QUIT" << endl;
        colorSet(4); // 4
        gamePart("seperator");
        colorSet(7); // LIGHT GRAY
        cout << "(Press the number of your choice!) ";
        colorSet(15); // WHITE

        // GET USER CHOICE
        char select = getch();

        if (!(select < '1' || select > '3'))
        {
            cout << endl;
            if (select == '2')
            {
                helpSudoku("in-game");
            }
            else if (select == '3')
            {
                sudokuStatus = "quitted";
                break;
            }
            else
            {
                break;
            }
        }
    } while (true);
}

// INSTRUCTIONS

void helpSudoku(string located)
{
    system("cls");
    colorSet(4); // DARK RED
    gamePart("line_small_left");
    colorSet(15); // 15
    cout << "SUDOKU";
    colorSet(4); // DARK RED
    gamePart("line_small_right");
    colorSet(13); // 13
    cout << setw(25) << right << "INSTRUCTIONS" << endl;
    colorSet(4);   // DARK RED gamePart("seperator");
    colorSet(10); // LIGHT GREEN
    cout << " How to play: " << endl;
    colorSet(15); // WHITE
    cout << "-> The sudoku puzzle is consist of" << endl;
    cout << "   a 9x9 grid, you have to fill" << endl;
    cout << "   the empty squares using the " << endl;
    cout << "   numbers 1 to 9." << endl;
    cout << "-> Use the 1-9 keys in your" << endl;
    cout << "   keybord to fill the sudoku" << endl;
    cout << "   puzzle." << endl;
    cout << "-> To move arround the sudoku" << endl;
    cout << "   puzzle, use the WASD letter" << endl;
    cout << "   keys or the arrow keys." << endl;
    cout << "-> Use backspace or delete key to" << endl;
    cout << "   clear the number selected in" << endl;
    cout << "   the sudoku puzzle. " << endl;
    cout << "-> Once you finish the sudoku" << endl;
    cout << "   puzzle, it will prompt you that" << endl;
    cout << "   you finished it if not you can" << endl;
    cout << "   press P then you can choose" << endl;
    cout << "   Quit\" in the pause menu" << endl;
    cout << "   if your having a hard time." << endl;
    colorSet(4); // DARK RED
    gamePart("seperator");
    colorSet(7); // LIGHTGRAY
    cout << " (Press any key to go back!) ";
    colorSet(15); // WHITE
    // PAUSE
    getch();
    // GO TO MAIN MENU
    if (located == "main")
    {
        main();
    }
}

void exitMenu()
{
    // DISPLAY
    do
    {
        system("cls");
        colorSet(4); // DARK RED
        gamePart("line_small_left");
        colorSet(15); // 15
        cout << "SUDOKU";
        colorSet(4); // DARK RED
        gamePart("line_small_right");
        colorSet(13); // 13
        cout << setw(28) << right << "DO YOU WANT TO EXIT" << endl;
        colorSet(4); // DARK RED
        gamePart("seperator");
        colorSet(15); // WHITE
        cout << "[1] ";
        colorSet(12); // LIGHT RED
        cout << "YES" << endl;
        colorSet(15); // WHITE
        cout << "[2] ";
        colorSet(10); // LIGHT GREEN
        cout << "NO" << endl;
        colorSet(4); // 4
        gamePart("seperator");
        colorSet(7); // LIGHT GRAY
        cout << "(Press the number of your choice!) ";
        colorSet(15); // WHITE

        // GET USER CHOICE
        char select = getch();
        if (!(select < '1' || select > '2'))
        {
            cout << endl;
            if (select == '1')
            {
                exit(0);
            }
            else
            {
                main();
            }
        }
    } while (true);
}

// COLOR SET

void colorSet(int tint)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tint);
}

// THIS IS WHERE YOU GET THE PARTS AND DISPLAY IT TO THE GAME
// YOU'LL JUST DECLARE THE NAME OF THE GAME PART IF YOU WILL USE IT REPEATEDLY
// ADJUST THE PARTS BELOW AND IT WILL AFFECT THE GAME DESIGN AS WELL
// GAME PARTS

void gamePart(string part)
{

    if (part == "line_small_left")
    {
        cout << "=============== ";
    }
    else if (part == "line_small_right")
    {
        cout << " ================" << endl;
    }
    else if (part == "seperator")
    {
        cout << "=======================================" << endl;
    }
    else if (part == "sudoku_outer_border")
    {
        cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    }
    else if (part == "sudoku_outer_vertical_border_small")
    {
        cout << " $ ";
    }
    else if (part == "sudoku_outer_vertical_border_next_line")
    {
        cout << " $" << endl;
    }
    else if (part == "sudoku_inner_vertical_border_small")
    {
        cout << " | ";
    }
    else if (part == "sudoku_inner_border")
    {
        cout << " $---*---*---$---*---*---$---*---*---$" << endl;
    }
    else
    {
        cout << "";
    }
}

// HIDE CURSOR IN THE CONSOLE

void hideCursor(bool condition)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = (!(condition)); // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
