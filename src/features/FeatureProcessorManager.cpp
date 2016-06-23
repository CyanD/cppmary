//
// Created by sooda on 16/6/15.
//

#include "features/FeatureProcessorManager.h"
#include "features/GenericFeatureProcessors.h"
#include "features/LanguageFeatureProcessors.h"

namespace cppmary {
    FeatureProcessorManager::FeatureProcessorManager(std::string localeString, std::string phonesetXmlStr) {
        //locale process
        localeString_ = localeString;
        setupGenericFeatureProcessors();
        AllophoneSet phonset(phonesetXmlStr);
        setupPhoneFeatureProcessors(phonset);
    }

    FeatureProcessorManager::~FeatureProcessorManager() {
        std::map<std::string, FeatureProcessor *>::iterator iter;
        for (iter = processors_.begin(); iter != processors_.end(); ++iter) {
            delete iter->second;
        }
    }

    void FeatureProcessorManager::setupGenericFeatureProcessors() {

        std::vector<std::string> phraseValues;
        for (int i = 0; i <= RAIL_LIMIT; i++) {
            phraseValues.push_back(std::to_string(i));
        }
        addFeatureProcessor(new PhraseNumSyls("phrase_numsyls", phraseValues, NULL));
        std::vector<std::string> zhToneValues;
        zhToneValues.assign(ZHTONES, ZHTONES+ZHTONE_NUM);
        TargetElementNavigator* syllableNav = new SyllableNavigator();
        TargetElementNavigator* prevSyllableNav = new PrevSyllableNavigator();
        TargetElementNavigator* prevPrevSyllableNav = new PrevPrevSyllableNavigator();
        TargetElementNavigator* nextSyllableNav = new NextSyllableNavigator();
        TargetElementNavigator* nextnextSyllableNav = new NextNextSyllableNavigator();
        TargetElementNavigator* wordNav = new WordNavigator();
        TargetElementNavigator* firstSylInWord = new FirstSyllableInWordNavigator();
        TargetElementNavigator* lastSylInPhrase = new LastSyllableInPhraseNavigator();
        addFeatureProcessor(new Zhtone("zhtone", zhToneValues, syllableNav));
        addFeatureProcessor(new Zhtone("prev_zhtone", zhToneValues, prevSyllableNav));
        addFeatureProcessor(new Zhtone("next_zhtone", zhToneValues, nextSyllableNav));
        addFeatureProcessor(new Zhtone("nextnext_zhtone", zhToneValues, nextnextSyllableNav));
        addFeatureProcessor(new Zhtone("prevprev_zhtone", zhToneValues, prevPrevSyllableNav));
        addFeatureProcessor(new Zhtone("phrase_zhtone", zhToneValues, lastSylInPhrase));


        std::vector<std::string> tobiValues;
        tobiValues.assign(TOBIACCENTS, TOBIACCENTS+TOBIACCENT_NUM);
        addFeatureProcessor(new TobiAccent("tobiAccent", tobiValues, syllableNav));
        addFeatureProcessor(new TobiAccent("prev_tobiAccent", tobiValues, prevSyllableNav));
        addFeatureProcessor(new TobiAccent("prevprev_tobiAccent", tobiValues, prevPrevSyllableNav));
        addFeatureProcessor(new TobiAccent("next_toAccent", tobiValues, nextSyllableNav));
        addFeatureProcessor(new TobiAccent("nextnext_tobiAccent", tobiValues, nextnextSyllableNav));


        std::vector<std::string> posValues;
        posValues.assign(ZHPOS, ZHPOS+ZHPOS_NUM);
        addFeatureProcessor(new Pos("pos", posValues, wordNav));


    }

    void FeatureProcessorManager::addFeatureProcessor(FeatureProcessor * fp) {
        processors_[fp->getName()] = fp;
    }

    FeatureProcessor * FeatureProcessorManager::getFeatureProcessor(std::string name) {
        //TODO: faild process
        return processors_[name];
    }

    void FeatureProcessorManager::setupPhoneFeatureProcessors(AllophoneSet phoneset) {
        std::vector<std::string> phoneValues;
        std::vector<std::string> pValues = phoneset.getAllophoneNames();
        std::string pauseSymbol = phoneset.getSilent().name();
        TargetElementNavigator* segmentNavigator = new SegmentNavigator();
        //addFeatureProcessor(new Phone("phone", pValues, pauseSymbol, segmentNavigator));
        addFeatureProcessor(new Phone("phone", pValues, segmentNavigator));
    }
}
