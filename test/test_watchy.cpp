#include <unity.h>
#include <Arduino.h>

// Mock des fonctions Arduino pour les tests
unsigned long mockMillis = 0;
unsigned long millis() { return mockMillis; }
void delay(unsigned long ms) { mockMillis += ms; }

// Mock de l'écran e-paper
class MockDisplay {
public:
    String lastText = "";
    int lastX = 0, lastY = 0;
    int textSize = 1;
    bool screenFilled = false;
    
    void fillScreen(uint16_t color) {
        screenFilled = true;
    }
    
    void setCursor(int x, int y) {
        lastX = x;
        lastY = y;
    }
    
    void setTextSize(int size) {
        textSize = size;
    }
    
    void println(const String& text) {
        lastText = text;
    }
    
    void display(bool partial) {
        // Simulation de l'affichage
    }
};

MockDisplay mockDisplay;

// Tests pour les fonctionnalités Watchy
void test_display_initialization() {
    mockDisplay.fillScreen(0xFFFF);
    TEST_ASSERT_TRUE(mockDisplay.screenFilled);
}

void test_text_display() {
    mockDisplay.setCursor(10, 30);
    mockDisplay.setTextSize(2);
    mockDisplay.println("Hello Watchy!");
    
    TEST_ASSERT_EQUAL(10, mockDisplay.lastX);
    TEST_ASSERT_EQUAL(30, mockDisplay.lastY);
    TEST_ASSERT_EQUAL(2, mockDisplay.textSize);
    TEST_ASSERT_EQUAL_STRING("Hello Watchy!", mockDisplay.lastText.c_str());
}

void test_sleep_functionality() {
    unsigned long startTime = mockMillis;
    delay(1000); // Simulation du délai avant le sommeil
    TEST_ASSERT_GREATER_THAN(1000, mockMillis - startTime);
}

void test_button_wakeup() {
    // Simulation du réveil par bouton
    mockDisplay.fillScreen(0xFFFF);
    mockDisplay.println("Woken up!");
    TEST_ASSERT_EQUAL_STRING("Woken up!", mockDisplay.lastText.c_str());
}

void RUN_UNITY_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_display_initialization);
    RUN_TEST(test_text_display);
    RUN_TEST(test_sleep_functionality);
    RUN_TEST(test_button_wakeup);
    UNITY_END();
}

int main() {
    RUN_UNITY_TESTS();
    return 0;
} 