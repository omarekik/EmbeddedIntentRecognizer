#include "IntentRecognizer.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <filesystem>
#include "CsvParser.h"

namespace bpo = boost::program_options;

int main(int argc, char* argv[])
{
    try {
        std::string sentence = "";
        std::string dictionary_file = "";
        
        bpo::options_description desc("Program options");
        desc.add_options()
        // First parameter describes option name/short name
        // The second is parameter to option
        // The third is description
        ("help,h", "display help menu")
        ("sentence,s", bpo::value<std::string>(&sentence), "sentence to recognize its intents")
        ("dictionary,d", bpo::value<std::string>(&dictionary_file) -> default_value("IntentRecognizer/intention.csv"), 
                "path to csv file of intent per row that specifies the intent name as first row "
                "element and context in remaining row elements (see example in config folder)")
        ;
    
        bpo::variables_map vm;
        bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
        bpo::notify(vm);

        if (vm.count("help") || !(0 < vm.count("sentence"))) {  
            std::cout << desc << "\n"
                        "sentence: " << sentence << "\n"
                        "dictionary: " << dictionary_file << "\n";
            return 0;
        }
        if(!vm["dictionary"].defaulted())
        {
            std::cout << "Warning value for dictionary overwritten to " << dictionary_file << "\n";
        }
        std::filesystem::path dictionary_path (dictionary_file);
        if (!std::filesystem::exists(dictionary_path))
        {
            std::cout<<"Check existance of dictionary CSV file " << dictionary_path << "\n";
        }
        else if (dictionary_path.extension() != ".csv")
        {
            std::cout<<"Extension of dictionary file should be .csv \n";
        }
        else
        {
            IntentRecognizer intent_recognizer;

            CsvParser csv_parser (dictionary_file);
            for(auto & row : csv_parser.getData())
            {
                intent_recognizer.emplaceIntent(Intent(std::move(row.second), std::move(row.first)));
            }    
            //std::cout<< intent_recognizer.serialize() << "\n";
            intent_recognizer.recognize(sentence);
            std::string recognized_intents = intent_recognizer.getRecognizedIntents();
            std::cout<< recognized_intents << "\n";
        }
    }
    catch(std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}