#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <array>
#include <vector>

constexpr std::array<int, 12> B_LUT = {0, 1, 2, 3, 4, -1, -1, 5, -1, -1, -1, 6};
constexpr std::array<int, 52> X_map = {
    0, 0, 3, 0, 6, 0, 9, 0, 0, 1,
    0, 11, 0, 13, 0, 17, 0, 0, 10, 0, 
    8, 0, 0, 0, 14, 0, 0, 7, 0, 5,
    0, 0, 0, 0, 0, 0, 4, 0, 2, 0, 
    13, 0, 0, 0, 0, 15, 0, 0, 0, 0,
    0, 12
};

int get_F2L_Index(int n1, int n2, int n3) {
    // n3 korrekció (branch-mentesen)
    int index_3 = B_LUT[n3] - (n2 < n3 ? 1 : 0);
    // végső formula
    return X_map[n1] * 42
         + B_LUT[n2]   *  6
         + index_3;
}

int process_line(const std::vector<int>& args) {
    if (args.size() != 3) {
        std::cerr << "Hiba: várható 3 argumentum, de " 
                  << args.size() << " érkezett.\n";
        return -1;
    }
    return get_F2L_Index(args[0], args[1], args[2]);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Használat: " << argv[0] << " <fájlnév>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::perror("Fájl megnyitása sikertelen");
        return 1;
    }

    std::string line;
    int previous = -1;
    int line_number = 0;

    while (std::getline(file, line)) {
        ++line_number;
        std::istringstream iss(line);
        std::vector<int> args;
        int v;
        // felveszünk max. 3 int-et
        while (args.size() < 3 && (iss >> v)) {
            args.push_back(v);
        }

        int current = process_line(args);
        if (current == -1) {
            // hibás sor, kihagyjuk
            continue;
        }

        std::cout << current << "\n";

        if (previous != -1 && current != previous + 1) {
            std::cerr << "HIBA " << line_number 
                      << ". sorban: az érték nem 1-gyel nagyobb az előzőnél!\n"
                      << "  Előző érték:  " << previous << "\n"
                      << "  Jelenlegi érték: " << current << "\n";
        }
        previous = current;
    }

    return 0;
}
