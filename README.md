# 🖥️ System Monitor with Telegram Alerts (C++)

This C++ program monitors system performance (CPU, RAM, Disk, and Network) and sends alerts via Telegram if any metric exceeds predefined thresholds.  

## 🚀 Features  

- ✅ **Real-time monitoring** of CPU, RAM, Disk, and Network  
- ✅ **Sends Telegram notifications** for system health updates and alerts  
- ✅ **Runs every 5 minutes** to ensure the system is within healthy limits  

## 🔧 Requirements  

### **Install Dependencies**  

Ensure you have the following installed:  

- **G++ Compiler** (`sudo apt install g++` for Linux/macOS)  
- **Python3** with `psutil` (`pip install psutil`)  
- **cpr (C++ HTTP Requests Library)**  

```
  bash
  git clone https://github.com/whoshuu/cpr.git
  cd cpr
  mkdir build && cd build
  cmake .. -DBUILD_CPR_TESTS=OFF
  make -j$(nproc)
  sudo make install
```

## Builde & Run
```
g++ -o system_monitor monitor.cpp -lcpr -pthread
```

## Run the Program
```
./system_monitor
```

# Security Note

Do not share the bot token publicly. Store it in environment variables or a config file.

