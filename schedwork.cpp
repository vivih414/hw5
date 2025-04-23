#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool completeSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched,
                    vector<int>& shiftTracker, size_t day, size_t slot)
{
    if(day == avail.size())
    {
        return true;
    }
    for(size_t w = 0; w < avail[0].size(); w++)
    {
        if(!avail[day][w])
        {
            continue;
        }
        if(shiftTracker[w] >= (int)maxShifts)
        {
            continue;
        }
        bool alreadyWorking = false;
        for(size_t i = 0; i < sched[day].size(); i++)
        {
            if(sched[day][i] == w)
            {
                alreadyWorking = true;
                break;
            }
        }
        if(alreadyWorking)
        {
            continue;
        }
        sched[day][slot] = w;
        shiftTracker[w]++;
        size_t next = day;
        size_t nextSlot = slot + 1;
        if(nextSlot == dailyNeed)
        {
            next++;
            nextSlot = 0;
        }
        if(completeSchedule(avail, dailyNeed, maxShifts, sched, shiftTracker, next, nextSlot))
        {
            return true;
        }
        sched[day][slot] = INVALID_ID;
        shiftTracker[w]--;
    }
    return false;
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t days = avail.size();
    size_t workers = avail[0].size();

    if(dailyNeed > workers)
    {
        return false;
    }

    sched.assign(days, std::vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<int> shiftTracker(workers, 0);
    
    return completeSchedule(avail, dailyNeed, maxShifts, sched, shiftTracker, 0, 0);
}