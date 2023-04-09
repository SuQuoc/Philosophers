


void philo_eats(t_philo *philo)
{
    int eating_time;
    pthread_mutex_lock(&philo->data->time_print_lock);//LOCK
    eating_time = philo->data->t_eat;
    pthread_mutex_unlock(&philo->data->time_print_lock);//UNLOCK
    
    
    usleep(eating_time * 1000);
    

    
    pthread_mutex_lock(&philo->data->time_print_lock);//LOCK
    philo->last_meal = philo->timestamp;
    philo->meals++;
    pthread_mutex_unlock(&philo->data->time_print_lock);//UNLOCK
}

void grab_first_fork_if_w_grab_second(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *sec)
{
    
    
    pthread_mutex_lock(first);
   
    
    pthread_mutex_lock(&philo->data->time_print_lock);
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    
    printf("%lld Philo number %d grabed first fork\n", philo->timestamp, philo->name);      
    pthread_mutex_unlock(&philo->data->time_print_lock);
    

    
    pthread_mutex_lock(sec); 
    pthread_mutex_lock(&philo->data->time_print_lock);
    get_time_in_ms(&philo->t_in_ms);
    set_rel_timestamp(philo);
    printf("%lld Philo number %d grabed sec fork\n", philo->timestamp, philo->name);      
    printf("%lld Philosopher %d is eating\n", philo->timestamp, philo->name);
    pthread_mutex_unlock(&philo->data->time_print_lock);
    philo_eats(philo);
        

    pthread_mutex_unlock(sec);
    pthread_mutex_unlock(first);
}