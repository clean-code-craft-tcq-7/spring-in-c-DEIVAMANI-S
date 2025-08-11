#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct Stats {
    float average;
    float min;
    float max;
};

struct Stats compute_statistics(const float* numbers, int count);
int setStatisticstoNaN(struct Stats* statistics);
int checkValueAbsurdity(const float* numbers, int count);

#ifdef __cplusplus
}
#endif