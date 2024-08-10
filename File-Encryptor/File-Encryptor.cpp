#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

class Encryptor {
public:
    virtual string encrypt(const string& data, const string& key) = 0;
    virtual string decrypt(const string& data, const string& key) = 0;
};

class SimpleEncryptor : public Encryptor {
public:
    string encrypt(const string& data, const string& key) override {
        string encrypted = data;
        for (size_t i = 0; i < data.size(); ++i) {
            encrypted[i] = data[i] ^ key[i % key.size()];
        }
        return encrypted;
    }

    string decrypt(const string& data, const string& key) override {
        return encrypt(data, key);
    }
};

class CaesarEncryptor : public Encryptor {
public:
    string encrypt(const string& data, const string& key) override {
        string encrypted = data;
        int shift = key[0] % 26;
        for (char& c : encrypted) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base + shift) % 26 + base;
            }
        }
        return encrypted;
    }

    string decrypt(const string& data, const string& key) override {
        string decrypted = data;
        int shift = key[0] % 26;
        for (char& c : decrypted) {
            if (isalpha(c)) {
                char base = islower(c) ? 'a' : 'A';
                c = (c - base - shift + 26) % 26 + base;
            }
        }
        return decrypted;
    }
};

class ReverseEncryptor : public Encryptor {
public:
    string encrypt(const string& data, const string& key) override {
        string encrypted = data;
        reverse(encrypted.begin(), encrypted.end());
        return encrypted;
    }

    string decrypt(const string& data, const string& key) override {
        return encrypt(data, key);
    }
};

string generateRandomKey(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static mt19937 generator(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    string key;
    for (size_t i = 0; i < length; ++i) {
        key += charset[dist(generator)];
    }
    return key;
}

void writeFile(const string& filename, const string& data) {
    ofstream file(filename, ios::binary);
    file.write(data.c_str(), data.size());
}

string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return data;
}

void encryptFile(const string& inputFile, const string& outputFile, const vector<Encryptor*>& encryptors) {
    string data = readFile(inputFile);
    string randomKey = generateRandomKey(16);
    for (auto& encryptor : encryptors) {
        data = encryptor->encrypt(data, randomKey);
    }

    SimpleEncryptor keyEncryptor;
    string encryptedKey = keyEncryptor.encrypt(randomKey, "Abligerateduwu");
    data += encryptedKey;

    writeFile(outputFile, data);
}

void decryptFile(const string& inputFile, const string& outputFile, const vector<Encryptor*>& encryptors) {
    string data = readFile(inputFile);
    string encryptedKey = data.substr(data.size() - 16);
    data = data.substr(0, data.size() - 16);

    SimpleEncryptor keyEncryptor;
    string randomKey = keyEncryptor.decrypt(encryptedKey, "Abligerateduwu");

    for (auto it = encryptors.rbegin(); it != encryptors.rend(); ++it) {
        data = (*it)->decrypt(data, randomKey);
    }

    writeFile(outputFile, data);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: file.exe <encrypt/decrypt> --in <input file> [--out <output file>]" << endl;
        return 1;
    }

    string mode = argv[1];
    string inputFile = argv[3];
    string outputFile = (argc > 5) ? argv[5] : inputFile;

    vector<Encryptor*> encryptors = { new SimpleEncryptor(), new CaesarEncryptor(), new ReverseEncryptor() };

    if (mode == "encrypt") {
        encryptFile(inputFile, outputFile, encryptors);
    }
    else if (mode == "decrypt") {
        decryptFile(inputFile, outputFile, encryptors);
    }
    else {
        cerr << "Invalid mode. Use 'encrypt' or 'decrypt'." << endl;
        return 1;
    }

    for (auto& encryptor : encryptors) {
        delete encryptor;
    }

    return 0;
}
