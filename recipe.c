Philos: eat -> put 2 forks back -> think -> wake up and think
5 args -> ac = 6
args:
number_of_philosophers
time_to_die
time_to_eat 
time_to_sleep
[number_of_times_each_philosopher_must_eat]



#include <stdio.h>
#include <pthread.h>

void routine(void)
{
    printf("Test");
}

pthread_t t1;
pthead_create(&t1, NULL, &routine);
pthread_join(t1, NULL); //wait wie process aber für threads





gettimeofday() microseconds / 1000 = milliseconds



State Change
printf("timestamp_in_ms X has taken a fork")

printf("timestamp_in_ms X is eating");
printf("timestamp_in_ms X is sleeping");
printf("timestamp_in_ms X is thinking");
printf("timestamp_in_ms X died");



creating threads 
each thread is a philo and does philo things

when do they die?
    should a thread only return if they die? 
    if (timestamp after eating )