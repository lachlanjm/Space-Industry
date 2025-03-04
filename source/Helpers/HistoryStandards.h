#ifndef HISTORY_STANDARDS_H
#define HISTORY_STANDARDS_H

#include <stdint.h>

#define MAX_HISTORY (64)
#define ITER_PER_HISTORY_TICK (40)
#define HISTORY_INT int64_t
// #define HISTORY_BIG_INT int64_t // TODO improve
#define HISTORY_FLOAT long double
#define HISTORY_FLOAT_RECALC_FACTOR (2) // 1/n

#define HISTORY_ARRAY_ID_INT uint_least16_t

#define ABS(x) ((x)>=0?(x):-(x))

// TODO test and implement
// typedef union HistoryBigInt {
//   char val[2*sizeof(int64_t)];
//   struct {
//     int64_t x;
//     int64_t y;
//   };
// } HistoryBigInt;

#endif