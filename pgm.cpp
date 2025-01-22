#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

void executeCommand(const std::string &command) {
    int ret_code = std::system(command.c_str());
    if (ret_code != 0) {
        std::cerr << "Erro ao executar o comando: " << command << std::endl;
        exit(EXIT_FAILURE);
    }
}

void moveGeneratedFiles(const std::string &baseName, const std::string &folderName) {
    for (const auto &entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file()) {
            std::string fileName = entry.path().filename().string();

            // Mover arquivos relacionados ao baseName, arquivos específicos e backups
            if (fileName.find(baseName) == 0 || fileName == "topol.top" || fileName == "posre.itp" ||
                (fileName.front() == '#' && fileName.back() == '#')) {
                fs::rename(entry.path(), folderName + "/" + fileName);
            }
        }
    }
}


int main() {
    // Listar arquivos .pdb
    std::vector<std::string> pdbFiles;
    for (const auto &entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().extension() == ".pdb") {
            pdbFiles.push_back(entry.path().filename().string());
        }
    }

    if (pdbFiles.empty()) {
        std::cout << "Nenhum arquivo .pdb encontrado na pasta atual." << std::endl;
        return 0;
    }

    std::cout << "Arquivos .pdb encontrados:" << std::endl;
    for (size_t i = 0; i < pdbFiles.size(); ++i) {
        std::cout << i + 1 << ": " << pdbFiles[i] << std::endl;
    }

    std::cout << "Digite o número do arquivo para processar ou 0 para todos: ";
    int choice;
    std::cin >> choice;

    std::vector<std::string> filesToProcess;
    if (choice == 0) {
        filesToProcess = pdbFiles;
    } else if (choice > 0 && static_cast<size_t>(choice) <= pdbFiles.size()) {
        filesToProcess.push_back(pdbFiles[choice - 1]);
    } else {
        std::cerr << "Escolha inválida." << std::endl;
        return 1;
    }

    for (const auto &file : filesToProcess) {
        std::string baseName = file.substr(0, file.find_last_of('.'));

        // Executar comandos
        executeCommand("grep -v HOH " + file + " > " + baseName + "_clean.pdb");
        executeCommand("gmx pdb2gmx -f " + baseName + "_clean.pdb -o " + baseName + "_processed.gro -water spce");
        executeCommand("gmx editconf -f " + baseName + "_processed.gro -o " + baseName + "_newbox.gro -c -d 1.0 -bt cubic");
        executeCommand("gmx solvate -cp " + baseName + "_newbox.gro -cs spc216.gro -o " + baseName + "_solv.gro -p topol.top");

        // Criar pasta e mover arquivos
        std::string folderName = baseName;
        if (!fs::create_directory(folderName)) {
            std::cerr << "Erro ao criar pasta: " << folderName << std::endl;
            return 1;
        }

        moveGeneratedFiles(baseName, folderName);

        std::cout << "Arquivos movidos para a pasta: " << folderName << std::endl;
    }

    return 0;
}
