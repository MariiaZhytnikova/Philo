https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e
Threads:
— DRD: Run with valgrind --tool=drd to check for data races.
— Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.

Processes:
- -fsanitize=thread

Test cases:
./philo 1 800 200 200	| one should die	*
./philo 4 310 200 100	| one should die	*
./philo 5 600 150 150	| no one should die
./philo 5 800 200 200	| no one should die	*
./philo 4 410 200 200 	| no one should die	*
./philo 100 800 200 200	| no one should die
./philo 105 800 200 200	| no one should die
./philo 200 800 200 200	| no one should die -- dead bonus
./philo 4 800 200 200	| no one should die

./philo 4 410 200 200 12 |no one should die stop 12 meals
./philo 5 800 200 200 7	 |no one should die stop 7 meals	8
./philo 4 410 200 200 10 |no one should die stop 12 meals	8
./philo 4 410 200 200 15 |no one should die stop 12 meals

./philo 2 170 60 60 -->  Expected: Philosophers should survive if eating in time.
./philo 2 150 60 60 --> Expected: Philosophers should survive if eating in time.
./philo 5 210 100 100 --> Expected: Each philosopher will have a chance to eat at least once. -- No one die bonus
./philo 5 310 200 100 --> Expected: One philo has no chance to eat before dying.

/// Comment

./philo 5 200 800000 200 | Long delay before eating again (checks starvation risk). 

./philo 5 200 800 2000000 -->Expected: Runs for an extended period without issues. 
		Philosophers **might die after 200ms** if they don’t eat in time.
./philo 199 401 200 200 --> Expected: Large-scale simulation, no deadlocks / one die

./philo 199 401 200 200 0 --> Expected: Simulation starts and stops instantly. 
	No philosopher should die as the execution stops immediately.

./philo 5 800 800 800 --> Expected: Philosophers act in sync without deadlocks. 
	**Might die** if the given times are insufficient for continuous eating.

./philo 5 60 60 60 --> Expected: somebody die

**Maximum CPU load**, as philosophers constantly eat, think, 
	and sleep. **Fast starvation likely**, as the times may be too short for 
							sustained survival.
