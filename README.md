<h1 align="center">Philosophers</h1>
<p>Eat, Sleep, Spaghetti, repeat. This project is about learning how threads and mutexes work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.</p>

---

- Status: Finished
- Result: 100%

---

## Install

```sh
git clone https://github.com/itsmevitinn/Philosophers.git philosophers
```

## Usage

1. Run `cd philo` and `make` to compile program

2. Run the program with the params below 

```
./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_times_must_eat]
```

### Examples
```c
./philo 1 800 200 200 // Not have enough forks, so return error
./philo 5 800 200 200 // Nobody dies
./philo 5 800 200 200 7 // Simulation stops when all philosophers eat 7 times
./philo 4 410 200 200 // Nobody dies
./philo 4 310 200 100 // One philosopher dies
./philo 4 500 200 1.2 // Invalid arguments
./philo 4 0 200 200 // Invalid arguments
./philo 4 -500 200 200 // Invalid arguments
./philo 4 500 200 2147483647 // One philopher dies after 500ms
./philo 4 2147483647 200 200 // Nobody dies
./philo 4 200 210 200 // One philosopher dies, you should show his dead before eating time (210ms)
```

## Author

👤 **Vitor Marcondes**

- Github: [@itsmevitinn](https://github.com/itsmevitinn)
- LinkedIn: [@itsmevitinn](https://www.linkedin.com/in/itsmevitinn/)

## Show your support

Give a ⭐️ if this project helped you!
