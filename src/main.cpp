#include "crow_all.h"                     // Direct reference target
#include "include/routes/ProductRoutes.h" // Root configuration tracking
#include <iostream>

int main() {
    crow::SimpleApp app;
    std::cout << "[SERVER] Initializing stable MongoDB local system pipeline driver...\n";
    ProductRoutes::init(app);
    app.port(18080).multithreaded().run();
    return 0;
}
