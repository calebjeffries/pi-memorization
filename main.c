#include <ncurses.h>
#include <time.h>

const char * PI = "141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129021960864034418159813629774771309960518707211349999998372978049951059731732816096318595024459455346908302642522308253344685035261931188171010003137838752886587533208381420617177669147303598253490428755468731159562863882353787593751957781857780532171226806613001927876611195909216420198";

char getchsilent() {
  noecho();
  flushinp();
  char c = getch();
  echo();
  return c;
}

void sleep(long int seconds, long int milliseconds) {
  refresh();
  nanosleep(&(struct timespec){tv_sec: seconds, tv_nsec: milliseconds * 1000000}, NULL);
}

int main() {
  initscr();
  if (has_colors() == TRUE) {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
  }
  cbreak();
  int correct;
  while (1) {
    correct = 1;
    for (int level = 2; level < 999 && correct == 1; level++) {
      addstr("Watch closely:\n3.");
      for (int printdigitnum = 0; printdigitnum < level; printdigitnum++) {
        addch(PI[printdigitnum]);
        sleep(0, 500);
      }
      sleep(3, 0);
      clear();
      addstr("Your turn:\n3.");
      for (int digitnum = 0; digitnum < level && correct == 1; digitnum++) {
        char x = (char)getchsilent();
        if (x == PI[digitnum]) {
          attron(COLOR_PAIR(1));
          addch(x);
          attroff(COLOR_PAIR(1));
          if (digitnum == level - 1) {
            addstr("\nCORRECT");
            refresh();
            sleep(1, 0);
            clear();
          }
        } else {
          attron(COLOR_PAIR(2));
          addch(x);
          attroff(COLOR_PAIR(2));
          attron(COLOR_PAIR(1));
          mvaddch(2, digitnum + 2, PI[digitnum]);
          attroff(COLOR_PAIR(1));
          addstr("\nWRONG\nPress any key to continue...");
          getchsilent();
          correct = 0;
        }
      }
    }
    addstr("\nTry again? [y/n] ");
    noecho();
    char contchar = getchsilent();
    echo();
    if (contchar == 'n' || contchar == 'N') {
      break;
    }
    clear();
  }
  endwin();
}
