## Philosophers 42 Project (with Bonus)

### Overview

The Philosophers project is an implementation of the classic dining philosophers problem using multithreading (or processes in bonus) in C. The goal of the project is to simulate philosophers sitting at a table, thinking, and eating. Philosophers need to pick up two forks (represented as mutexes in mandatory part or semaphores in bonus) to eat, and they must do so in a way that avoids deadlocks.

### Usage

To run the philosophers simulation, execute the following command:

	./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]

Parameters:
-    <number_of_philosophers>: The total number of philosophers in the simulation.
-    <time_to_die>: The time in milliseconds that a philosopher can survive without eating before dying.
-    <time_to_eat>: The time in milliseconds it takes for a philosopher to eat.
-    <time_to_sleep>: The time in milliseconds a philosopher will sleep after eating.
-    <number_of_times_each_philosopher_must_eat> (optional): The number of times each philosopher must eat. If not provided, philosophers will eat indefinitely.

Example:

	./philo 5 800 200 200 3

This will run a simulation with 5 philosophers where each philosopher will eat 3 times, and the time parameters are set to 800ms to die, 200ms to eat, and 200ms to sleep.

Output:

	timestamp_in_ms 1 is thinking
	timestamp_in_ms 2 is eating
	timestamp_in_ms 3 is sleeping
	timestamp_in_ms 4 is eating
	timestamp_in_ms 5 is thinking
	...
	timestamp_in_ms 3 has died

### Dataraces and dead lock check

Threads:
- DRD: Run with valgrind to check for data races  
  	--tool=drd




- Helgrind: Run with valgrind to find lock issues and potential deadlocks and data races  
 	--tool=helgrind 

### Test cases:
One should die:

	./philo 1 800 200 200
	./philo 4 310 200 100
  
No one should die:
 
	./philo 5 600 150 150
	./philo 5 800 200 200
	./philo 4 410 200 200
	./philo 100 800 200 200
	./philo 105 800 200 200
	./philo 200 800 200 200
	./philo 4 800 200 200
 	./philo 2 170 60 60
	./philo 2 150 60 60

All philosophers have eaten the required number of times, no one should die

	./philo 4 410 200 200 12
	./philo 5 800 200 200 7
	./philo 4 410 200 200 10
	./philo 4 410 200 200 15

Each philosopher will have a chance to eat at least once / No one should die bonus (all forks in the middle of the table)

	./philo 5 210 100 100

Edge cases
	A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher
	
 	./philo 5 200 800000 200 
	./philo 5 200 800 2000000

Large-scale simulation, no deadlocks shouls occure and one philo dies
 
	./philo 199 401 200 200
No meals: one philo should die or, as option, error message

	./philo 199 401 200 200 0
