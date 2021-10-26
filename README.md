# EmbeddedIntentRecognizer
Simple and small intent recognition command line tool that is not AI based for low latency consideration.

### Build:
Buildable with cmake (minimum version 3.14) using modern C++ compiler (minimum version C++17) by running following command for linux:
```
git clone https://github.com/omarekik/EmbeddedIntentRecognizer && cd EmbeddedIntentRecognizer
mkdir build && cd build && cmake .. && make && make test
```
For windows use following command:
```
git clone https://github.com/omarekik/EmbeddedIntentRecognizer && cd EmbeddedIntentRecognizer
mkdir build && cd build && cmake .. && cmake --build . && ctest
```
### Example of execution:
Remain in the build directory and run the following commands:
```
$ ./IntentRecognizer/EmbeddedIntentRecognizer -h
Program options:
  -h [ --help ]           print usage message
  -s [ --sentence ] arg   sentence to recognize its intents
  -d [ --dictionary ] arg path to csv file of intent per row that specifies the
                          intent name as first row element and context in
                          remaining row elements (see example in config folder)

$ ./IntentRecognizer/EmbeddedIntentRecognizer -s "Tell me an interesting fact."
Intent: GET FACT

$ ./IntentRecognizer/EmbeddedIntentRecognizer -s "What is the weather like today?" -d IntentRecognizer/intention.csv
Warning value for dictionary overwritten to IntentRecognizer/intention.csv
Intent: GET WEATHER
```
Each line in dictionary file is uppercase, started by intent name followed by comma separated values of vocabulary and the line ends by a comma. In the following example `GET` is the intent name and all other expressions are the intent possible vocabulary:
```
GET,WHAT,WHEN,WHERE,WHICH,WHO,WHOM,WHOSE,WHY,WHY DON'T,HOW,HOW FAR,HOW LONG,HOW MANY,HOW MUCH,HOW OLD,TELL,
```
A dictionary file example is present in config directory.
### Open items to improve performance:
* Actually boost/Split is used for CSV parsing. Some research is done to avoid copying strings using string_view and Vince's CSV Parser (https://github.com/svandernotte/csv-parser). The limit of this parser is that it supports only one delimiter. 
 > It is recommended to implement a CSV Parser that loads all CSV file content in a string buffer and all parsing and intent matching operations will be based on string_view so the application will be string copy free.  
* Some research is done to handle different semantic variations using AI. This is a great example (https://github.com/mit-nlp/MITIE/blob/master/examples/cpp/ner/ner_example.cpp) for integration of MITIE open source AI library and trained models in named entity recognition (NER) application.
 > In cases where this embedded application failes recognizing intent, it should log the input sentence and when possible send it to cloud SaaS application (well trained NER) which is not limited by embedded environment requirements. SaaS will recognize intent and context of failed sentence and send back a new CSV to embedded application to enrich its dictionary. 
* Case insensitive matching between sentence and expressions of intents is implemented in the commit e5e0568 using `boost::ifind_first`. Actual solution is based on predefine in uppercase all expressions of intents in CSV file   and `boost::to_upper` the input sentence for matching intents with it.
 > Some benchmarking should be done to confirm performance of actual solution.
* Parse multiple CSV file to enrich the IntentRecognizer and resolve overlap between them.
* Implement a multi-language UI command line.