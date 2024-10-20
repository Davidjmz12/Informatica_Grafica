#include "metrics/metrics.hpp"



int main()
{
    Metrics m = Metrics();
    m.start_timer_metric("test","Test timer metric");
    for(int i = 0; i < 1000000; i++)
        int j = i;
    m.finish_timer_metric("test");
    m.print_metrics();
    return 0;
}

