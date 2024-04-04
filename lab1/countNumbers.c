#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "countNumbers.h"



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