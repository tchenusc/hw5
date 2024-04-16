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
bool assignDaily(const AvailabilityMatrix& avail,
                 const size_t dailyNeed,
                 const size_t maxShifts,
                 DailySchedule& sched, int n, int d, vector<int>& numShiftsScheduled);
bool checkValidity(const size_t maxShifts, DailySchedule& sched, size_t day, vector<int>& numShiftsScheduled, Worker_T id);

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
    
    size_t numWorkers = avail[0].size();
    if (numWorkers < dailyNeed) return false;
    
    vector<int> numShiftsScheduled(numWorkers);
    fill(numShiftsScheduled.begin(), numShiftsScheduled.end(), 0);
    
    for (size_t i = 0; i < avail.size(); i++)
    {
        vector<Worker_T> dailySched;
        for (size_t i = 0; i < dailyNeed; i++)
        {
            dailySched.push_back(INVALID_ID);
        }
        sched.push_back(dailySched);
    }
    
    
    bool status = assignDaily(avail, dailyNeed, maxShifts, sched, 0, 0, numShiftsScheduled);
    return status;

}

bool assignDaily(const AvailabilityMatrix& avail,
                 const size_t dailyNeed,
                 const size_t maxShifts,
                 DailySchedule& sched, int n, int d, vector<int>& numShiftsScheduled)
{
    if ((unsigned int)n == avail.size()-1 && (unsigned int)d == dailyNeed)
    {
        return true;
    }
    
    if ((unsigned int)d >= dailyNeed)
    {
        return assignDaily(avail, dailyNeed, maxShifts, sched, n+1, 0, numShiftsScheduled);
    }
    
    
    for (size_t i = 0; i < avail[0].size(); i++)
    {
        sched[n][d] = i;
        numShiftsScheduled[i]++;
        if (avail[n][i] == 1 && checkValidity(maxShifts, sched, n, numShiftsScheduled, i)) // is available
        {
            bool status = assignDaily(avail, dailyNeed, maxShifts, sched, n, d+1, numShiftsScheduled);
            if (status) return true;
        }
        numShiftsScheduled[i]--;
    }
    sched[n][d] = INVALID_ID;
    return false;
}

bool checkValidity(const size_t maxShifts, DailySchedule& sched, size_t day, vector<int>& numShiftsScheduled, Worker_T id)
{
    if (count(sched[day].begin(), sched[day].end(), id) != 1) return false;
    if ((unsigned int)numShiftsScheduled[id] > maxShifts) return false;
    return true;
}
