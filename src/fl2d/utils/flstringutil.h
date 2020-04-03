#pragma once

#include <string>
#include "ofMain.h"

using namespace std;

namespace flinternal {
    
    class flstringutil {
            
        public:
            /*!
             * �p�X����g���q���������ɂ��Ď��o��
             * @param[in] path �t�@�C���p�X
             * @return (������������)�g���q
             */
            static inline string getExtension(const string& path) {
                string ext;
                size_t pos1 = path.rfind('.');
                if(pos1 != string::npos){
                    ext = path.substr(pos1 + 1, path.size() - pos1);
                    string::iterator itr = ext.begin();
                    
                    while(itr != ext.end()) {
                        *itr = tolower(*itr);
                        itr++;
                    }
                    itr = ext.end()-1;
                    
                    //�p�X�̍Ō��\0��X�y�[�X���������Ƃ��̑΍�
                    while(itr != ext.begin()) {
                        if(*itr == 0 || *itr == 32){
                            ext.erase(itr--);
                        } else{
                            itr--;
                        }
                    }
                }
                return ext;
            }
            
            /**
             * �����񒆂��當������������ĕʂ̕�����ɒu������
             * @param str  : �u���Ώۂ̕�����B�㏑����܂��B
             * @param from : ����������
             * @param to   : �u����̕�����
             */
            static inline void replaceAll(string& str, const string& from, const string& to) {
                string::size_type pos = 0;
                while(pos = str.find(from, pos), pos != string::npos) {
                    str.replace(pos, from.length(), to);
                    pos += to.length();
                }
            }
            
            static int getLength(string& str, const string& target) {
                int n = 0;
                
                string::size_type pos = 0;
                while(pos = str.find(target, pos), pos != string::npos) {
                    //        str.replace(pos, from.length(), to);
                    pos += target.length();
                    
                    n ++;
                }
                
                return n;
            }
            
        private:
            flstringutil() { };
            ~flstringutil() { };
        
    };
    
}
