#include "stdafx.h"
#include <iostream>

/*
Call Center:  Imagine you have a call center with three levels of employees: respondent, manager, and director.  An incoming
telephone call must be first allocated to a respondent who is free.  If the respondent can't handle the call, he or she 
must escalate the call to a manager.  If the manager is not free or not able to handle it, then the call should be escalated
to a director.  Design the classes and data structures for this problem.  Implement a method dispatchCall() which assigns 
a call to the first available employee.
*/



/*
Idea:  Have 3 queues, one for each level of employee, such that the next available employee at each level is at the front
of the queue.  When an employee either (i) finishes a call, or (2) escalates a call to an employee one level up, then 
that employee is put into the back of their corresponding queue.  

dispatchCall() pops a person off their queue and assigns the call to them.  If the respondent queue is empty, it 
considers the manager queue, and if that's also empty then it considers the director queue.
The "PhoneCall" class will take care of putting that employee back into a queue.  
The "Employee" will know which queue he/she belongs to.

I'm not sure that this is worth coding.  Seems pretty straightforward.
*/




int main()
{
    return 0;
}

