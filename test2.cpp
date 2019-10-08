/**
 * @file
 * @author Micheal peterson
 *
 * @section DESCRIPTION
 *
 * This program tracks life totals for a game of Magic the Gathering. It can do
 * two-headed, commander and 60 card fromats. The program works with up o 2
 * teams or 20 players. It will track when someone loses and report the winner
 * of each game. The program outputs to a file and the terminal.
 *
 * @section IMPROVEMENTS
 *
 * 1) See what sentering the table elements looks like.
 * 2) Add formats:
 * 	a) Star
 * 	b) Emperor
 * 3) Move the life change into a function.
 * 4) Teestream.
 * 5) Make players a class or struc, has string for initials and ints for both
 * life and life change. a) stop gap: turn all referances of multi dimentional
 * array for players into a sing dimention. 6) Change to vector.
 */

#include <array>
#include <fstream>
//#include <functions.h>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
int num_players;
string players[20][4];
ofstream record;
// currently only working with dimesion [i][0]
// other dimesions for later implementation, will try atof as way to do math on
// array elements

/**
 * This clears the input of leftover input.
 */

void new_line() {
  char next;
  do {
    cin.get(next);
  } while (next != '\n');
}

/**
 * This initializes the life totals for each game.
 *
 * Depending on the style of game selected it will initialize the totals to
 * either 20, 30, or 40. If 2-headed is selected it should shrink the array down
 * to 2.
 *
 * @param S An ineger representing the style of game choosen.
 * @param num_players A referance to the number of players.
 * @param l[] The array of life totals.
 *
 * @section EDGE CASES
 *
 * 1) Odd number of players when 2 headed is selected.
 * 2) 6 or more players when 2 headed is selected.
 *
 */

void setlife(int S, int &num_players, int l[]) {
  int style = S, lifestart;
  if (style == '1') {
    lifestart = 20;
  }
  if (style == '2') {
    lifestart = 30;
    num_players =
        num_players / 2; // does not work with inputing odd player number
                         // added to fix problem with 2heaed calculations
  }
  if (style == '3') { // these were changed from = to ==
    lifestart = 40;
  }
  for (int i = 0; i < num_players; i++) { // life inicialization added
    l[i] = lifestart;
  }
}

/**
 * This creates the header for 2-headed.
 *
 * THis will first output the each team, as a pair of players, seperated by
 * "vs." Then it will use set up the table header.
 *
 * @section IMPROVEMENTS
 *
 * 1) Space after each "vs.".
 * 2) Note which pair is what Tm.
 * 3) More then 2 teams.
 * 4) Align the header with the life total. Curently Tm2 is left justified and
 * their life is right.
 */
void twoheaded() { // moved into a function
  cout << players[0][0];
  cout << "/";
  cout << players[1][0];
  cout << " vs.";
  cout << players[2][0];
  cout << "/";
  cout << players[3][0];
  cout << "\n\n";
  cout.width(4);
  cout << left << "Tm1";
  cout << " | ";
  cout.width(4);
  cout << right << "Tm2\n";
  cout << "_____|______\n";

  record << "\nStart Game\n";
  record << players[0][0];
  record << "/";
  record << players[1][0];
  record << " vs. ";
  record << players[2][0];
  record << "/";
  record << players[3][0];
  record << "\n\n";
  record << setw(4) << left << "Tm1";
  record << " | ";
  record << setw(4) << right << "Tm2\n";
  record << "_____|______\n";
}

/**
 * THis gives the first line of the table, aka the starting life of each player.
 *
 * @param life[] The life already initialized life array.
 */

void row1(int life[]) {
  cout.width(4);
  cout << left << life[0];
  cout << " | ";
  cout.width(4);
  cout << right << life[1];
  for (int p = 2; p < num_players; p++) {
    cout << " | ";
    cout.width(4);
    cout << left << life[p];
  }
  cout << "\n";
  record << setw(4) << left << life[0];
  record << " | ";
  record << setw(4) << left << life[1];
  for (int p = 2; p < num_players; p++) {
    record << " | ";
    record << setw(4) << left << life[2];
  }
  record << "\n";
}

/**
 * This reates the header for 2+ player free for alls.
 *
 * First the player initials are diplayed seperated by "vs.". Then we have the
 * table set up using the initials as headers.
 */

void multiplayer() {
  cout << players[0][0] << " vs. " << players[1][0];
  for (int p = 2; p < num_players; p++) {
    cout << " vs. " << players[p][0];
  }
  cout << "\n\n";
  cout << setw(4) << left << players[0][0];
  cout << " | ";
  cout << setw(4) << left << players[1][0];
  for (int p = 2; p < num_players; p++) {
    cout << " | ";
    cout << setw(4) << left << players[p][0];
  }
  cout << "\n_____|______";
  for (int p = 2; p < num_players; p++) {
    cout << "|______";
  }
  cout << "\n";

  record << "\nStart Game\n";
  record << players[0][0] << " vs. " << players[1][0];
  for (int p = 2; p < num_players; p++) {
    record << " vs. " << players[p][0];
  }
  record << "\n\n";
  record << setw(4) << left << players[0][0];
  record << " | ";
  record << setw(4) << left << players[1][0];
  for (int p = 2; p < num_players; p++) {
    record << " | ";
    record << setw(4) << left << players[p][0];
  }
  record << "\n_____|______";
  for (int p = 2; p < num_players; p++) {
    record << "|______";
  }
  record << "\n";
}

int track(int style, int life[]) {
  // int life[]=l[];
  int chan_1, chang, newlife, chan[20], winner, replay = 0;
  do {
    for (int c = 0; c < num_players; c++) { // can i merge these 2 for loops
      cin >> chan_1;                        // can these 2 lines be merged...
      chan[c] = chan_1;
    }
    for (int l = 0; l < num_players; l++) {
      newlife = life[l]; //...then i can probably merge these.
      chang = chan[l];
      life[l] = newlife + chang;
    }
    cout.width(4);
    if (life[0] < 1) {
      cout << left << "L";
      record << setw(4) << left << "L";
    } else {
      cout << left << life[0];
      record << setw(4) << left << life[0];
    }
    cout << " | ";
    record << " | ";
    cout.width(4);
    if (life[1] < 1) {
      cout << left << "L";
      record << setw(4) << left << "L";
    } else {
      cout << right << life[1];
      record << setw(4) << left << life[1];
    }
    for (int p = 2; p < num_players; p++) {
      cout << " | ";
      record << " | ";
      cout.width(4);
      if (life[p] < 1) {
        cout << left << "L";
        record << setw(4) << left << "L";
      } else {
        cout << left << life[p];
        record << setw(4) << left << life[p];
      }
    }
    cout << "\n";
    record << "\n";
    for (int w = 0; w < num_players; w++) {
      if (life[w] > 0) {
        replay++;
        winner = w;
      }
    }
  } while (replay > 1 && cin);
  cout << "end track\n";
  if (style == '2') { // changed from = to ==
    cout << "Winner is Team " << winner + 1 << ".\n";
    record << "Winner is Team " << winner + 1 << ".\n";
  } else {
    cout << "Winner is " << players[winner][0] << ".\n";
    record << "Winner is " << players[winner][0] << ".\n";
  }

  return winner;
}
/**
 * This records the initials of the players.
 *
 * Each player inputs their initials and they are stored in an array. It also
 * records the players initials to a file.
 *
 * @param Players[][] The array where the strings are stored.
 * @param num_players A referance to the number of players it is recording.
 *
 * @section IMPROVEMENTS
 *
 * Why do I have it recording to a file?
 * If there is a reason have it append and not overwrite.
 */

void getplayers(string players[20][4], int &num_players) {
  char next, letter;
  ofstream cin_out;
  ifstream cin_in;
  cout << "\nIf this is a team game please enter teammates next to each "
          "other.\n";
  cout << "When entering initials there should be no spaces or other "
          "characters.\n";
  for (int i = 0; i < num_players; i++) {
    cout << "\nPlayer " << i + 1 << " enter your initails and press enter.\n";
    cin_out.open("players.doc");
    if (cin_out.fail()) {
      cout << "There was an error while trying to open players.txt!\n";
      cout << "Enter any character and hit return to end the program.\n";
      cin >> letter;
      exit(1);
    }
    do {
      cin.get(next);
      cin_out.put(toupper(next));
    } while (next != '\n');
    cin_out.close();
    cin_in.open("players.doc");
    if (cin_in.fail()) {
      cout << "There was an error while trying to open players.txt!\n";
      cout << "Enter any character and hit return to end the program.\n";
      cin >> letter;
      exit(1);
    }
    getline(cin_in, players[i][0], '\n');
    cin_in.close();
  }
}

int main() {
  using namespace std;
  char letter, style, playercheck, stylecheck;
  ofstream record;
  int life[20], chan[20];             // chan[20]
  int num_players = 2, gamecount = 0; // removed unused variables
  cout << "This program will keep track of life totals in a game of Magic.\n";
  cout << "The program can do 1v1, 2 headed giant, and 4 player commander.\n";
  cout << "Whenever a life total changes, enter the changes to each player's, "
          "or team's, life starting with player one.\n";
  cout << "No change in life is entered as 0, and life loss is entered with a "
          "-.\n";
  cout << "Even if a player loses continue entering 0 for life change.\n\n";
  record.open("game.doc");
  if (record.fail()) {
    cout << "There was an error while trying to open players.txt!\n";
    cout << "Enter any character and hit return to end the program.\n";
    cin >> letter;
    exit(1);
  }
  do {
    // do {
    if (gamecount == 0) {
      cout << "How many players?(up to 4)\n";
      cin >> num_players;
      new_line();
      getplayers(players, num_players);
    } else {
      cout << "Same players (Y or N)?\n";
      cin >> playercheck;
      if (toupper(playercheck) == 'N') {
        cout << "How many players?(up to 4)\n";
        cin >> num_players;
        new_line();
        getplayers(players, num_players);
      }
    }
    if (gamecount == 0) {
      cout << "What play style is this (enter the corresponding number)?\n";
      cout << "1) 1v1   2) 2 headed giant 3) Commander\n";
      cin >> style;
      new_line();
    } else {
      cout << "Same style (Y or N)?\n";
      cin >> stylecheck;
      if (toupper(stylecheck) == 'N') {
        cout << "What play style is this (enter the corresponding number)?\n";
        cout << "1) 1v1   2) 2 headed giant 3) Commander\n";
        cin >> style;
        new_line();
      }
    }
    // int winner, replay = 0;
    cout << "Start Game\n";
    setlife(style, num_players, life);
    if (style == '2') { // changed from = to ==
      twoheaded();
    } else {
      multiplayer();
    }
    row1(life);
    int done = track(style, life);
    // } while (done = > 0 && cin); // added && cin for close on testing
    new_line();
    cout << "\nAnother game (Y or N)?\n";
    cin >> letter;

  } while (toupper(letter) == 'Y');

  record.close();
  return 0;
}
