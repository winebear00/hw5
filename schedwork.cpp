#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

bool fixSchedule(const AvailabilityMatrix& avail, DailySchedule& sched, const size_t dailyNeed, const size_t maxShift, int day, Worker_T shift, vector<int> avail_shifts);

    
//code taken from sudoku lab 9
bool fixSchedule(const AvailabilityMatrix& avail, DailySchedule& sched, const size_t dailyNeed, const size_t maxShift, int day, Worker_T shift, vector<int> avail_shifts) {

    // when the condition is true and all options are vaild
    if (day == (int)avail.size() - 1 && shift == dailyNeed) {
        return true;
    }
    // reached the end of the col need to shift to the next row
    if (shift == dailyNeed) {
        day++;
        shift = 0;
    }

    // iterate through all the possible workers 
    for (int i = 0; i < (int)avail[0].size(); i++) {
        if (avail[day][i] && avail_shifts[i] < maxShift) {
            sched[day][shift] = i;
            avail_shifts[i]++;
            // recursive case
            if(fixSchedule(avail, sched, dailyNeed, maxShift, day, shift+1, avail_shifts)){
                return true;
            }
            // backtrace
            sched[day][shift] = INVALID_ID;
            avail_shifts[i]--;
        }
    }
    return false;
    
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U) return false;
    sched.clear();
    // Add your code below 
    // initalize the sched matrix
    for(int row = 0; row < (int)avail.size(); row++) {
        vector<Worker_T> day;
        for (int col = 0; col < dailyNeed; col++) {
            day.push_back(INVALID_ID);
        }
        sched.push_back(day); 
    } 
    vector<int> avali_shifts(avail[0].size(), 0);
    return fixSchedule(avail, sched, dailyNeed, maxShifts, 0, 0, avali_shifts);
}



