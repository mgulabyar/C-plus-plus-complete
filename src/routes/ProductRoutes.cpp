#include "../../include/routes/ProductRoutes.h"
#include "../../include/models/Product.h"
#include <iostream>
#include <vector>

// Database state data simulation container (Global vector acting as local DB cluster)
std::vector<Product> globalProductDB = {
    {101, "Gaming Laptop", 1250.50, 15},
    {102, "Mechanical Keyboard", 85.00, 50}
};

void ProductRoutes::init(crow::SimpleApp& app) {
    
    // ---------------------------------------------------------
    // 1. CREATE OPERATION (POST: /api/v1/products)
    // ---------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        auto body = crow::json::load(req.body); // req.body parse
        if (!body) return crow::response(400, "Invalid JSON template payload");

        Product prod;
        prod.id = body["id"].i();
        prod.name = body["name"].s();
        prod.price = body["price"].d();
        prod.stock = body["stock"].i();

        // MongoDB Database Insert Action Simulation
        globalProductDB.push_back(prod);
        std::cout << "[MONGO] insert_one() executed successfully inside products collection\n";

        crow::json::wvalue resJson;
        resJson["status"] = "success";
        resJson["message"] = "Product added to MongoDB";
        return crow::response(201, resJson);
    });

    
    // 2. READ ALL OPERATION (GET: /api/v1/products)

    CROW_ROUTE(app, "/api/v1/products")
    ([](){
        std::cout << "[MONGO] find({}) query triggered across active collection cluster\n";

        crow::json::wvalue resList;
        for(size_t i = 0; i < globalProductDB.size(); ++i) {
            resList[i]["id"] = globalProductDB[i].id;
            resList[i]["name"] = globalProductDB[i].name;
            resList[i]["price"] = globalProductDB[i].price;
            resList[i]["stock"] = globalProductDB[i].stock;
        }
        return crow::response(200, resList);
    });

    // -------------------------------------------------------------------------
    // 3. UPDATE OPERATION (PUT: /api/v1/products/<int>)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products/<int>").methods(crow::HTTPMethod::PUT)
    ([](const crow::request& req, int id){
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "Bad payload layout parameters");

        std::cout << "[MONGO] update_one() execution initiated targeting ID: " << id << "\n";

        for(auto& prod : globalProductDB) {
            if(prod.id == id) {
                prod.name = body["name"].s();
                prod.price = body["price"].d();
                prod.stock = body["stock"].i();

                crow::json::wvalue resJson;
                resJson["status"] = "success";
                resJson["message"] = "Product details fields updated inside MongoDB";
                return crow::response(200, resJson);
            }
        }
        return crow::response(404, "Product target ID referencing not found");
    });

    // -------------------------------------------------------------------------
    // 4. DELETE OPERATION (DELETE: /api/v1/products/<int>)
    // -------------------------------------------------------------------------
    CROW_ROUTE(app, "/api/v1/products/<int>").methods(crow::HTTPMethod::DELETE)
    ([](int id){
        std::cout << "[MONGO] delete_one() pipeline matching parameter identification: " << id << "\n";

        for(auto it = globalProductDB.begin(); it != globalProductDB.end(); ++it) {
            if(it->id == id) {
                globalProductDB.erase(it); // Document delete operation execution

                crow::json::wvalue resJson;
                resJson["status"] = "success";
                resJson["message"] = "Document removed securely from MongoDB collection cluster";
                return crow::response(200, resJson);
            }
        }
        return crow::response(404, "Data reference not matching document schema ID");
    });
}
