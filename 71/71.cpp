#include <vector>
#include <unordered_map>
#include <string>
using std::vector, std::string;

class Solution
{
    struct Dfa {
        enum State {
            IDLE,
            START_DIR,
            DIR
        };
        const std::unordered_map<State, vector<State>> table = {
            // INPUT = {'/', not '/'}
            {IDLE, {START_DIR, IDLE}},
            {START_DIR, {START_DIR, DIR}},
            {DIR, {START_DIR, DIR}}
        };
        int getNextStateIndex(char c) {
            if (c == '/') {
                return 0;
            }
            return 1;
        }

        string curStr;
        string readBuffer;
        State curState = IDLE;
        void getChar(char c) {
            const State nextState = table.at(curState)[getNextStateIndex(c)];
            switch (nextState) {
                case IDLE: break;
                case START_DIR: {
                    if (curState == DIR) {
                        if (readBuffer == "..") {
                            int lastSlashIndex = -1;
                            for (int i = curStr.length() - 1; i >= 0; i--) {
                                if (curStr[i] == '/') {
                                    lastSlashIndex = i;
                                    break;
                                }
                            }
                            curStr = curStr.substr(0, lastSlashIndex + 1);
                        } else if (readBuffer == ".") {
                            // do nothing
                        } else {
                            curStr += readBuffer + "/";
                        }
                    }
                    readBuffer = "";
                    break;
                }
                case DIR: {
                    if (curState == DIR && curStr[curStr.length() - 1] != '/') {
                        curStr += "/";
                    }
                    readBuffer += c;
                    curStr += c;
                    break;
                }
                default: break;
            }
            curState = nextState;
        }
    };
public:
    string simplifyPath(string path)
    {
        Dfa dfa;
        for (const char c : path) {
            dfa.getChar(c);
        }
        return dfa.curStr;
    }
};