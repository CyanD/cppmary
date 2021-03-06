//
// Created by sooda on 16/6/15.
//

#ifndef CPPMARY_FEATUREPROCESSORMANAGER_H
#define CPPMARY_FEATUREPROCESSORMANAGER_H
#include <map>
#include <string>
#include "FeatureProcessor.h"
#include "AllophoneSet.h"
#include <memory>


namespace cppmary {
    class FeatureProcessorManager {
        public:
            FeatureProcessorManager(std::string localeString, std::string phonesetXmlStr);
            FeatureProcessorManager(const FeatureProcessorManager& manager);
            ~FeatureProcessorManager();
            void setupGenericFeatureProcessors();
            void setupPhoneFeatureProcessors();
            void addFeatureProcessor(std::shared_ptr<FeatureProcessor> fp);
            std::shared_ptr<FeatureProcessor> getFeatureProcessor(std::string name);

        private:
            std::string localeString_;
            std::map<std::string, std::shared_ptr<FeatureProcessor> > processors_;
            std::map<std::string, std::vector<std::string> > phonefeature2values_;
            AllophoneSet phoneset_;

    };
}


#endif //CPPMARY_FEATUREPROCESSORMANAGER_H
