#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_TARGETS 10000
#define COORD_MAX 99

typedef struct {
    int x, y;
} Point;

int read_targets(const char* filename, Point* targets) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Ошибка: не удалось открыть файл '%s'\n", filename);
        exit(1);
    }
    int n = 0;
    int x, y;
    while (fscanf(f, "%d,%d", &x, &y) == 2 && n < MAX_TARGETS) {
        targets[n].x = x;
        targets[n].y = y;
        n++;
    }
    fclose(f);
    return n;
}

/*  квадрат расстояния (чтобы не использовать вещественную арифметику) */
static int dist_sq(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    return dx * dx + dy * dy;
}

/* считает сколько целей попадают в круг R с центром (cx, cy). */
int count_hits(const Point* targets, int n, int cx, int cy, int radius) {
    int r_sq = radius * radius;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (dist_sq(cx, cy, targets[i].x, targets[i].y) <= r_sq)
            count++;
    }
    return count;
}

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif
    if (argc != 3) {
        fprintf(stderr, "использование: %s <файл_координат> <радиус>\n", argv[0]);
        return 1;
    }
    const char* filename = argv[1];
    int radius = atoi(argv[2]);
    if (radius < 0) {
        fprintf(stderr, "ошибка: радиус отрицательный\n");
        return 1;
    }

    Point targets[MAX_TARGETS];
    int n = read_targets(filename, targets);
    if (n == 0) {
        fprintf(stderr, "В файле нет координат целей\n");
        return 1;
    }

    int best_cx = 0, best_cy = 0;
    int best_count = 0;

    for (int cx = 0; cx <= COORD_MAX; cx++) {
        for (int cy = 0; cy <= COORD_MAX; cy++) {
            int count = count_hits(targets, n, cx, cy, radius);
            if (count > best_count) {
                best_count = count;
                best_cx = cx;
                best_cy = cy;
            }
        }
    }

    printf("%d,%d\n", best_cx, best_cy);
    printf("%d\n", best_count);
    return 0;
}
