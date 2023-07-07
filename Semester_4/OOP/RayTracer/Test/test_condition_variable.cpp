/*
** EPITECH PROJECT, 2023
** B-OOP-400-NCY-4-1-raytracer-antoine.khalidy
** File description:
** test
*/

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unistd.h>

using namespace std;

vector<int> vec;
mutex mtx;
condition_variable cv;
bool isRunning;

void extract(int id) {
    while (isRunning) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [id]{
            if (vec.empty()) {
                cout << "Thread " << id << " se met en pause." << endl;
            }
            if (!isRunning) {
                return true;
            }
            return !vec.empty();
        });
        if (!isRunning) {
            break;
        }

        int n = vec.back();
        vec.pop_back();

        cout << "Thread " << id << " a extrait " << n << endl;
        lock.unlock();


    }
    std::cout << "Thread " << id << " a fini." << std::endl;
}

void fillv()
{
    while (isRunning) {
        unique_lock<mutex> lock(mtx);
        if (vec.empty()) {
            for (int i = 0; i < 50; i++) {
            vec.push_back(i);
            }

            lock.unlock();
            cv.notify_all();
        }


        this_thread::sleep_for(chrono::seconds(1));
    }
    std::cout << "Thread fillv a fini." << std::endl;
}

int main() {
    isRunning = true;
    thread t1(extract, 1);
    thread t2(extract, 2);
    thread t3(extract, 3);

    thread t4(fillv);

    sleep(2);
    isRunning = false;
    cv.notify_all();

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
