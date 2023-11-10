#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

// Define a structure for the Huffman tree node
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Custom comparator for the priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Function to build the Huffman tree
HuffmanNode* buildHuffmanTree(map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create a leaf node for each character and add it to the minHeap
    for (const auto& pair : frequencies) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build the Huffman tree by merging nodes
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with the sum of frequencies of its children
        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // Add the new node back to the minHeap
        minHeap.push(newNode);
    }

    // The remaining node is the root of the Huffman tree
    return minHeap.top();
}

// Function to print Huffman codes for characters
void printHuffmanCodes(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        huffmanCodes[root->data] = code;
        cout << root->data << ": " << code << endl;
    }

    printHuffmanCodes(root->left, code + "0", huffmanCodes);
    printHuffmanCodes(root->right, code + "1", huffmanCodes);
}

int main() {
    string inputString = "she sells sea shells at the sea shore";
    map<char, int> frequencies;

    // Calculate character frequencies
    for (char c : inputString) {
        if (c != ' ') {
            frequencies[c]++;
        }
    }

    // Build the Huffman tree
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Create a map to store Huffman codes
    map<char, string> huffmanCodes;

    // Generate Huffman codes and print them
    printHuffmanCodes(root, "", huffmanCodes);

    return 0;
}
