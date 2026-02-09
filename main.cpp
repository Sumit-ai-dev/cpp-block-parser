#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>

// Bitcoin Genesis Block (Raw Hex)
// Block Height: 0
// Hash: 000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f
const std::string GENESIS_BLOCK_HEX = 
    "01000000"          // Version (4 bytes)
    "0000000000000000000000000000000000000000000000000000000000000000" // Prev Hash (32 bytes)
    "3ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a" // Merkle Root (32 bytes)
    "29ab5f49"          // Time (4 bytes)
    "ffff001d"          // Bits (4 bytes)
    "1dac2b7c";         // Nonce (4 bytes)
    // Transaction count (VarInt) + Coinbase Transaction omitted for this header parser demo

// Utility: Convert Hex String to Byte Vector
std::vector<unsigned char> hex_to_bytes(const std::string& hex) {
    std::vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

// Utility: Reverse bytes (for Little Endian handling)
void reverse_bytes(unsigned char* start, int size) {
    std::reverse(start, start + size);
}

// Struct representing a Bitcoin Block Header (80 bytes)
struct BlockHeader {
    uint32_t version;
    unsigned char prev_hash[32];
    unsigned char merkle_root[32];
    uint32_t timestamp;
    uint32_t bits;
    uint32_t nonce;
};

int main() {
    std::cout << "Starting C++ Block Parser..." << std::endl;
    std::cout << "Parsing Genesis Block Header..." << std::endl;
    std::cout << "--------------------------------" << std::endl;

    // 1. Convert Hex to Bytes
    std::vector<unsigned char> raw_bytes = hex_to_bytes(GENESIS_BLOCK_HEX);
    
    // 2. Parse into Struct
    // Bitcoin uses Little Endian for these fields
    BlockHeader header;
    unsigned char* ptr = raw_bytes.data();

    // Copy and swap endianness
    // Version
    header.version = *(uint32_t*)ptr;
    ptr += 4;

    // Prev Hash (32 bytes)
    std::copy(ptr, ptr + 32, header.prev_hash);
    // Note: Internal hash storage is often kept reversed, but usually displayed Big Endian.
    // For this demo, we'll keep it raw.
    ptr += 32;

    // Merkle Root (32 bytes)
    std::copy(ptr, ptr + 32, header.merkle_root);
    ptr += 32;

    // Timestamp
    header.timestamp = *(uint32_t*)ptr;
    ptr += 4;

    // Bits
    header.bits = *(uint32_t*)ptr;
    ptr += 4;

    // Nonce
    header.nonce = *(uint32_t*)ptr;
    ptr += 4;

    // 3. Display Results
    std::cout << "Version:   " << header.version << std::endl;
    
    // Time (Needs conversion)
    std::time_t t = header.timestamp;
    std::cout << "Time:      " << std::put_time(std::gmtime(&t), "%c %Z") << " (" << header.timestamp << ")" << std::endl;
    
    std::cout << "Bits:      0x" << std::hex << header.bits << std::dec << std::endl;
    std::cout << "Nonce:     " << header.nonce << std::endl;

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Parsing Complete." << std::endl;

    return 0;
}
