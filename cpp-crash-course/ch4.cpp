#include <iostream>
#include <thread>
#include <chrono>


using namespace std::literals;

struct TimerClass
{
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::string name;
    bool moved_from;

    TimerClass(char const* name)
        : timestamp{std::chrono::system_clock::now()}
        , name{name}
        , moved_from{false}
    {
        std::cout << "TimerClass() of " << name << std::endl;
    }

    TimerClass(TimerClass const& timer)
        : timestamp{timer.timestamp}
        , name{timer.name}
        , moved_from{timer.moved_from}
    {
        std::cout << "copy ctor TimerClass" << std::endl;
    }

    TimerClass& operator=(TimerClass const& timer)
    {
        std::cout << "copy assignment TimerClass" << std::endl;
        timestamp = timer.timestamp;
        name = timer.name;
        moved_from = timer.moved_from;
        return *this;
    }
    
    TimerClass(TimerClass&& timer)
        : timestamp{timer.timestamp}
        , name{std::move(timer.name)}
        , moved_from{timer.moved_from}
    {
        std::cout << "move ctor TimerClass" << std::endl;
        timer.moved_from = true;
    }

    TimerClass& operator=(TimerClass&& timer)
    {
        std::cout << "move assignment TimerClass" << std::endl;
        timestamp = timer.timestamp;
        name = std::move(timer.name);
        timer.moved_from = true;
        return *this;
    }

    ~TimerClass()
    {
        auto end_timestamp = std::chrono::system_clock::now();
        std::cout << "~TimerClass()" << std::endl; 
        if (!moved_from)
        {
            std::cout << "[" 
                << name 
                << "] Time elapsed (ms): " 
                << (end_timestamp - timestamp) / 1ms 
                << std::endl;
        }
    }
};

void f(TimerClass t)
{
    std::cout << "void f(TimerClass&& t);" << std::endl;
    std::cout << "name of t " << t.name << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    // f(std::move(TimerClass("Test")));
    // auto t2 = std::move(t);

    std::cout << "Hello World!" << std::endl;
    return 0;
}