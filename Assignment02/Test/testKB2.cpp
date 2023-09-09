#include <iostream>
using namespace std;

bool conjunctionOperation(bool p, bool q){
    return (p * q);
}

bool biconditionalOperation(bool p, bool q){
    return (p * q) || (!p * !q);
}

bool disjunctionOperation(bool p, bool q){
    return (p || q);
}

bool implication(bool p, bool q){
    return (!p || q);
}

bool negationOPeration(bool p){
    return (!p);
}

int main(){

    for (int a = 0; a < 2; a++){
        for (int b = 0; b < 2; b++){
            for (int c = 0; c < 2; c++){
                for (int d = 0; d < 2; d++){
                    for (int e = 0; e < 2; e++){
                        for (int f = 0; f < 2; f++){
                            for (int g = 0; g < 2; g++){
                                for (int h = 0; h < 2; h++){
                                    for (int p1 = 0; p1 < 2; p1++){
                                        for (int p2 = 0; p2 < 2; p2++){
                                            for (int p3 = 0; p3 < 2; p3++){
                                                bool s1 = implication(p2, p3);
                                                bool s2 = implication(p3, p1);
                                                bool s3 = implication(c, e);
                                                bool s4 = implication(conjunctionOperation(b, e), f);
                                                bool s5 = implication(conjunctionOperation(f, g), h);
                                                bool s6 = implication(p1, d);
                                                bool s7 = implication(conjunctionOperation(p1, p3),c);
                                                bool s8 = a;
                                                bool s9 = b;
                                                bool s10 = p2;

                                                if (s1 && s2 && s3 && s4 && s5 && s6 && s7 && s8 && s9 && s10){
                                                    if (!d){
                                                        cout << "NO" << endl;
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
        }
    }

    cout << "YES" << endl;
    return 0;
}