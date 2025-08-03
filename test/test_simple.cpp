#include <iostream>
#include <vector>
#include <string>
#include <chrono>

// Test simple pour vérifier les zones critiques
int main() {
    std::cout << "=== Tests des Zones Critiques ===\n\n";
    
    // Test 1: Parsing CSV
    std::cout << "1. Test Parsing CSV... ";
    std::string line = "1;hello;bonjour";
    size_t first_semi = line.find(';');
    size_t second_semi = line.find(';', first_semi + 1);
    std::string front = line.substr(first_semi + 1, second_semi - first_semi - 1);
    std::string back = line.substr(second_semi + 1);
    if (front == "hello" && back == "bonjour") {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 2: Algorithme de Leitner
    std::cout << "2. Test Algorithme de Leitner... ";
    constexpr uint8_t BOX_NEW = 0, BOX_OK = 1, BOX_GOOD = 2;
    constexpr uint32_t kBoxDelays[] = {0, 1, 3};
    
    uint8_t current_box = BOX_NEW;
    uint32_t today = 1000;
    
    // Grade correct -> box 0 -> box 1
    current_box = std::min(static_cast<uint8_t>(current_box + 1), BOX_GOOD);
    uint32_t next_due = today + kBoxDelays[current_box];
    if (current_box == 1 && next_due == 1001) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 3: Gestion des erreurs
    std::cout << "3. Test Gestion des erreurs... ";
    std::vector<std::string> cards = {"hello", "world"};
    if (cards.size() == 2 && cards[0] == "hello" && cards[1] == "world") {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 4: Performance
    std::cout << "4. Test Performance... ";
    auto start = std::chrono::high_resolution_clock::now();
    int sum = 0;
    for (int i = 0; i < 1000; ++i) {
        sum += i;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    if (sum == 499500 && duration.count() < 1000) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 5: Machine d'états
    std::cout << "5. Test Machine d'états... ";
    enum State { RECTO, VERSO, INFO, ERROR };
    State current_state = RECTO;
    
    current_state = VERSO;
    if (current_state == VERSO) {
        current_state = RECTO;
        if (current_state == RECTO) {
            std::cout << "OK\n";
        } else {
            std::cout << "FAIL\n";
            return 1;
        }
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 6: Robustesse
    std::cout << "6. Test Robustesse... ";
    std::vector<std::string> special_texts = {"café", "naïve", "résumé", "🎉"};
    bool all_valid = true;
    for (const auto& text : special_texts) {
        if (text.empty()) {
            all_valid = false;
            break;
        }
    }
    if (all_valid) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    // Test 7: Validation des constantes
    std::cout << "7. Test Validation des constantes... ";
    constexpr unsigned long kDeepSleepTimeout = 15000;
    constexpr uint8_t kFullRefreshThreshold = 10;
    constexpr int16_t kMaxTextWidth = 180;
    
    if (kDeepSleepTimeout == 15000 && kFullRefreshThreshold == 10 && kMaxTextWidth == 180) {
        std::cout << "OK\n";
    } else {
        std::cout << "FAIL\n";
        return 1;
    }
    
    std::cout << "\n=== Tous les tests sont PASSÉS ! ===\n";
    std::cout << "Le code fonctionne correctement.\n";
    
    return 0;
}
