#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>

class NumberProcessor {
public:
    void processFiles(int argc, char* argv[]) {
        if (argc < 2) {
            fprintf(stderr, "Usage: %s <file1> [<file2>...]\n", argv[0]);
            return;
        }

        uint32_t totalSum = 0;

        for (int i = 1; i < argc; ++i) {
            uint32_t number;
            if (!readNumberFromFile(argv[i], number)) {
                continue;
            }
            totalSum += number;
            printNumber(number, i < argc - 1);
        }

        if (totalSum > 0) {
            printTotal(totalSum);
        }
    }

private:
    bool readNumberFromFile(const char* filename, uint32_t& number) {
        FILE* file = fopen(filename, "rb");
        if (!file) {
            fprintf(stderr, "Failed to open file: %s\n", filename);
            return false;
        }

        size_t bytesRead = fread(&number, sizeof(uint32_t), 1, file);
        if (bytesRead != 1) {
            fprintf(stderr, "Failed to read 4 bytes from file: %s\n", filename);
            fclose(file);
            return false;
        }

        fclose(file);
        number = ntohl(number);
        return true;
    }

    void printNumber(uint32_t number, bool hasNext) {
        printf("%u(0x%08x)", number, number);
        if (hasNext) {
            printf(" + ");
        }
    }

    void printTotal(uint32_t totalSum) {
        printf(" = %u(0x%08x)\n", totalSum, totalSum);
    }
};

int main(int argc, char* argv[]) {
    NumberProcessor processor;
    processor.processFiles(argc, argv);
    return 0;
}
