#include <iostream>
#include <iomanip>   

#define SPEED_OF_LIGHT 299792.458 

int main() {
    int spacecraftId = 8804;
    double distanceFromEarth = 149597870.7;
    float orbitalVelocity = 28.5456f;       
    char engineStatusFlag = 'A';            
    bool warpDriveReady = true;

    std::cout << std::fixed; 

    std::cout << "==================================================\n";
    std::cout << "       DEEP SPACE TELEMETRY CORE INITIALIZED      \n";
    std::cout << "==================================================\n";

    std::cout << std::left << std::setw(25) << "SPACECRAFT IDENTIFIER" << ": SPX-" << spacecraftId << "\n";
    std::cout << std::left << std::setw(25) << "ENGINE STATUS CODE"    << ": [" << engineStatusFlag << "]\n";
    
    std::cout << std::left << std::setw(25) << "ORBITAL VELOCITY"     << ": " << std::setprecision(2) << orbitalVelocity << " km/s\n";
    std::cout << std::left << std::setw(25) << "TOTAL SECTOR DISTANCE" << ": " << std::setprecision(1) << distanceFromEarth << " km\n";
    
    std::cout << std::left << std::setw(25) << "WARP ENGINE STATE"     << ": " << (warpDriveReady ? "ONLINE (1)" : "OFFLINE (0)") << "\n";
    std::cout << "--------------------------------------------------\n";

    double timeToTarget = distanceFromEarth / SPEED_OF_LIGHT;
    std::cout << "CRITICAL TELEMETRY CALCULATION:\n";
    std::cout << "Signal connection latency to Earth terminal:\n";
    std::cout << ">> " << std::setprecision(4) << timeToTarget << " Seconds\n";
    std::cout << "==================================================\n";

    std::cout << "\n[KERNEL AUDIT] Memory Allocated on Win-64 Architecture:\n";
    std::cout << "ID: " << sizeof(spacecraftId) << " Bytes | Distance: " << sizeof(distanceFromEarth) << " Bytes | Status: Operational\n";

    return 0; 
}
