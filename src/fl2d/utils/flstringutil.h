#pragma once

#include <string>
#include "ofMain.h"

using namespace std;

namespace flinternal {
    
    class flstringutil {
        
    public:
        /*!
         * パスから拡張子を小文字にして取り出す
         * @param[in] path ファイルパス
         * @return (小文字化した)拡張子
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
                
                //パスの最後に\0やスペースがあったときの対策
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
         * 文字列中から文字列を検索して別の文字列に置換する
         * @param str  : 置換対象の文字列。上書かれます。
         * @param from : 検索文字列
         * @param to   : 置換後の文字列
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
