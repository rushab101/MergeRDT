#include <ostream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <set>

#include "../src/state_based/PNCounterSB.hpp"
#include "../src/state_based/GCounterSB.hpp"
#include "../src/state_based/GMapSB.hpp"
#include "../src/state_based/GSetSB.hpp"
#include "../src/state_based/MultiSetSB.hpp"
#include "../src/state_based/ORSetSB.hpp"
#include "../src/state_based/PriorityQueueSB.hpp"
#include "../src/state_based/TwoPSetSB.hpp"
#include "../src/state_based/VectorSB.hpp"
#include "../src/operation_based/StringOB.hpp"
#include "../src/state_based/LWWMultiSetSB.hpp"

int main(int argc, char* argv[])
{
	std::string filePath = "/home/tapasvi/workspace/CRDT-Library/test_application/json/temp.json";

	// PN COUNTER
	/*
	crdt::state::PNCounterMetadata<uint32_t> replica1A(1,10);
	crdt::state::PNCounterMetadata<uint32_t> replica1B(2,20);
	
	std::cout << replica1A.serialize() << std::endl;
	std::cout << replica1B.serialize() << std::endl;
	replica1B.serializeFile(filePath);

	crdt::state::PNCounterMetadata<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.queryId() << std::endl;
	std::cout << replica1C.queryPayloadP() << std::endl;
	std::cout << replica1C.queryPayloadN() << std::endl;
	*/
	// PN COUNTER END

	// GCOUNTER START
	/*
	crdt::state::GCounterMetadata<uint32_t> replica1A(1,6);
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::GCounterMetadata<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.queryId() << std::endl;
	std::cout << replica1C.queryPayload() << std::endl;
	*/
	// GCOUNTER END

	// GMAP START
	/*
	crdt::state::GMapMetadata<uint32_t, uint32_t> replica1A(1,0,1);
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::GMapMetadata<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// GMAP END

	// GSET BEGIN
	/*
	crdt::state::GSetMetadata<std::string> replica1A(1,"bob");
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::GSetMetadata<std::string> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// GSET END

	// MULTISET START
	/*
	crdt::state::MultiSetMetadata<uint32_t> replica1A(0,5);
	replica1A.insert({2,6,4,6,2,16,2,1,6,7});
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::MultiSetMetadata<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// MULTISET END

	// ORSET START
	/*
	crdt::state::ORSetMetadata<std::string> replica1A(3,{"bob","alice","charlie","jack"});
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::ORSetMetadata<std::string> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// ORSET END

	// PRIORITY QUEUE START
	/*
	crdt::state::PriorityQueueMetadata<std::string> replica1A(0,"hi");
	replica1A.push("you");
	replica1A.push("me");
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::PriorityQueueMetadata<std::string> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// PRIORITY QUEUE END

	// 2PSET START
	/*
	crdt::state::TwoPSetMetadata<uint32_t> replica1A(3,{7,8,9,10});
	replica1A.remove(7);
	replica1A.remove(7);
	replica1A.remove(8);
	replica1A.remove(9);
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::TwoPSetMetadata<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// 2PSET END

	// VECTOR START
	/*
	crdt::state::VectorMetadata<std::string> replica1A(3,"bob");
	replica1A.push_back("alice");
	replica1A.push_back("george");
	//replica1A.push_back(10);
	//replica1A.push_back(36);
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::state::VectorMetadata<std::string> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// VECTOR END

	// STRING START
	/*
	crdt::operation::StringMetaData<std::string> replica1A(0, "AB+++CDEFG");
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);

	crdt::operation::StringMetaData<uint32_t> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// STRING END

	// LWWMULTISET START
	/*
	crdt::state::LWWMultiSetMetadata<std::string> replica1A(0,"taps",0); //Added at time = 0
	replica1A.insert(0,{"bob","cat","fish","goat","lion","mufasa","disney","elephant"});
	std::cout << replica1A.serialize() << std::endl;
	replica1A.serializeFile(filePath);
		
	crdt::state::LWWMultiSetMetadata<std::string> replica1C;
	replica1C.deserializeFile(filePath);
	std::cout << replica1C.serialize() << std::endl;
	*/
	// LWWMULTISET END

	return 0;
}

/*
	Testing JSON related functionality


	json j;

	j["pi"] = 123;
	j["name"] = "taps";

	std::cout << j << std::endl;

	std::ofstream o("sample.json");
	o << j << std::endl;
	return 0;

*/
