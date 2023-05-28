# osActiveObject

## Description:

This project is a demonstration of the Active Object Design Pattern implemented in C. Active Object Design Pattern decouples method execution from method invocation in order to enhance concurrency and simplify synchronized access to an object that resides in its own thread of control.

In this program, the pipeline of active objects (essentially, threads with assigned roles) that generate, print, check, and manipulate numbers is an example of the Active Object Pattern. Each active object is independent and safe to use concurrently with the others. The method invocation on the active object (enqueueActiveObject) is decoupled from its execution (runActiveObject) by a queue which is thread-safe due to the use of mutex locks.

The four active objects perform functions on a number: randomly generating a six-digit number, printing and checking if it's prime, adding 11 and rechecking if it's prime, subtracting 13 and rechecking, and finally, adding 2 and rechecking.

All tests have been performed on a MacBook Pro with an ARM processor using the UTM virtual machine to run GCC (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0.

## How to use

```sh
  git clone https://github.com/NickBres/osActiveObject.git
  cd osActiveObject/
  make
  ./st_pipeline <tasksNum> <seed>
   ```
 seed - optional value for random number generator. if seed is null it will use time(0)
 
 ## Screenshots
 
 ![image](https://github.com/NickBres/osActiveObject/assets/70432147/5ac90e85-a137-41ef-a717-80c02158fa2e)
![image](https://github.com/NickBres/osActiveObject/assets/70432147/ec69405e-fc6c-4303-b046-56371cf3849b)
![image](https://github.com/NickBres/osActiveObject/assets/70432147/380c571f-af84-4ccc-a2e6-f3041cbf151a)
