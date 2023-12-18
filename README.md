
# About The Project
The Dining Philosophers Problem is a classical synchronization problem in computer science, which illustrates synchronization issues and techniques for resolving them. In this problem, there are multiple processes (philosophers) that share a limited set of resources (forks) to perform a task (eating). The challenge is to design a concurrent algorithm that allows each philosopher to access the resources they need without causing deadlock or starvation.

  ![An_illustration_of_the_dining_philosophers_problem](https://github.com/SuQuoc/Philosophers/assets/116435885/83446dde-62f7-4c6c-860e-e46a97f2913b)

When using mutex locks to solve the Dining Philosophers Problem, the key is to ensure that philosophers can only access the forks they need, one at a time, and release them when they are done eating. Here's a possible solution using mutex locks:

1. Each philosopher is represented by a thread, and each fork is represented by a mutex.
2. A philosopher must lock the mutex for the fork to their left and the mutex for the fork to their right before they can begin eating.
3. If a philosopher cannot lock both mutexes, they must wait until they become available.
4. After eating, a philosopher must unlock both mutexes, allowing other philosophers to access the forks.

However, there are still some challenges when coding the Dining Philosophers Problem with mutex locks:

1. Deadlock: If all philosophers pick up their left forks at the same time, none of them can pick up their right forks, causing a deadlock geeksforgeeks.org.
2. Starvation: If neighboring philosophers keep eating and releasing forks before a philosopher can acquire both forks, the philosopher may starve

To address these challenges, you can use various techniques such as limiting the number of philosophers entering the room, implementing a priority system, or using a different synchronization mechanism like semaphores (not allowed in this project subject) or condition variables.



# Build Instructions
### Requirements
  - Linux OS
  - c-compiler cc
  - make

### Build
#### Clone the repository
```
git clone git@github.com:SuQuoc/Philosophers.git
cd Philosophers/philo
make
```


# Usage
```
./philosophers [time to die] [time to eat] [time to sleep] [optional: number of meals]
```

__All time parameters are in millisecods and the times should not be set lower than 60ms.__
+ `time to die:` the time it takes the to die after their last meal
+ `time to eat:` time they need to eat
+ `time to sleep:` time they need so sleep
+ `number of meals:` the amount of meals they should eat at least (to end the program with time values causing an endlesss loop)



__Here are some examples:__
- No philosopher should die 
  ```
  ./philosophers 4 410 200 200
  ```


- One philosopher should die
  ```
  ./philosophers 4 310 200 100
  ```


- No philosopher should die and the simulation stops when every philsopher has eaten at least 7 times
  ```
  ./philosophers 5 800 200 200 7
  ```


## Copyright
© 2023 Benjamin D. Esham. All rights reserved.

The image "An illustration of the dining philosophers problem" is used under the terms of the Creative Commons Attribution-ShareAlike 3.0 Unported License. The original work can be found at [link to the original image on Wikipedia]: 

https://de.wikipedia.org/wiki/Philosophenproblem#/media/Datei:An_illustration_of_the_dining_philosophers_problem.png

Modifications and adaptations have been made to the original image.

Please note that the Creative Commons license requires you to provide appropriate attribution to the original author(s) and indicate if changes were made when using the image. For more information about the license, please visit: https://creativecommons.org/licenses/by-sa/3.0/

