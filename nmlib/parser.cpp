#include "parser.hpp"

#include <rapidsjon/document.h>

#include <iostream>

namespace nm {

namespace {



optional<std::unique_ptr<ModuleInput> > parseModuleInput(const rapidjson::Value &inputValue, const ModuleType &moduleType)
{
    using namespace std;
    string name = inputValue["name"].GetString();
    string signalType = inputValue["type"].GetString();
    ModuleInput moduleInput{name, };
}

optional<std::unique_ptr<ModuleType> > parseModule(const rapidjson::Value &moduleValue)
{
}

optional<std::unique_ptr<ModuleType> > parseModuleType(const rapidjson::Value &type)
{
    auto &nameValue = type["name"];
    if(!nameValue.IsString()){
        std::cerr << "Module missing required field \"name\"\n";
        return {};
    }
    std::string name = nameValue.GetString();
    std::string description;
    auto &descriptionValue = type["description"];
    if(descriptionValue.IsString()){
        description = descriptionValue.GetString();
    }

    auto moduleType = std::unique_ptr<ModuleType>{new ModuleType(name, description)};

    //parse Inputs
    std::vector<ModuleInput> inputs;
    auto &inputsValue = type["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsArray()){
            return {};
        }
        for(rapidjson::SizeType i = 0; i < inputsValue.Size(); i++){
            auto maybeInput = parseModuleInput(inputsValue[i]);
            if(!maybeInput){
                return {};
            }
            inputs.push_back(*maybeInput);
        }
    }
    for(auto input : inputs){
        moduleType.addInput(input);
    }

    //parse submodules

    return {std::move(moduleType)};
}

bool parseModuleTypeArray(const rapidjson::Value &array, TypeManager &typeManager)
{
    if(!array.IsArray()){
        std::cerr << "Tried to parse an array that wasn't an array";
        return {};
    }
    std::map <std::string, std::unique_ptr<ModuleType>> moduleTypes{};
    for(rapidjson::SizeType i = 0; i < array.Size(); i++){
        auto maybeModuleType = parseModuleType(array[i]);
        if(!maybeModuleType){
            return false;
        }
        auto &moduleTypePtr = *maybeModuleType;
        if(!typeManager.addType(std::move(moduleTypePtr))){
            std::cerr << "Couldn't add type to typeManager.\n";
            return false;
        }
    }
    return true;
}

} // namespace

Parser::Parser()
{
}

optional<std::unique_ptr<TypeManager> > Parser::parseDocument(std::string input)
{
    rapidjson::Document document;
    document.Parse<0>(input.c_str());

    if(document.HasParseError()){
        std::cerr << "Couldn't parse json document\n";
        return {};
    }

    auto &moduleTypes = document["moduleTypes"];

    if(moduleTypes.IsNull()){
        std::cerr << "moduleTypes not present in root of document\n";
        return {};
    }

    std::unique_ptr<TypeManager> typeManager{new TypeManager()};
    if(!parseModuleTypeArray(moduleTypes, *(typeManager.get()))){
        return {};
    }
    return {std::move(typeManager)};
}

} // namespace nm
