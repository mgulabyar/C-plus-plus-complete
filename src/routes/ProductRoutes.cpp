#include "crow_all.h"
#include "include/routes/ProductRoutes.h"
#include "include/models/Product.h"
#include <iostream>
#include <vector>
// Database core tracking cluster array simulation (Vector holding data records)
std::vector<Product> globalProductDB = {
    {101, "Gaming Laptop", 1250.50, 15},
    {102, "Mechanical Keyboard", 85.00, 50}
};

void ProductRoutes::init(crow::SimpleApp& app) {
    
    // -------------------------------------------------------------------------
    // 1. READ ALL INVENTORY DATA (GET: /api/v1/products)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products")
    ([](){
        std::cout << "[MONGO-SIM] find({}) query string operation executed over core collections\n";

        crow::json::wvalue responseList;
        for(size_t i = 0; i < globalProductDB.size(); ++i) {
            responseList[i]["id"] = globalProductDB[i].id;
            responseList[i]["name"] = globalProductDB[i].name;
            responseList[i]["price"] = globalProductDB[i].price;
            responseList[i]["stock"] = globalProductDB[i].stock;
        }
        return crow::response(200, responseList);
    });

    // -------------------------------------------------------------------------
    // 2. CREATE NEW PRODUCT RECORD (POST: /api/v1/products)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto bodyPayload = crow::json::load(req.body); // Parsing incoming req.body JSON
        if (!bodyPayload) return crow::response(400, "Bad Request: Corrupted JSON parameters");

        Product newProduct;
        newProduct.id = bodyPayload["id"].i();
        newProduct.name = bodyPayload["name"].s();
        newProduct.price = bodyPayload["price"].d();
        newProduct.stock = bodyPayload["stock"].i();

        // Inserting document record within data cluster persistence matrix
        globalProductDB.push_back(newProduct);
        std::cout << "[MONGO-SIM] insert_one() execution pipeline successfully committed\n";

        crow::json::wvalue dynamicResponse;
        dynamicResponse["status"] = "success";
        dynamicResponse["message"] = "Product record structural document inserted into database";
        return crow::response(201, dynamicResponse);
    });

    // -------------------------------------------------------------------------
    // 3. UPDATE INSTANCE ATTRIBUTES (PUT: /api/v1/products/<int>)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products/<int>").methods(crow::HTTPMethod::PUT)
    ([](const crow::request& req, int targetId){
        auto bodyPayload = crow::json::load(req.body);
        if (!bodyPayload) return crow::response(400, "Inbound payload tracking structure failed verification");

        std::cout << "[MONGO-SIM] update_one() matching state metrics initialization for target key ID: " << targetId << "\n";

        for(auto& dynamicProduct : globalProductDB) {
            if(dynamicProduct.id == targetId) {
                dynamicProduct.name = bodyPayload["name"].s();
                dynamicProduct.price = bodyPayload["price"].d();
                dynamicProduct.stock = bodyPayload["stock"].i();

                crow::json::wvalue successReturn;
                successReturn["status"] = "success";
                successReturn["message"] = "Entity data columns updated safely in storage engine";
                return crow::response(200, successReturn);
            }
        }
        return crow::response(404, "Target entry identifier reference referencing point not found");
    });

    // -------------------------------------------------------------------------
    // 4. PURGE SPECIFIC DOCUMENT (DELETE: /api/v1/products/<int>)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products/<int>").methods(crow::HTTPMethod::DELETE)
    ([](int targetId){
        std::cout << "[MONGO-SIM] delete_one() operational execution targeting internal index key: " << targetId << "\n";

        for(auto iteratorEngine = globalProductDB.begin(); iteratorEngine != globalProductDB.end(); ++iteratorEngine) {
            if(iteratorEngine->id == targetId) {
                globalProductDB.erase(iteratorEngine); // Document erasure from memory loop tracking pointers

                crow::json::wvalue completeResponse;
                completeResponse["status"] = "success";
                completeResponse["message"] = "Document dropped completely from storage collection indexes";
                return crow::response(200, completeResponse);
            }
        }
        return crow::response(404, "Invalid deletion context request pointer mapping parameters");
    });
}
