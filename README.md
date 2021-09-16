# dining_philosophers

My implementation of the classical problem of synchronization.

Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

A philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.

<img src='https://assets.leetcode.com/uploads/2019/09/24/an_illustration_of_the_dining_philosophers_problem.png' width='300px'>
The problem statement and the image above are taken from wikipedia.org


Programm runs as follows:

<code>
./philo number_of_philosophers  time_to_die  time_to_eat   time_to_sleep  [number_of_times_each_philosopher_must_eat]</code>

Time is considered to be in ms(milliseconds).
