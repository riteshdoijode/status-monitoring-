#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <cpr/cpr.h>

using namespace std;

// Telegram Bot Credentials
const string TELEGRAM_BOT_TOKEN = "YOUR_TELEGRAM_BOT_TOKEN";
const string CHAT_ID = "YOUR_CHAT_ID";

// System Thresholds
const float CPU_THRESHOLD = 80.0;   // Alert if CPU usage > 80%
const float RAM_THRESHOLD = 4.0;    // Alert if RAM usage < 4 GB
const float DISK_THRESHOLD = 90.0;  // Alert if disk usage > 90%
const float NETWORK_THRESHOLD = 500.0; // Alert if network usage is below 500 KB/s

// Function to send Telegram messages
void sendTelegramMessage(const string &message) {
    string url = "https://api.telegram.org/bot" + TELEGRAM_BOT_TOKEN + "/sendMessage";
    cpr::Response r = cpr::Post(cpr::Url{url},
                                cpr::Payload{{"chat_id", CHAT_ID}, {"text", message}});
    if (r.status_code == 200) {
        cout << "Telegram message sent successfully.\n";
    } else {
        cout << "Failed to send message. Status code: " << r.status_code << endl;
    }
}

// Function to execute Python script and get system stats
string getSystemStats(const string &command) {
    string data;
    FILE *stream;
    char buffer[256];

    stream = popen(command.c_str(), "r");
    if (stream) {
        while (fgets(buffer, sizeof(buffer), stream) != nullptr) {
            data += buffer;
        }
        pclose(stream);
    }
    return data;
}

// Function to monitor system health
void monitorSystem() {
    while (true) {
        string cpu_usage = getSystemStats("python3 -c \"import psutil; print(psutil.cpu_percent())\"");
        string ram_usage = getSystemStats("python3 -c \"import psutil; print(psutil.virtual_memory().available / (1024 ** 3))\"");
        string disk_usage = getSystemStats("python3 -c \"import psutil; print(psutil.disk_usage('/').percent)\"");
        string net_usage = getSystemStats("python3 -c \"import psutil; print(psutil.net_io_counters().bytes_recv / 1024)\"");

        float cpu = stof(cpu_usage);
        float ram = stof(ram_usage);
        float disk = stof(disk_usage);
        float net = stof(net_usage);

        string message = "System Status:\nCPU: " + to_string(cpu) + "%\nRAM: " + to_string(ram) + " GB\nDisk: " +
                         to_string(disk) + "%\nNetwork: " + to_string(net) + " KB/s";

        sendTelegramMessage(message);

        if (cpu > CPU_THRESHOLD) {
            sendTelegramMessage("⚠️ High CPU Usage: " + to_string(cpu) + "%");
        }
        if (ram < RAM_THRESHOLD) {
            sendTelegramMessage("⚠️ Low RAM: " + to_string(ram) + " GB");
        }
        if (disk > DISK_THRESHOLD) {
            sendTelegramMessage("⚠️ High Disk Usage: " + to_string(disk) + "%");
        }
        if (net < NETWORK_THRESHOLD) {
            sendTelegramMessage("⚠️ Low Network Activity: " + to_string(net) + " KB/s");
        }

        this_thread::sleep_for(chrono::minutes(5)); // Monitor every 5 minutes
    }
}

int main() {
    sendTelegramMessage("🖥️ System Monitoring Started...");
    monitorSystem();
    return 0;
}
