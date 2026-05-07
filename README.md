# Naumlautrg Changes
Organization-focused edits with some style changes
* Renamed FinalPresentationCOSC-2436.cpp to main.cpp
* Moved classes and their members into seperate files
* Changed MenuItem from a class to a struct
* Removed using namespace std and added corresponding scope resolution operators
* Changes all string parameters to be passed by const reference
* Replaced input validation functions with a single template function getInput()
* InputValidation is now a static class
