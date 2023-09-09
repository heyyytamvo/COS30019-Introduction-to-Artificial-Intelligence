#include <iostream>
using namespace std;

// Function to evaluate the logical implication (=>)
bool implication(bool p, bool q) {
    return !p || q;
}

int main() {
    // Loop through all possible combinations of truth values for p1, p2, p3, c, e, b, f, g, d, and h
    bool d_entailed_from_kb = true;
    for (int p1 = 0; p1 < 2; p1++) {
        for (int p2 = 0; p2 < 2; p2++) {
            for (int p3 = 0; p3 < 2; p3++) {
                for (int c = 0; c < 2; c++) {
                    for (int e = 0; e < 2; e++) {
                        for (int b = 0; b < 2; b++) {
                            for (int f = 0; f < 2; f++) {
                                for (int g = 0; g < 2; g++) {
                                    for (int d = 0; d < 2; d++) {
                                        for (int h = 0; h < 2; h++) {
                                            // Evaluate the truth values of the given statements
                                            bool statement1 = implication(p2, p3);
                                            bool statement2 = implication(p3, p1);
                                            bool statement3 = implication(c, e);
                                            bool statement4 = implication(b && e, f);
                                            bool statement5 = implication(f && g, h);
                                            bool statement6 = implication(p1, d);
                                            bool statement7 = implication(p1 && p3, c);

                                            if (statement1 && statement2 && statement3 && statement4 && statement5 && statement6 && statement7 && !d){
                                                d_entailed_from_kb = false;
                                                cout << "NO" << endl;
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "YES" << endl;

    return 0;
}
