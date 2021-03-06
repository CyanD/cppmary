//
// Created by sooda on 16/6/8.
//

#include "modules/Tokenizer.h"
#include <iostream>
#include "common.h"
#include "pugixml/pugixml.hpp"
#include "limonp/Logging.hpp"
#include <algorithm>

namespace cppmary {

    Tokenizer::Tokenizer() {
        name_ = "tokenizer";
    }

    Tokenizer::~Tokenizer() {
    }

    std::string Tokenizer::process(const std::string& input) {
        XLOG(DEBUG) << "tokenizer input: " << input;
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_string(input.c_str());
        pugi::xml_node paragraph = doc.child("maryxml").first_child();
        std::string text = paragraph.child_value();
        text = trim(text);
        //std::vector<std::string> words;
        std::vector<std::pair<std::string, std::string> > wordTags;
        JiebaSegment::Instance()->Tag(text, wordTags);
        pugi::xml_node textNode = paragraph.first_child();
        paragraph.remove_child(textNode);
        pugi::xml_node sentence = paragraph.append_child("s");
        for (int i = 0; i < wordTags.size(); i++) {
            pugi::xml_node token = sentence.append_child("t");
            token.append_child(pugi::node_pcdata).set_value(wordTags[i].first.c_str());
            std::string pos = wordTags[i].second;
            std::transform(pos.begin(), pos.end(), pos.begin(), (int (*)(int))toupper);
            token.append_attribute("pos") = pos.c_str();
        }
        std::string tokenStr = MaryXml::saveDoc2String(doc);
        XLOG(DEBUG) << "tokenizer output: " << tokenStr;
        return tokenStr;
    }
}
