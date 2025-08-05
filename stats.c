#include "stats.h"
#include <stddef.h>
#include <float.h>
#include <math.h>

struct Stats compute_statistics(const float* numbers, int count) {
    struct Stats stats;
    float sum = 0.0f;
    stats.min = FLT_MAX;
    stats.max = -FLT_MAX;
    int validValuesCount = 0;
    for (int i = 0; i < count; i++) {

        //One of the value in batch is invalid
        if(isnan(numbers[i])) {
            continue; // ignore NaN values
        }
        validValuesCount++;
        //Calculates min, max, avereage values based on Numbers provided for statistics 
        if (numbers[i] < stats.min) {
            stats.min = numbers[i];
        }
        if (numbers[i] > stats.max) {
            stats.max = numbers[i];
        }
        sum += numbers[i];
    }
    //All of them Invalids
    if(validValuesCount == 0) {
        stats.average = NAN;
        stats.min = NAN;
        stats.max = NAN;
        return stats;
    }
    stats.average = sum / count;
    return stats;
}