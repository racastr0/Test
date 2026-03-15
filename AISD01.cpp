#define _CRT_SECURE_NO_WARNINGS
#include <iostream>              
#include <cstring>               
#include <cstdlib>               
#include <ctime>               
#include <chrono>                
#include <functional>            
#include <iomanip>              
#include <cctype>                
using namespace std;
using namespace std::chrono;

const int UNIV = 26;

inline bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

inline char toLowerChar(char c) {
    return static_cast<char>(tolower(static_cast<unsigned char>(c)));
}

void printSet(const char* S) {
    cout << "{";
    int count = 0;
    for (int i = 0; S[i]; i++) {
        if (!isLatinLetter(S[i])) continue;
        if (count++) cout << ",";
        cout << S[i];
    }
    cout << "}";
}

void randomSet(char* S) {
    int k = 0;
    for (int i = 0; i < UNIV; i++) {
        if (rand() % 2) {
            char c = 'a' + i;
            if (rand() % 2) c = static_cast<char>(toupper(c));
            S[k++] = c;
        }
    }
    S[k] = 0;
}

void unionArr(const char* A, const char* B, char* Res) {
    strcpy(Res, A);
    for (int i = 0; B[i]; i++) {
        char cB = toLowerChar(B[i]);
        bool found = false;
        for (int j = 0; Res[j]; j++) {
            if (toLowerChar(Res[j]) == cB) {
                found = true;
                break;
            }
        }
        if (!found && isLatinLetter(B[i])) {
            int len = strlen(Res);
            Res[len] = B[i];
            Res[len + 1] = 0;
        }
    }
}

void diffArr(const char* A, const char* B, char* Res) {
    int k = 0;
    for (int i = 0; A[i]; i++) {
        char cA = toLowerChar(A[i]);
        bool inB = false;
        for (int j = 0; B[j]; j++) {
            if (toLowerChar(B[j]) == cA) {
                inB = true;
                break;
            }
        }
        if (!inB && isLatinLetter(A[i]))
            Res[k++] = A[i];
    }
    Res[k] = 0;
}

void arrayMethod(const char* A, const char* B, const char* C, const char* D, char* E) {
    char BCD[80];
    unionArr(B, C, BCD);
    unionArr(BCD, D, BCD);
    diffArr(A, BCD, E);
}

struct Node {
    char el;
    Node* next;
    Node(char e, Node* n = nullptr) : el(e), next(n) {}
};

Node* makeList(const char* S) {
    Node* head = nullptr;
    for (int i = (int)strlen(S) - 1; i >= 0; i--) {
        if (!isLatinLetter(S[i])) continue;
        head = new Node(S[i], head);
    }
    return head;
}

void freeList(Node* L) {
    while (L) {
        Node* tmp = L;
        L = L->next;
        delete tmp;
    }
}

bool inList(Node* L, char c) {
    c = toLowerChar(c);
    for (; L; L = L->next)
        if (toLowerChar(L->el) == c) return true;
    return false;
}

Node* unionList(Node* A, Node* B) {
    Node* Res = nullptr;
    for (Node* p = A; p; p = p->next)
        if (!inList(Res, p->el)) Res = new Node(p->el, Res);
    for (Node* p = B; p; p = p->next)
        if (!inList(Res, p->el)) Res = new Node(p->el, Res);
    return Res;
}

Node* diffList(Node* A, Node* B) {
    Node* Res = nullptr;
    for (Node* p = A; p; p = p->next) {
        if (!inList(B, p->el) && !inList(Res, p->el) && isLatinLetter(p->el)) {
            Res = new Node(p->el, Res);
        }
    }
    return Res;
}

void listMethod(const char* A, const char* B, const char* C, const char* D, char* E) {
    Node* LA = makeList(A);
    Node* LB = makeList(B);
    Node* LC = makeList(C);
    Node* LD = makeList(D);

    Node* BC = unionList(LB, LC);
    Node* BCD = unionList(BC, LD);

    Node* LE = diffList(LA, BCD);

    int k = 0;
    for (Node* p = LE; p; p = p->next) E[k++] = p->el;
    E[k] = 0;

    freeList(LA);
    freeList(LB);
    freeList(LC);
    freeList(LD);
    freeList(BC);
    freeList(BCD);
    freeList(LE);
}

void toBitArr(const char* S, int X[UNIV]) {
    for (int i = 0; i < UNIV; i++) X[i] = 0;
    for (int i = 0; S[i]; i++) {
        char c = S[i];
        if (!isLatinLetter(c)) continue;
        int idx = toLowerChar(c) - 'a';
        if (idx >= 0 && idx < UNIV)
            X[idx] = 1;
    }
}

void fromBitArr(int X[UNIV], const char* A, char* S) {
    int k = 0;
    bool used[UNIV] = { false };
    for (int i = 0; A[i]; i++) {
        char c = A[i];
        if (!isLatinLetter(c)) continue;
        int idx = toLowerChar(c) - 'a';
        if (idx >= 0 && idx < UNIV && X[idx] && !used[idx]) {
            S[k++] = c;
            used[idx] = true;
        }
    }
    S[k] = 0;
}

void bitArrMethod(const char* A, const char* B, const char* C, const char* D, char* E) {
    int a[UNIV], b[UNIV], c[UNIV], d[UNIV], e[UNIV];
    toBitArr(A, a);
    toBitArr(B, b);
    toBitArr(C, c);
    toBitArr(D, d);

    for (int i = 0; i < UNIV; i++)
        e[i] = a[i] && !(b[i] || c[i] || d[i]);

    fromBitArr(e, A, E);
}

unsigned int toWord(const char* S) {
    unsigned int w = 0;
    for (int i = 0; S[i]; i++) {
        char c = S[i];
        if (!isLatinLetter(c)) continue;
        int idx = toLowerChar(c) - 'a';
        if (idx >= 0 && idx < UNIV)
            w |= (1u << idx);
    }
    return w;
}

void fromWord(unsigned int w, const char* A, char* S) {
    int k = 0;
    bool used[UNIV] = { false };
    for (int i = 0; A[i]; i++) {
        char c = A[i];
        if (!isLatinLetter(c)) continue;
        int idx = toLowerChar(c) - 'a';
        if (idx >= 0 && idx < UNIV) {
            if (((w >> idx) & 1) && !used[idx]) {
                S[k++] = c;
                used[idx] = true;
            }
        }
    }
    S[k] = 0;
}

void wordMethod(const char* A, const char* B, const char* C, const char* D, char* E) {
    unsigned int wA = toWord(A);
    unsigned int wB = toWord(B);
    unsigned int wC = toWord(C);
    unsigned int wD = toWord(D);

    unsigned int wBCD = wB | wC | wD;
    unsigned int wE = wA & (~wBCD);

    fromWord(wE, A, E);
}

void measurePerformance(const function<void(char*)>& runner, const char* methodName, const char* A, const char* B, const char* C, const char* D) {
    char tmpE[80];
    runner(tmpE);

    const long long TARGET_MS = 100;
    const long long MAX_ITER = 10000000;
    long long iterations = 1;
    nanoseconds elapsed_ns(0);

    while (true) {
        auto t0 = high_resolution_clock::now();
        for (long long i = 0; i < iterations; ++i)
            runner(tmpE);
        auto t1 = high_resolution_clock::now();
        elapsed_ns = duration_cast<nanoseconds>(t1 - t0);
        if (elapsed_ns >= milliseconds(TARGET_MS) || iterations >= MAX_ITER)
            break;
        iterations *= 2;
    }

    double avg_ns = static_cast<double>(elapsed_ns.count()) / iterations;
    double avg_us = avg_ns / 1000.0;
    double total_ms = static_cast<double>(elapsed_ns.count()) / 1e6;

    cout << "\n=== " << methodName << " ===";
    cout << "\nResult E = "; printSet(tmpE);
    cout << "\nIterations executed: " << iterations;
    cout << "\nTotal time: " << fixed << setprecision(3) << total_ms << " ms";
    cout << "\nAverage per iteration: " << setprecision(3) << avg_us << " us (" << (long long)avg_ns << " ns)\n";
    cout << "------------------------\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    char A[80], B[80], C[80], D[80];

    cout << "Choose input mode:\n1. Random sets\n2. Keyboard input\n> ";
    int mode;
    cin >> mode;

    if (mode == 1) {
        randomSet(A);
        randomSet(B);
        randomSet(C);
        randomSet(D);

        cout << "\nGenerated sets:";
        cout << "\nA = "; printSet(A); cout << "\n";
        cout << "B = "; printSet(B); cout << "\n";
        cout << "C = "; printSet(C); cout << "\n";
        cout << "D = "; printSet(D); cout << "\n";
    }
    else {
        cout << "A = "; cin >> A;
        cout << "B = "; cin >> B;
        cout << "C = "; cin >> C;
        cout << "D = "; cin >> D;
    }

    while (true) {
        cout << "\nChoose method:\n1. Arrays\n2. Linked lists\n3. Bit array\n4. Machine word\n5. Test all methods\n6. Exit\n> ";
        int meth;
        cin >> meth;

        if (meth == 6) {
            cout << "Goodbye!\n";
            break;
        }

        function<void(char*)> runner;
        string methodName;

        switch (meth) {
        case 1:
            runner = [&](char* out) { arrayMethod(A, B, C, D, out); };
            methodName = "ARRAY METHOD";
            break;
        case 2:
            runner = [&](char* out) { listMethod(A, B, C, D, out); };
            methodName = "LINKED LIST METHOD";
            break;
        case 3:
            runner = [&](char* out) { bitArrMethod(A, B, C, D, out); };
            methodName = "BIT ARRAY METHOD";
            break;
        case 4:
            runner = [&](char* out) { wordMethod(A, B, C, D, out); };
            methodName = "MACHINE WORD METHOD";
            break;
        case 5:
            cout << "\n=== TESTING ALL METHODS ===\n";
            measurePerformance([&](char* out) { arrayMethod(A, B, C, D, out); }, "ARRAY METHOD", A, B, C, D);
            measurePerformance([&](char* out) { listMethod(A, B, C, D, out); }, "LINKED LIST METHOD", A, B, C, D);
            measurePerformance([&](char* out) { bitArrMethod(A, B, C, D, out); }, "BIT ARRAY METHOD", A, B, C, D);
            measurePerformance([&](char* out) { wordMethod(A, B, C, D, out); }, "MACHINE WORD METHOD", A, B, C, D);

            cout << "\nTry another method with the same sets? (y/n): ";
            {
                char response_all;
                cin >> response_all;
                if (response_all != 'y' && response_all != 'Y') {
                    cout << "Goodbye!\n";
                    return 0;
                }
            }
            continue;
        default:
            cout << "Invalid choice! Please try again.\n";
            continue;
        }

        measurePerformance(runner, methodName.c_str(), A, B, C, D);

        cout << "\nTry another method with the same sets? (y/n): ";
        char response;
        cin >> response;
        if (response != 'y' && response != 'Y') {
            cout << "Goodbye!\n";
            break;
        }
    }

    return 0;
}