#ifndef FORMAT_HPP
#define FORMAT_HPP

#include<string>
#include<typeinfo>
#include<concepts>

namespace cyg{
    template<typename T>
    concept is_number=std::integral<T> or std::floating_point<T>;

    //only for float number
    std::string no_suffix_0(std::string value){
        if(value.find('.')<value.size()){
            while(value.back()=='0')
                value.pop_back();
            if(value.back()=='.')value.pop_back();
        }
        return value;
    }

    template<typename T>
    requires is_number<T>
    std::string to_str(T value){
        return no_suffix_0(std::to_string(value));
    }

    std::string to_str(std::string value){
        return value;
    }

    std::string format(std::string fmt){
        return fmt;
    }

    template<typename hT,typename...argsT>
    std::string format(std::string fmt,hT hArg,argsT...Args){
        if(fmt.find("{}")<fmt.size()){
            fmt.replace(fmt.find("{}"),std::string("{}").size(),to_str(hArg));
            return format(fmt,Args...);
        }
        else
            return fmt;
    }
}

#endif //FORMAT_HPP
