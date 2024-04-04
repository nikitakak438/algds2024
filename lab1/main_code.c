#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>



// Функция для подсчета количества чисел от 1 до 10^n, сумма цифр которых равна k
long long countNumbers(int n, int k) {
    // Выделяем память под двумерный массив для хранения промежуточных результатов
    long long** dp = (long long**)malloc((n + 1) * sizeof(long long*)); 
    for (int i = 0; i <= n; i++) {
        dp[i] = (long long*)calloc((k + 1), sizeof(long long));
    }

    // Инициализация базовых случаев
    for (int i = 0; i <= 9 && i <= k; i++) {
        dp[1][i] = 1;
    }

    // Заполнение таблицы динамического программирования
    for (int rang = 2; rang <= n; rang++) { //разряд числа
        for (int sum = 0; sum <= k; sum++) { // сумма цифр
            for (int digit = 0; digit <= 9; digit++) {
                if (sum - digit >= 0) {
                    dp[rang][sum] += dp[rang - 1][sum - digit];
                }
                if (dp[rang][sum] < 0) {
                    return -1;
                }
            }
        }
    }

    // Записываем колличество чисел из нужной нам ячейки таблицы
    long long totalCount = dp[n][k];

    // Освобождаем память, выделенную для dp
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return totalCount;
}

int main() {
    int n, k;
    setlocale(LC_ALL, "Russian");

    // Ввод значений n и k
    printf("Введите колличество разрядов числа (n): ");
    scanf("%d", &n);
    printf("Введите суумму цифр числа (k): ");
    scanf("%d", &k);

    // Проверка корректности ввода
    if (n < 1 || k < 1) {
        printf("Неверный ввод. n и k должны быть положительными числами.\n");
        return 1;
    }

    // Подсчет и вывод результата
    long long result = countNumbers(n, k);
    if (result < 0) {
        printf("Ошибка. \nЧисло выходит за пределы типа long long.\n"); 
    }  // rang = 21; sum = 75 пример в котрой число выходит за прелелы типа long long
    else {
        printf("Количество чисел из %d разрядов, сумма цифр которых равна %d: %lld\n", n, k, result);
    }
    return 0;
}

