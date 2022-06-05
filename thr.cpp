#include <iostream>
#include <thread>
bool s_finished = false;

void DoWork(){
    using namespace std::literals::chrono_literals;
    std::cout << "Started thread id: " << std::this_thread::get_id() << std::endl;
    while (!s_finished){
        std::cout << "Working...\n";
        std::this_thread::sleep_for(1s);
    }
}

int main(){
    std::thread Worker(DoWork);
    std::cin.get();
    s_finished = true;
    Worker.join();
    std::cout << "Finished." << std::endl;
    std::cout << "Started thread id: " << std::this_thread::get_id() << std::endl;

    std::cin.get();
}