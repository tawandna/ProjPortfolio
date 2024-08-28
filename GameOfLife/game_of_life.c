
#include <ncurses.h>  // интерактив
#include <stdio.h>
#include <unistd.h>  // скорость и время

#define NMAX 25
#define MMAX 80
void read_generation(int generation[NMAX][MMAX]);
void print_generation(int generation[NMAX][MMAX]);
void new_generation(int generation[NMAX][MMAX]);
int new_cell(int generation[NMAX][MMAX], int i, int j);
int count_neighbours(int generation[NMAX][MMAX], int i, int j);

int main() {
    int generation[NMAX][MMAX];
    read_generation(generation);
    if (freopen("/dev/tty", "r", stdin)) {  // переоткрытие терминала
        int speed = 500000, c = 0;  //время задержки в микросекундах, пол секунды
        initscr();                  // инициализация библиотеки ncurses
        noecho();                   // ncurses отключение отображения символов
        nodelay(stdscr, TRUE);  // ncurses отключает режим ожидания ввода
        while (c != 'q') {
            print_generation(generation);  //печатает текущее поколение
            new_generation(generation);    // генерация нового поколения
            usleep(speed);                 // время между итерациями
            c = getch();                   // считывание клавиш
            if (c == 'a' && speed > 50000) {
                speed -= 50000;
            }
            if (c == 'z' && speed < 1000000) {
                speed += 50000;
            }
        }
        endwin();  // окончание работы с библиотекой ncurses
    }
    return 0;
}

void read_generation(int generation[NMAX][MMAX]) {  //
    for (int i = 0; i < NMAX; i++) {                // задали матрицу
        for (int j = 0; j < MMAX; j++) {
            generation[i][j] = 0;
        }
    }
    int c = getchar();  // чтение содержимого txt файла
    for (int i = 0; i < NMAX && c != EOF; i++) {
        for (int j = 0; j < MMAX && c != '\n' && c != EOF; j++) {
            if (c == ' ') {
                generation[i][j] = 0;
            } else {
                generation[i][j] = 1;
            }
            c = getchar();
        }
        while (c != '\n' && c != EOF) c = getchar();  // проверка на мусор
        c = getchar();
    }
}

void print_generation(int generation[NMAX][MMAX]) {
    clear();  // очистка терминала ncurses
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX; j++) {
            printw("%c", generation[i][j] ? '*' : ' ');
        }
        printw("\n");
    }
    refresh();  // обновление кадра
}

void new_generation(int generation[NMAX][MMAX]) {
    int data[NMAX][MMAX];
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < MMAX; j++) {
            data[i][j] = new_cell(generation, i, j);
        }
    }
    for (int i = 0; i < NMAX; ++i) {
        for (int j = 0; j < MMAX; ++j) {
            generation[i][j] = data[i][j];
        }
    }
}

int new_cell(int generation[NMAX][MMAX], int i, int j) {
    int ret = 0;
    int neighbours = count_neighbours(generation, i, j);
    if (neighbours == 3) ret = 1;
    if (neighbours == 2 && generation[i][j] == 1) ret = 1;
    return ret;
}

int count_neighbours(int generation[NMAX][MMAX], int i, int j) {
    int count = 0;
    for (int k = i - 1; k <= i + 1; k++) {
        for (int m = j - 1; m <= j + 1; m++) {
            count +=
                generation[(k + NMAX) % NMAX][(m + MMAX) % MMAX];  // по условию поле зациклено само на себя
        }
    }
    count -= generation[i][j];
    return count;
}
