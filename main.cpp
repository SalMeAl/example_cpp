//Example of interacting with user LEDs using cpp Language
//Salvador Medina Alonzo
//04/05/2020
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

#define LED_PATH "/sys/class/leds/beaglebone:green:usr"

class LED{
    private:
        string path;
        int number;
        virtual void writeLED(string fileName, string value);
        virtual void removeTrigger();
    public:
        LED(int number);
        virtual void turnOn();
        virtual void turnOff();
        virtual void flashing();
        virtual ~LED();
};

LED::LED(int number){
    this->number = number;
    ostringstream ledString;
    ledString << LED_PATH << number;
    path = string(ledString.str());
}

void LED::writeLED(string fileName, string value){
    ofstream fs;
    fs.open((path + fileName).c_str());
    fs << value;
    fs.close();
}

void LED::removeTrigger(){
    writeLED("/trigger", "none");
}

void LED::turnOn(){
    cout << "LED" << number << " on" << endl;
    removeTrigger();
    writeLED("/trigger", "1");
}

void LED::turnOff(){
    cout << "LED" << number << " off" << endl;
    removeTrigger();
    writeLED("/trigger", "0");
}

void LED::flashing(){
    cout << "LED" << number << " flashing" << endl;
    removeTrigger();
    writeLED("/trigger", "timer");
    writeLED("/delay_on", "50");
    writeLED("/delay_off", "50");
}

LED::~LED(){
    cout << "removing LED..." << number << endl;
}

//Main function:
int main(int argc, char* argv[]){
    if(argc!=2){
        cout << "Error" << endl;
        cout << "Try tiping: on, off or flashing" << endl;
        return 2;
    }
    cout << "Starting LED app" << endl;
    string cmd(argv[1]);
    LED leds[4]={ LED(0), LED(1), LED(2), LED(3)};
    for(int i=0; i<=3; i++){
        if(cmd=="on")
            leds[i].turnOn();
        else if(cmd=="off")
            leds[i].turnOff();
        else if(cmd=="flashing")
            leds[i].flashing();
        else
            cout << "Wrong command passed!!!" << endl;
            //cout << "Try tiping: on, off or flashing" << endl;
    }
    cout << "Script done" << endl;
}