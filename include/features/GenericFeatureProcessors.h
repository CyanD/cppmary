//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_MARYGENERICFEATUREPROCESSORS_H
#define CPPMARY_MARYGENERICFEATUREPROCESSORS_H
#include "TargetElementNavigator.h"
#include "StringTranslator.h"
#include <string>
#include <vector>

//通用特征定义MaryGenericFeatureProcessors的下半部分, 原本在例如,Phone, nextPhone等. 包含大量的类,大量的对象..
namespace cppmary {
    const int RAIL_LIMIT = 19;
    const int ZHTONE_NUM = 6;
    const int ZHPOS_NUM = 46;
    const int TOBIACCENT_NUM = 20;
    const std::string ZHTONES[ZHTONE_NUM] = {"0", "1", "2", "3", "4", "5"};
    const std::string ZHPOS[ZHPOS_NUM] = { "0", "AG", "A", "AD", "AN", "B", "C", "DG", "D", "E",
                                    "F", "G", "H", "I", "J", "K", "L", "M", "NG", "N",
                                    "NR", "NS", "NT", "NZ", "O", "P", "Q", "R", "S", "TG",
                                    "T", "U", "VG", "V", "VD", "VN", "W", "X", "Y", "Z",
                                    "NL","NW","VF","VX","VI","VL" };
    const std::string TOBIACCENTS[TOBIACCENT_NUM] = { "0", "*", "H*", "!H*", "^H*", "L*", "L+H*", "L*+H", "L+!H*", "L*+!H", 
        "L+^H*", "L*+^H", "H+L*", "H+!H*", "H+^H*", "!H+!H*", "^H+!H*", "^H+^H*", "H*+L", "!H*+L" };
    class PhraseNumSyls : public FeatureProcessor  {
    public:
        PhraseNumSyls(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~PhraseNumSyls();
        virtual int process(Target target);
    };

    /*
     * The Tobi accent of current syllable
     */
    class TobiAccent : public FeatureProcessor {
    public:
        TobiAccent(std::string name, std::vector<std::string> possibleValues, TargetElementNavigator* navigator);
        virtual ~TobiAccent();
        virtual int process(Target target);
    };
    


}


#endif //CPPMARY_MARYGENERICFEATUREPROCESSORS_H
