#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

mongocxx::client getClient();

using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;

int main() {
    std::cout << "Hello, World!" << std::endl;


    mongocxx::client conn = getClient();

    auto coll = conn["test"]["collections"];

    coll.drop();

    auto doc1 = make_document(kvp("a", 1));

    auto doc2 = make_document(kvp("$set", make_document(kvp("a", 2))));


    mongocxx::model::insert_one insert_op {doc1.view()};

    auto bulk_write = coll.create_bulk_write();
    bulk_write.append(insert_op);

    bulk_write.execute();
    auto cursor = coll.find({});
    for (auto &&doc : cursor) {
        std::cout << doc["a"].get_int32() << std::endl;
    }
    return 0;
}

mongocxx::client getClient() {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{bsoncxx::string::view_or_value{"mongodb://192.168.57.101:27017"}}};
    return conn;
}
