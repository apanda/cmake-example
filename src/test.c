#include <stdio.h>
int get_month();
int get_date();
int main(int, char*[]) {
    printf("We used %d %d\n", get_month(), get_date());
}
