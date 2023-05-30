#include <cstring>
#include <map>
#include <fstream>
#include "tasks_rk1.h"

int Node::countNodes = 0;

char* NewChar(const char* s) {
    char* NString = new char[20];
    int chek = 0;
    for (int i = 0; i < strlen(s); ++i) {
        int chek1 = 0;
        for (int j = i; j > 0; j--) {
            if (s[i] == s[j - 1]) {
                chek++;
                chek1++;
                break;
            }
        }
        if (chek1 == 0) {
            NString[i - chek] = s[i];
            NString[i - chek + 1] = '\0';
        }
    }
    return NString;
}

void WorkWithFile::readFromFile(const char* fileName) {
    std::ifstream inf(fileName);
    std::string F0;
    std::string F1;
    while (std::getline(inf, F1))
        F0 += F1;
    inf.close();
    for (int i = 0; i < F0.length(); ++i) {
        dataOfFile[i] = F0[i];
        dataOfFile[i + 1] = '\0';
    }
}

void WorkWithFile::prepareTestFile(const char* fileName) {
    FILE* pFile;
    pFile = fopen(fileName, "w");
    int value = 20;
    int i;
    srand(time(nullptr));
    char MS;
    for (i = 0; i < value; ++i)
    {
        MS = (rand() % ('z' - 'a' + 1)) + 'a';
        if (MS < 'a') MS = ' ';
        fwrite(&MS, 1, sizeof(MS), pFile);
    }
    fclose(pFile);
}

WorkWithFile::WorkWithFile(const char* fileName) {
    readFromFile(fileName);
}

WorkWithFile::WorkWithFile() {
    prepareTestFile("sourceFile_task1.txt");
}

WorkWithFile::~WorkWithFile() {
    delete[] dataOfFile;
}

void WorkWithFile::writeStatInfoToFile(const char* outFile) {
    char* Simbols = NewChar(dataOfFile);
    int* CountArr = new int[strlen(Simbols)];
    for (int i = 0; i < strlen(Simbols); ++i) {
        CountArr[i] = 0;
    }
    for (int i = 0; Simbols[i] != '\0'; ++i) {
        for (int j = 0; j < strlen(dataOfFile); ++j) {
            if (Simbols[i] == dataOfFile[j])
                CountArr[i]++;
        }
    }
    FILE* pFile = fopen(outFile, "w");
    for (int i = 0; i < strlen(Simbols); ++i) {
        fprintf(pFile, "%c\t%d\n", Simbols[i], CountArr[i]);
    }
    fclose(pFile);
    delete[] Simbols;
    delete[] CountArr;
}

void buildTree(int height) {
    int chek = height - 1;
    for (int j = 1; j <= height; j++) {
        for (int i = chek--; i > 0; i--) {
            std::cout << " ";
        }
        for (int i = 0; i < 2 * j - 1; ++i) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

char* convertDecToBin(int number) {
    if (number != 0) {
        int CoolNum = abs(number);
        char* str = new char[33];
        int chek = 0;
        for (int i = 32; CoolNum > 0; i--) {
            str[i] = CoolNum % 2 + '0';
            CoolNum /= 2;
            chek++;
        }
        char* CoolStr = new char[chek];
        int Index = 33 - chek;
        for (int i = 0; i < chek; ++i) {
            if (i == 0 && number < 0) {
                CoolStr[i] = '-';
                chek++;
                continue;
            }
            CoolStr[i] = str[Index++];
            CoolStr[i + 1] = '\0';
        }
        delete[]str;
        return CoolStr;
    }
    else {
        char* str1 = new char[2];
        str1[0] = '0';
        str1[1] = '\0';
        return str1;
    }
}

void writeToFile(const char& fileName, const char* strNum) {
    FILE* pFile = fopen(&fileName, "w");
    fprintf(pFile, "%s", strNum);
    fclose(pFile);
}

char* convertBinToHex(const char* binNum) {
    int num = 0;
    if ((int)(strlen(binNum)) % 4 != 0)
        num = 4 - (int)(strlen(binNum)) % 4;
    char* CoolBinNum = new char[num + strlen(binNum) + 1];
    std::map<std::string, char> m{ {"0000", '0'}, {"0001", '1'}, {"0010", '2'},
                              {"0011", '3'}, {"0100", '4'}, {"0101", '5'},
                              {"0110", '6'}, {"0111", '7'}, {"1000", '8'},
                              {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
                              {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'},
                              {"1111", 'F'} };
    for (int i = 0; i < num; ++i) {
        CoolBinNum[i] = '0';
    }
    for (int i = num; i < num + strlen(binNum) + 1; ++i) {
        CoolBinNum[i] = binNum[i - num];
        CoolBinNum[i + 1] = '\0';
    }
    char* hexNum = new char[8];
    int index = 0;
    int i = 0;
    while (i < strlen(CoolBinNum)) {
        char* p = new char[5];
        for (int j = 0; j < 4; ++j) {
            p[j] = CoolBinNum[i++];
            p[j + 1] = '\0';
        }
        hexNum[index++] = m.find(p)->second;
        delete[] p;
    }
    hexNum[index] = '\0';
    delete[] CoolBinNum;
    int chek = 0;
    for (int j = 0; hexNum[j] == '0'; ++j) {
        chek++;
    }
    for (int j = 0; j < chek; ++j) {
        for (int k = 0; k < strlen(hexNum) - 1; ++k) {
            std::swap(hexNum[k], hexNum[k + 1]);
        }
    }
    hexNum[strlen(hexNum) - chek] = '\0';
    return hexNum;
}

void writeToFile(const char* fileName, int writeAppend, const char* hexNum, const char* binNum) {
    FILE* pFile = fopen(fileName, "w");
    fprintf(pFile, "%s\t%s", binNum, hexNum);
    fclose(pFile);
}

std::vector<float> averStr2DArray(const float* ar, int colCount, int rowCount) {
    std::vector<float> vr;
    for (int i = 0; i < rowCount; ++i) {
        float sum = 0;
        for (int j = 0; j < colCount; ++j) {
            sum += (*(ar + (i * colCount) + j));
        }
        float aver = sum / colCount;
        vr.emplace_back(aver);
    }
    return vr;
}

void randFill(float* ar, int N) {
    for (int i = 0; i < N; i++) {
        ar[i] = rand() / float(RAND_MAX) * 24.f + 1.f;
    }
}

LinkedList::LinkedList() {
    Head = nullptr;
    Tail = nullptr;
}

LinkedList::~LinkedList() {
    while (Head != nullptr) {
        Node* p = Head;
        Head = Head->next;
        delete p;
    }
}

void LinkedList::push_back(int nameNode) {
    Node* Element = new Node;
    if (Head == nullptr) {
        Element->nameNode = nameNode + 1;
        Element->next = nullptr;
        Element->prev = nullptr;
        Head = Tail = Element;
    }
    else {
        Element->next = nullptr;
        Element->nameNode = nameNode + 1;
        Element->prev = Tail;
        Tail->next = Element;
        Tail = Element;
    }
    Node::countNodes++;
}

void LinkedList::writeToFileFromTail() {
    FILE* pFile = fopen("ListFromTail.txt", "w");
    Node* p = Tail;
    while (p != nullptr) {
        fprintf(pFile, "%d%c%s", p->nameNode, ';', " ");
        p = p->prev;
    }
    fclose(pFile);
}

void LinkedList::writeToFileFromHead() {
    FILE* pFile = fopen("ListFromHead.txt", "w");
    Node* p = Head;
    while (p != nullptr) {
        fprintf(pFile, "%d%c%s", p->nameNode, ';', " ");
        p = p->next;
    }
    fclose(pFile);
}

void LinkedList::insert(int nameNode, int position) {
    if (position >= 0 && position < Node::countNodes + 1) {
        Node* Element = new Node;
        Element->nameNode = nameNode;
        if (position == 0) {
            Element->next = Head;
            Element->prev = nullptr;
            Head->prev = Element;
            Head = Element;
        }
        else {
            Node* p = Head;
            for (int i = 0; i < position - 1; ++i) {
                p = p->next;
            }
            Element->next = p->next;
            Element->prev = p;
            p->next = Element;
            if (position != Node::countNodes)
                Element->next->prev = Element;
            else
                Tail = Element;
        }
        Node::countNodes++;
    }
}

float StudentInfo::getAverMark(const std::string& subjName) {
    float sum = 0;
    for (auto it = subjMark.find(subjName)->second.first.begin(); it != subjMark.find(subjName)->second.first.end(); it++) {
        sum += *it;
    }
    float aver = sum / subjMark.find(subjName)->second.first.size();
    return aver;
}

int StudentInfo::addMark(const std::string& subjName, int mark) {
    if (subjMark.find(subjName) == subjMark.end())
        return 1;
    subjMark.find(subjName)->second.first.push_back(mark);
    subjMark.find(subjName)->second.second = getAverMark(subjName);
    return  0;
}

int StudentInfo::addSubj(const std::string& subjName) {
    if (subjMark.find(subjName) != subjMark.end())
        return 1;
    std::list<int> lst;
    float aver = 0;
    std::pair<std::list<int>, float> pair;
    pair.first = lst;
    pair.second = aver;
    subjMark.emplace(subjName, pair);
    return 0;
}

void StudentInfo::printInfoStudent(bool writeFile) {
    if (!writeFile) {
        FILE* pFile = fopen("Student.txt", "w");
        std::string z = std::get<0>(info);
        std::string z1 = std::get<1>(info);
        std::string z2 = std::get<2>(info);
        fprintf(pFile, "%s\t%s%c%s\n", z.c_str(), z1.c_str(), ':', z2.c_str());
        for (auto ite = subjMark.begin(); ite != subjMark.end(); ite++) {
            fprintf(pFile, "%s%s", ite->first.c_str(), " :\t");
            for (auto ite1 = ite->second.first.begin(); ite1 != ite->second.first.end(); ite1++) {
                fprintf(pFile, "%d%s", *ite1, ", ");
            }
            fprintf(pFile, "%s%f\n", " -- ", ite->second.second);
        }
        fclose(pFile);
    }
}

void StudentInfo::writeAllInfoToFile() {
    std::ofstream out("AllInfo.txt", std::ios::binary);
    out.write((char*)&info, sizeof(info));
    out.close();
}

bool brackets(const char* str) {
    std::map<char, char> mp{ {'(', ')'},{'[',']'},{'<','>'}, {'{','}'} };
    FILO Stack;
    for (int i = 0; i < strlen(str); ++i) {
        bool IsBrac = false;
        for (auto ite = mp.begin(); ite != mp.end(); ite++) {
            if (ite->first == str[i] || ite->second == str[i]) {
                IsBrac = true;
                break;
            }
        }
        if (IsBrac) {
            bool OpenBrac = false;
            for (auto iter = mp.begin(); iter != mp.end(); iter++) {
                if (iter->first == str[i]) {
                    Stack.AddEl(str[i]);
                    OpenBrac = true;
                    break;
                }
            }
            if (!OpenBrac) {
                char buf;
                Stack.GetEl(buf);
                if (mp.find(buf)->second != str[i]) {
                    Stack.AddEl(buf);
                    Stack.AddEl(str[i]);
                }
            }
        }
    }
    return Stack.IsEmpty();
}
