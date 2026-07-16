#include <iostream>  // 1. Input/Output stream library (cout ke liye zaroori hai)
#include <iomanip>   // 2. Output manipulation library (formatting ke liye zaroori hai)

// Preprocessor Macro: Compile hone se pehle poore code mein speed_of_light ko replace kar dega
#define SPEED_OF_LIGHT 299792.458 

int main() {
    // 3. Data Initialization (RAM mein variables ke liye space allocate ho rahi hai)
    int spacecraftId = 8804;
    double distanceFromEarth = 149597870.7; // Earth se Sun ka distance (km)
    float orbitalVelocity = 28.5456f;       // Orbital speed (km/s)
    char engineStatusFlag = 'A';            // 'A' for Active, 'E' for Error
    bool warpDriveReady = true;

    std::cout << std::fixed; 

    std::cout << "==================================================\n";
    std::cout << "       DEEP SPACE TELEMETRY CORE INITIALIZED      \n";
    std::cout << "==================================================\n";

    // std::setw(25) text ko left side par alignment deta hai (Professional layout)
    std::cout << std::left << std::setw(25) << "SPACECRAFT IDENTIFIER" << ": SPX-" << spacecraftId << "\n";
    std::cout << std::left << std::setw(25) << "ENGINE STATUS CODE"    << ": [" << engineStatusFlag << "]\n";
    
    // std::setprecision decimal ke baad ke numbers ko control karta hai
    std::cout << std::left << std::setw(25) << "ORBITAL VELOCITY"     << ": " << std::setprecision(2) << orbitalVelocity << " km/s\n";
    std::cout << std::left << std::setw(25) << "TOTAL SECTOR DISTANCE" << ": " << std::setprecision(1) << distanceFromEarth << " km\n";
    
    // Ternary operator check (Boolean state control)
    std::cout << std::left << std::setw(25) << "WARP ENGINE STATE"     << ": " << (warpDriveReady ? "ONLINE (1)" : "OFFLINE (0)") << "\n";
    std::cout << "--------------------------------------------------\n";

    // 6. Real Math/Physics Calculation using Macro
    double timeToTarget = distanceFromEarth / SPEED_OF_LIGHT;
    std::cout << "CRITICAL TELEMETRY CALCULATION:\n";
    std::cout << "Signal connection latency to Earth terminal:\n";
    std::cout << ">> " << std::setprecision(4) << timeToTarget << " Seconds\n";
    std::cout << "==================================================\n";

    // 7. Hardware Kernel Memory Audit
    // sizeof() variable ka exact size (Bytes) hardware level par check karta hai
    std::cout << "\n[KERNEL AUDIT] Memory Allocated on Win-64 Architecture:\n";
    std::cout << "ID: " << sizeof(spacecraftId) << " Bytes | Distance: " << sizeof(distanceFromEarth) << " Bytes | Status: Operational\n";

    return 0; // Windows OS ko 0 (Success Sign) bhejna ke code bina crash chal gaya
}
