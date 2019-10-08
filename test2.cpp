#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
int num_players;
string players[20][4];
ofstream record;
Teestream ts(cout, record);
// currently only working with dimesion [i][0]
// other dimesions for later implementation, will try atof as way to do math on
// array elements

//**
//@section DESCRITPION
//
// THis is a function fount at
// http://www.cs.technion.ac.il/~imaman/programs/teestream.html. It should allow
// a single call to an output to go to both a file and std output.
//

template <typename Elem, typename Traits = std::char_traits<Elem>>
struct basic_TeeStream : std::basic_ostream<Elem, Traits> {
  typedef std::basic_ostream<Elem, Traits> SuperType;

  basic_TeeStream(std::ostream &o1, std::ostream &o2)
      : SuperType(o1.rdbuf()), o1_(o1), o2_(o2) {}

  basic_TeeStream &operator<<(SuperType &(__cdecl *manip)(SuperType &)) {
    o1_ << manip;
    o2_ << manip;
    return *this;
  }

  template <typename T> basic_TeeStream &operator<<(const T &t) {
    o1_ << t;
    o2_ << t;
    return *this;
  }

private:
  std::ostream &o1_;
  std::ostream &o2_;
};

void new_line() {
  char next;
  do {
    cin.get(next);
  } while (next != '\n');
}
// dhould realy be a switch statment
void setlife(int S, int &num_players, int l[]) {
  int style = S, lifestart;
  cout << "In function\n";

  if (style == '1') {
    lifestart = 20;
  }
  if (style == '2') {
    cout << "in initializer\n";
    lifestart = 30;
    num_players =
        num_players / 2; // does not work with inputing odd player number
    // added to fix problem with 2heaed calculations
  }
  if (style == '3') { // these were changed from = to ==
    lifestart = 40;
  }
  for (int i = 0; i < num_players; i++) { // life inicialization added
    cout << "in for\n";
    l[i] = lifestart;
  }
}
void game(ofstream &record) {
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
  // lifestart = 40;
  // for (int i = 0; i < num_players; i++) {
  // life[i] = lifestart;
  // }

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

void twoheaded(ofstream &record) { // moved into a function
  ts << players[0][0] << "/" << players[1][0];
  ts << " vs.";
  ts << players[2][0] << "/" cout << players[3][0] << "\n\n";
  cout.width(4);
  record << setw(4);
  ts << left << "Tm1"
     << " | ";
  cout.width(4);
  record << setw(4);
  ts << right << "Tm2\n";
  ts << "_____|______\n";
  //**
  // record << "\nStart Game\n";
  // record << players[0][0];
  // record << "/";
  // record << players[1][0];
  // record << " vs. ";
  // record << players[2][0];
  // record << "/";
  // record << players[3][0];
  // record << "\n\n";
  // record << setw(4) << left << "Tm1";
  // record << " | ";
  // record << setw(4) << right << "Tm2\n";
  //  record << "_____|______\n";
}
// this function needs editing so that it records more then the last player to
// file
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
  int life[20], chan[20];
  int chan_1, newlife, chang, num_players = 2,
                              gamecount = 0; // removed unused variables
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
    do {
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

      int winner, replay = 0;
      // see if possible to skip a player so that number of inputs can go down
      cout << "Start Game\n";
      setlife(style, num_players,
              life);      // setlife(int S, int &num_players, int l[])
      if (style == '2') { // changed from = to ==
        twoheaded(record);
      } else {
        game(record);
      }

      // life setting shall become a for loop
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
    do {
      replay = 0;
      for (int c = 0; c < num_players; c++) {
        cin >> chan_1;
        chan[c] = chan_1;
        // cout << "change " << c << "is" << chan[c] << "\n";
      }
      for (int l = 0; l < num_players; l++) {
        // cout << "life " << l << "start is" << life[l] << "\n";
        newlife = life[l];
        chang = chan[l];
        life[l] = newlife + chang;
        // cout << "life " << l << "end is" << life[l] << "\n";
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
    if (style == '2') { // changed from = to ==
      cout << "Winner is Team " << winner + 1 << ".\n";
      record << "Winner is Team " << winner + 1 << ".\n";
    } else {
      cout << "Winner is " << players[winner][0] << ".\n";
      record << "Winner is " << players[winner][0] << ".\n";
    }
    gamecount = 0;
  } while (gamecount > 0 && cin); // added && cin for close on testing
  new_line();
  cout << "\nAnother game (Y or N)?\n";
  gamecount++;
  cin >> letter;
}
while (toupper(letter) == 'Y')
  ;

record.close();
return 0;
}
