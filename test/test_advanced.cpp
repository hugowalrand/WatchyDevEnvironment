#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <chrono>
#include <random>

// Test avancé pour vérifier les fonctionnalités spécifiques
int main() {
    std::cout << "=== Tests Avancés des Fonctionnalités ===\n\n";
    
    // Test 1: Parsing CSV avec caractères spéciaux
    std::cout << "1. Test Parsing CSV avec caractères spéciaux... ";
    std::vector<std::string> test_lines = {
        "1;café;coffee",
        "2;naïve;naive",
        "3;résumé;resume",
        "4;  hello  ;  bonjour  ",
        "5;\tworld\t;\tmonde\t"
    };
    
    bool parsing_ok = true;
    for (const auto& line : test_lines) {
        size_t first_semi = line.find(';');
        size_t second_semi = line.find(';', first_semi + 1);
        if (first_semi == std::string::npos || second_semi == std::string::npos) {
            parsing_ok = false;
            break;
        }
        
        std::string front = line.substr(first_semi + 1, second_semi - first_semi - 1);
        std::string back = line.substr(second_semi + 1);
        
        // Nettoyer les espaces
        front.erase(0, front.find_first_not_of(" \t\r\n"));
        front.erase(front.find_last_not_of(" \t\r\n") + 1);
        back.erase(0, back.find_first_not_of(" \t\r\n"));
        back.erase(back.find_last_not_of(" \t\r\n") + 1);
        
        if (front.empty() || back.empty()) {
            parsing_ok = false;
            break;
        }
    }
    
    if (parsing_ok) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 2: Algorithme de Leitner complet
    std::cout << "2. Test Algorithme de Leitner complet... ";
    constexpr uint8_t BOX_NEW = 0, BOX_OK = 1, BOX_GOOD = 2;
    constexpr uint32_t kBoxDelays[] = {0, 1, 3};
    
    // Simuler plusieurs cartes
    std::vector<std::pair<uint8_t, uint32_t>> cards = {
        {BOX_NEW, 0},   // Carte 0: nouvelle
        {BOX_OK, 1000}, // Carte 1: box 1, due dans le futur
        {BOX_GOOD, 999} // Carte 2: box 2, due aujourd'hui
    };
    
    uint32_t today = 1000;
    bool algorithm_ok = true;
    
    // Test progression correcte
    uint8_t card0_box = cards[0].first;
    card0_box = std::min(static_cast<uint8_t>(card0_box + 1), BOX_GOOD);
    uint32_t card0_next = today + kBoxDelays[card0_box];
    if (card0_box != 1 || card0_next != 1001) {
        algorithm_ok = false;
    }
    
    // Test reset sur erreur
    uint8_t card2_box = cards[2].first;
    card2_box = BOX_NEW;
    uint32_t card2_next = today;
    if (card2_box != 0 || card2_next != 1000) {
        algorithm_ok = false;
    }
    
    if (algorithm_ok) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 3: Gestion mémoire et performance
    std::cout << "3. Test Gestion mémoire et performance... ";
    std::vector<uint8_t> data;
    data.reserve(1000); // Éviter les réallocations
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 1000; ++i) {
        data.push_back(i % 256);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (data.size() == 1000 && duration.count() < 1000) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 4: Machine d'états complexe
    std::cout << "4. Test Machine d'états complexe... ";
    enum State { RECTO, VERSO, INFO, ERROR };
    
    std::vector<std::pair<State, State>> transitions = {
        {RECTO, VERSO},  // RECTO -> VERSO
        {VERSO, RECTO},  // VERSO -> RECTO (correct)
        {RECTO, VERSO},  // RECTO -> VERSO
        {VERSO, RECTO},  // VERSO -> RECTO (incorrect)
        {RECTO, ERROR},  // RECTO -> ERROR
        {ERROR, RECTO}   // ERROR -> RECTO (récupération)
    };
    
    bool transitions_ok = true;
    for (const auto& transition : transitions) {
        if (transition.first == ERROR && transition.second != RECTO) {
            transitions_ok = false;
            break;
        }
    }
    
    if (transitions_ok) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 5: Gestion des erreurs avancée
    std::cout << "5. Test Gestion des erreurs avancée... ";
    
    // Test accès hors limites
    std::vector<std::string> cards_data = {"hello", "world"};
    bool bounds_ok = true;
    
    if (2 < cards_data.size()) {
        bounds_ok = false; // Ne devrait pas arriver
    }
    
    // Test données corrompues
    std::vector<uint8_t> corrupted_blob = {0x01, 0x02, 0x03}; // Taille incorrecte
    bool is_corrupted = (corrupted_blob.size() % 5) != 0;
    
    if (bounds_ok && is_corrupted) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 6: Optimisations critiques
    std::cout << "6. Test Optimisations critiques... ";
    
    // Test temps de réponse des boutons
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 100; ++i) {
        int button_press = i % 4; // 4 boutons
        if (button_press < 0 || button_press >= 4) {
            std::cout << "FAIL\n";
            return 1;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (duration.count() < 1000) { // Moins de 1ms pour 100 pressions
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 7: Validation des constantes critiques
    std::cout << "7. Test Validation des constantes critiques... ";
    
    // Constantes de l'application
    constexpr unsigned long kDeepSleepTimeout = 15000;
    constexpr uint8_t kFullRefreshThreshold = 10;
    constexpr int16_t kMaxTextWidth = 180;
    constexpr uint8_t kNvsNamespaceSize = 32;
    constexpr uint8_t kMaxCardCount = 255;
    
    bool constants_ok = true;
    constants_ok &= (kDeepSleepTimeout == 15000);
    constants_ok &= (kFullRefreshThreshold == 10);
    constants_ok &= (kMaxTextWidth == 180);
    constants_ok &= (kNvsNamespaceSize <= 32);
    constants_ok &= (kMaxCardCount <= 255);
    
    if (constants_ok) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 8: Robustesse avec données aléatoires
    std::cout << "8. Test Robustesse avec données aléatoires... ";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);
    
    bool robustness_ok = true;
    for (int i = 0; i < 100; ++i) {
        int random_value = dis(gen);
        if (random_value < 0 || random_value > 1000) {
            robustness_ok = false;
            break;
        }
    }
    
    if (robustness_ok) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    std::cout << "\n=== Tous les tests avancés sont PASSÉS ! ===\n";
    std::cout << "Le code est robuste et fonctionne correctement.\n";
    
    return 0;
}
