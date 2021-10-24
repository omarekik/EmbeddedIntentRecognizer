# EmbeddedIntentRecognizer
Simple and small intent recognition command line tool that is not AI based for low latency consideration.

### Examples
* What is the weather like today? => Prints (Intent: Get Weather)
* What is the weather like in Paris today? => Prints (Intent: Get Weather City)
* Tell me an interesting fact. => Prints (Intent: Get Fact)

### Build:
Buildable with cmake (minimum version 3.10) using modern C++ compiler (should support C++17) by running following command:
   ```
   git clone https://github.com/omarekik/EmbeddedIntentRecognizer && cd EmbeddedIntentRecognizer
   mkdir build && cd build && cmake .. && make && make test
   ```

### Run:
```
./IntentRecognizer/EmbeddedIntentRecognizer
```
### Open items:
* Actually boost/Tokenizer is used for input sentence parsing. Some research is done to avoid copying strings using string_view and Vince's CSV Parser (https://github.com/svandernotte/csv-parser). The limit of this parser is that it supports only one delimiter. 
* Some research is done to handle different semantic variations using AI. This is a great example (https://github.com/mit-nlp/MITIE/blob/master/examples/cpp/ner/ner_example.cpp) for integration of MITIE open source AI library and trained models in named entity recognition application.